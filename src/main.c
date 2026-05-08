/**
 * @file main.c
 * @brief main for interface board
 */

#include "code_base/board_choice.h"
#include "include.h"
#include MCU_CONFIG_H
#include ADC_H
#include BOARD_H
#include EUSART_H
#include HAL_H
#include I2C_HOST_H
#include "code_base/libs/display.h"

int main(void) {
  // EepromInit();
  BoardInit();
  // AdcInit();
  // ChargeInit();
  // HeadlightInit();
  // LedInit();
  // WhiteLedInit();
  EusartInit();

  GlobalInterruptEnable(true);

  while(1) {
    DelayMs(500);
    DisplayAddStr("*");
    DisplayAndWait(10);
    PetWatchDog();
  }
}

/**
 * Interrupt handler
 */
void __interrupt(irq(default), base(0x4008)) DEFAULT_ISR(void) {
  GlobalInterruptEnable(false);

  // I2C interrupt
  // if (CheckI2cIntFlag() || CheckI2cTxIntFlag() || CheckI2cRxIntFlag()) {
  //   I2cIsr();
  // }

  // I2C2 interrupt
  // if (CheckI2c2IntFlag() || CheckI2c2TxIntFlag() || CheckI2c2RxIntFlag()) {
  //   I2cHostIsr(1);
  // }

  // if (!I2cHostBusy(0) &&
  //     !I2cHostBusy(1)) {  // we stop everything when i2c transaction is active
  //   // timer1 task for scheduler
  //   if (CheckTimer1IntFlag()) {
  //     Timer1InterruptReset();
  //     main_task_flag = true;
  //   }
    // eusart interrupt
    if (CheckUsartTxIntEnabled() &&
        CheckUsartTxIntFlag()) {  // If interrupt enabled and flag is set
      EusartInterruptHandler();
    }
  // }

  // adc comparator triggered interrup
  // if (CheckAdcCompInterrupt()) {
  //   // we disable adc so that it only trip once
  //   // otherwise it will overwrite all the eeprom error record
  //   EnableAdcCompInterrupt(false);
  //   ClearAdcCompInterrupt();
  //   DisableAdc();
  //   AddToSystemError(false, kErrorMain, 1);
  // }

  GlobalInterruptEnable(true);
}

#if 0
#include "batt_par.h"
#include "bms.h"
#include "bms_ltc2943.h"
#include "bms_max17260.h"
#include "charge.h"
#include "code_base/common_type.h"
#include "code_base/libs/dfv_i2c_registers.h"
#include "code_base/libs/display.h"
#include "code_base/libs/ds1775r_lib.h"
#include "code_base/libs/headlight_lib.h"
#include "code_base/libs/i2c_interface.h"
#include "code_base/libs/tps25750_i2crw.h"
#include "eeprom.h"
#include "error.h"
#include "headlight.h"
#include "headlight_flash.h"
#include "idle.h"
#include "led.h"

#include "self_test.h"
#include "version.h"
#include "white_led.h"

#define CYCLE_TEST 0
#define SELF_TEST_ENABLE 0

#if (CYCLE_TEST == 1)
static bool fully_charged = false;
static uint16_t restart_delay = 0;
#endif

typedef enum {
  kMainStateStart,
  kMainStateIdleEnter,
  kMainStateIdle,
  kMainStateChargeEnter,
  kMainStateCharge,
  kMainStateHeadlightEnter,
  kMainStateHeadlight,
  kMainStatePowerDownEnter,
  kMainStatePowerDown,
  kMainStateFaultEnter,
  kMainStateFault
} MainStateEnum;

const uint16_t kSelfShutdownTime =
    (uint16_t)(1000 / SCHEDULER_TIME) * 60 * 10;  // 10 minutes

static void DemoLedTask(void);
static bool PowerDownDetection(void);
static uint8_t ConvertTemperature(uint16_t adc_temperature);
static void LedsUpdate(MainStateEnum main_state, double soc, bool low_batt);

bool main_task_flag = false;

int main(void) {
  EepromInit();
  BoardInit();
  AdcInit();
  ChargeInit();
  HeadlightInit();
  LedInit();
  WhiteLedInit();
  EusartInit();
  I2cHostInit();
  I2cInterfaceInit();
  //  PortExpanderInit();

  EeUpdateRebootCtr();
  DisplayAddStr("$$reboot");

  DisplayAddStr("$compiled ");
  DisplayAddStr(__DATE__);
  DisplayAddStr(" ");
  DisplayAddStr(__TIME__);
  DisplayAddStr("$pcon0");
  DisplayAddNum8(GetPcon0());
  DisplayAddStr("$status");
  DisplayAddNum8(GetStatus());

  VersionUpdate();

  ClearPowerOnBrownOutReset();

  SetWhiteLedState(kWhiteLedOn);

#if (CYCLE_TEST == 1)
  EnablePowerOutlet(true);
#endif

  bool battery_empty = (bool)(EeGetBattEmpty());

  // check if watch dog reset occured
  if (CheckWatchDogReset()) {
    ClearWatchDogReset();
    EeUpdateWatchDogCtr();
  }

  GlobalInterruptEnable(true);

  DisplayAndWait(80);

#if SELF_TEST_ENABLE
  // self test if '=' received within 2 seconds
  uint8_t rx_data;
  for (uint8_t i = 0; i < 20; ++i) {
    if (EusartRead(&rx_data)) {
      if (rx_data == '=') {
        SelfTest();
      }
    }
    DelayMs(100);
    PetWatchDog();
  }
#endif

  MainStateEnum main_state = kMainStateStart;
  double state_of_charge = 0;
  bool main_power_down_detected = false;
  uint8_t power_down_ctr = 0;
  const uint8_t kPowerDownTime =
      1000 / SCHEDULER_TIME;  // wait 1 second before power down
  uint16_t self_shutdown_ctr = 0;
  bool charger_started = false;
  BatteryReadyEnum battery_ready = kBatteryNotDetected;
  uint8_t battery_check_ctr = 0;
  const uint8_t kBatteryCheckCycle =
      1000 / SCHEDULER_TIME;  // check battery every 1 second
  uint16_t headlight_current_average = 0;

  while (1) {
    //    SLEEP();
    DelayUs(5);
    if (!main_task_flag) {
      continue;
    }
    main_task_flag = false;

    ChargerPresentUpdate();
    HeadlightPresentUpdate();
    main_power_down_detected = PowerDownDetection();
    switch (main_state) {
      case kMainStateStart:
        if ((battery_check_ctr > kBatteryCheckCycle) ||
            (battery_ready != kBatteryNotDetected)) {
          battery_check_ctr = 0;
          battery_ready = CheckBatteryReady(false);
        } else {
          ++battery_check_ctr;
        }
        if (battery_ready == kBatteryReady) {
          main_state = kMainStateIdleEnter;
        } else if (battery_ready == kBatteryFault) {
          AddToSystemError(true, kErrorMain, 1);
          main_state = kMainStateFaultEnter;
        } else if (GetChargerPresent() && (!charger_started)) {
          DisplayAddStr("$load charger patch");
          DisplayAndWait(30);
          if (ChargeDownloadPatch()) {
            EnableCharger(true);
            charger_started = true;
            CheckBatteryReady(true);  // reset battery check
            DisplayAndWait(60);
          } else {
            AddToSystemError(true, kErrorMain, 2);
            main_state = kMainStateFaultEnter;
          }
        }
        break;
      case kMainStateIdleEnter:
        IdleBattInit();
        main_state = kMainStateIdle;
        DisplayAddStr("$idle");
        self_shutdown_ctr = 0;
        break;
      case kMainStateIdle:
        IdleSchedulerTask();
#if (CYCLE_TEST == 1)
        if (restart_delay > 0) {
          --restart_delay;
          break;
        }
        EnablePowerOutlet(true);
#endif
        ++self_shutdown_ctr;
        if (self_shutdown_ctr >= kSelfShutdownTime) {
          IdleEnd();
          main_state = kMainStatePowerDownEnter;
        } else if (main_power_down_detected) {
          IdleEnd();
          main_state = kMainStatePowerDownEnter;
        } else if (GetSystemErrorFunction() != kErrorNone) {
          IdleEnd();
          main_state = kMainStateFaultEnter;
#if (CYCLE_TEST == 1)
        } else if (GetChargerPresent() && (!fully_charged)) {
#else
        } else if (GetChargerPresent()) {
#endif
          IdleEnd();
          main_state = kMainStateChargeEnter;
        } else if (GetHeadlightPresent() && (!HeadlightFlashStatus()) &&
                   (!BattEndOfLife()) && (!battery_empty)) {
          // headlight present, turn on headlight
#if (CYCLE_TEST == 1)
          fully_charged = false;
#endif
          IdleEnd();
          main_state = kMainStateHeadlightEnter;
        }
        break;
      case kMainStateChargeEnter:
#if (CYCLE_TEST == 0)
        // tunr off switch power, use LDO3.3 enabled circuit
        // so that circuit shut down when charger unplugged
//        DisablePower();
#endif
        HeadlightFlashStatusReset();
        main_state = kMainStateCharge;
        DisplayAddStr("$charge");
        if ((!charger_started) && (!ChargeDownloadPatch())) {
          main_state = kMainStateFaultEnter;
        }
        // enable charger and set current limit after charging started
        ChargeStart();
        battery_empty = false;
        EeSaveBattEmpty(0);
        break;
      case kMainStateCharge:
        ChargeSchedulerTask();
        if (main_power_down_detected) {
          charger_started = false;
          ChargeEnd();
          main_state = kMainStatePowerDownEnter;
        } else if (GetSystemErrorFunction() != kErrorNone) {
          charger_started = false;
          ChargeEnd();
          main_state = kMainStateFaultEnter;
#if (CYCLE_TEST == 1)
        } else if (!ChargeGetChargingStatus()) {
          fully_charged = true;
          ChargeEnd();
          main_state = kMainStateIdleEnter;
#endif
        } else if (!GetChargerPresent()) {
          charger_started = false;
          ChargeEnd();
          main_state = kMainStateIdleEnter;
          // main_state = kMainStatePowerDownEnter;
        }
        break;
      case kMainStateHeadlightEnter:
        if (HeadlightStart()) {
          main_state = kMainStateHeadlight;
          DisplayAddStr("$headlight");
        }
        break;
      case kMainStateHeadlight:
        if (main_power_down_detected) {
          // HeadlightTriggerToggle();
          // DisplayAddStr("$headlight trigger");
          // HeadlightSaveLevel();
          HeadlightEnd();
          main_state = kMainStatePowerDownEnter;
        } else if (GetSystemErrorFunction() != kErrorNone) {
          HeadlightEnd();
          main_state = kMainStateFaultEnter;
        } else if (!GetHeadlightPresent()) {
          HeadlightEnd();
          main_state = kMainStateIdleEnter;
        } else if (HeadlightSchedulerTask()) {
          HeadlightEnd();
          main_state = kMainStateIdleEnter;
          battery_empty = true;
          EeSaveBattEmpty(1);
#if (CYCLE_TEST == 1)
          restart_delay = 50 * 10;  // 10 second
          EnablePowerOutlet(false);
#else
        } else if (GetChargerPresent()) {
          // charger present, turn off headlight
          HeadlightEnd();
          main_state = kMainStateChargeEnter;
#endif
        }
        break;
      case kMainStatePowerDownEnter:
        // disable all interrupt except scheduler timer
        SetUsartTxInterruptEanble(false);
        DisplayAddStr("$power down");
        DisplayAndWait(10);
        main_state = kMainStatePowerDown;
        break;
      case kMainStatePowerDown:
        // wait here until power down
        if (power_down_ctr > kPowerDownTime) {
          DisablePower();
        } else {
          ++power_down_ctr;
        }
        break;
      case kMainStateFaultEnter:
        DisplayAddStr("$fault");
        main_state = kMainStateFault;
        self_shutdown_ctr = 0;
        EnableHeadlight(false);
        EnableCharger(false);
        break;
      case kMainStateFault:
        // wait here until power down
        ++self_shutdown_ctr;
        if (self_shutdown_ctr >= kSelfShutdownTime) {
          main_state = kMainStatePowerDownEnter;
        } else if (main_power_down_detected) {
          main_state = kMainStatePowerDownEnter;
        }
        break;
    }

    //    PortExpanderUpdate();

    headlight_current_average = AdcRead(kAdcHeadLightCurrent);

    if (BmsSchedulerTask()) {
      // DisplayAddStr(" s");
      // DisplayAddNum8((uint8_t)main_state);

      DisplayAddStr(" V");
      DisplayAddFloat(GetBatteryVoltage(), 1, 2);

      DisplayAddStr(" I");
      DisplayAddFloat(GetBatteryCurrent(), 1, 2);

      if (main_state == kMainStateCharge) {
        I2cSetAddress(kTps25750I2cAddress);

        DisplayAddStr(" I");
        uint8_t current_limit;
        Bq25798ReadRegister(0x4, &current_limit);
        DisplayAddNum8(current_limit);

        DisplayAddStr(" C3");
        uint8_t charge_control;
        Bq25798ReadRegister(0x12, &charge_control);
        DisplayAddNum8(charge_control);

        DisplayAddStr(" T");
        uint8_t term_control;
        Bq25798ReadRegister(0x9, &term_control);
        DisplayAddNum8(term_control);

        DisplayAddStr(" VB");
        uint8_t vbus_h, vbus_l;
        Bq25798ReadRegister(0x35, &vbus_h);
        Bq25798ReadRegister(0x36, &vbus_l);
        uint16_t vbus =
            ((uint16_t)(vbus_h & 0xFF) << 8) + (uint16_t)(vbus_l & 0xFF);
        double vbus_d = (double)(vbus)*0.001;
        DisplayAddFloat(vbus_d, 2, 2);
      }

      // DisplayAddStr(" RX");
      // DisplayAddNum8(CHARGER_INT_PORT);

      if (main_state == kMainStateHeadlight) {
        DisplayAddStr(" IH");
        double current_d =
            (double)(headlight_current_average) / 4096.0 * 3.3 - 0.25;
        DisplayAddFloat(current_d, 1, 2);
      }

      // DisplayAddStr(" BT");
      uint16_t adc_temperature = AdcRead(kAdcBatteryNtc);
      if (adc_temperature < kTemperatureP60) {
        // DisplayAddStr("H");
        AddToSystemError(false, kErrorMain, 3);
      } else if (adc_temperature > kTemperatureN20) {
        // DisplayAddStr("L");
        AddToSystemError(false, kErrorMain, 4);
      }
      // DisplayAddNum8(ConvertTemperature(adc_temperature));

      // DisplayAddStr(" T");
      uint8_t temp;
      CheckI2cErrorAndAddToSystemError(Ds1775rReadTemperature(&temp),
                                       kErrorMain, 5);
      if (temp > 80 && temp < 120) {
        // DisplayAddStr("H");
        AddToSystemError(false, kErrorMain, 6);
      }
      // DisplayAddNum8(temp);

      // DisplayAddStr(" hl");
      // DisplayAddNum8((uint8_t)(USBC_ACK_PORT));

//      Max17260CheckAlive();
      if (Max17260CheckBatteryReady(false) == kBatteryReady) {
        DisplayAddStr(" 1-cell v");
        DisplayAddFloat(Max17260GetBatteryVoltage(), 1, 2);
        DisplayAddStr(" i");
        DisplayAddFloat(Max17260GetBatteryCurrent(), 1, 2);
        DisplayAddStr(" soc");
        DisplayAddFloat(Max17260GetBatteryStateOfCharge(), 1, 4);
      }

      DisplayAddStr(" S");
      state_of_charge = GetBatteryStateOfCharge();
      DisplayAddFloat(state_of_charge, 1, 4);

      //      DisplayAddStr(" C");
      DisplayAddNum8((uint8_t)ChargeGetChargingStatus());

      DisplayAddStr("  ");
      static uint8_t output_ctr = 0;
      ++output_ctr;
      if (output_ctr >= 6) {
        if (main_state == kMainStateHeadlight) {
          uint8_t temp;
          if (HeadlightReadRegister(kHeadLightTemperature, &temp)) {
            DisplayAddStr(" headlight temperature ");
            DisplayAddFloat((double)(temp - 100.0), 3, 1);
          } else {
            DisplayAddStr(" headlight temperature read fail");
          }
        }
        DisplayAddStr("$");
        output_ctr = 0;
      }
      //      FlushLED();
    }

    LedsUpdate(main_state, state_of_charge,
               (battery_empty && GetHeadlightPresent()));

    AdcSchedulerTask();

    if (DisplayOneItem()) {
      DelayMs(1);
    }

    bool led_on = WhiteLedSchedulerTask();
    LedSchedulerTask(led_on);

    PetWatchDog();

    // at the end of scheduler task, check the time used
    if (main_state != kMainStatePowerDown) {
      EeUpdateMaxTaskTime(CheckTimer1Passed());
    }
    // if flag is set, this task last longer than time slot
    if (main_task_flag) {
      EeUpdateMaxTaskTime(-1);
    }
  }
}

/**
 * Interrupt handler
 */
void __interrupt(irq(default), base(0x4008)) DEFAULT_ISR(void) {
  GlobalInterruptEnable(false);

  // I2C interrupt
  if (CheckI2cIntFlag() || CheckI2cTxIntFlag() || CheckI2cRxIntFlag()) {
    I2cIsr();
  }

  // I2C2 interrupt
  if (CheckI2c2IntFlag() || CheckI2c2TxIntFlag() || CheckI2c2RxIntFlag()) {
    I2cHostIsr(1);
  }

  if (!I2cHostBusy(0) &&
      !I2cHostBusy(1)) {  // we stop everything when i2c transaction is active
    // timer1 task for scheduler
    if (CheckTimer1IntFlag()) {
      Timer1InterruptReset();
      main_task_flag = true;
    }
    // eusart interrupt
    if (CheckUsartTxIntEnabled() &&
        CheckUsartTxIntFlag()) {  // If interrupt enabled and flag is set
      EusartInterruptHandler();
    }
  }

  // adc comparator triggered interrup
  // if (CheckAdcCompInterrupt()) {
  //   // we disable adc so that it only trip once
  //   // otherwise it will overwrite all the eeprom error record
  //   EnableAdcCompInterrupt(false);
  //   ClearAdcCompInterrupt();
  //   DisableAdc();
  //   AddToSystemError(false, kErrorMain, 1);
  // }

  GlobalInterruptEnable(true);
}

static void DemoLedTask(void) {
  static uint16_t main_led_task_ctr = 2499;
  static uint8_t main_led_level = 1;
  ++main_led_task_ctr;
  if (main_led_task_ctr >= 2500) {
    main_led_task_ctr = 0;
    LedFlashing(main_led_level, false);
    ++main_led_level;
    if (main_led_level >= 6) {
      main_led_level = 1;
    }
  }
}

/**
 * @brief check if power down initialized
 *
 * @return true if power down detected
 */
static bool PowerDownDetection(void) {
  // return true only once (debounce) because power down button also used
  // to trigger headlight
  const int8_t kPowerDownDetectionLimit = 2;
  static int8_t power_down_detection_ctr = 0;
  if (PowerDownDetected()) {
    if (power_down_detection_ctr >= kPowerDownDetectionLimit) {
      power_down_detection_ctr = -1;
      return true;
    }
    if (power_down_detection_ctr >= 0) {
      ++power_down_detection_ctr;
    }
  } else {
    power_down_detection_ctr = 0;
  }
  return false;
}

/**
 * @brief convert temperature to 1 degree resolution
 *
 * @param adc_temperature adc temperature
 * @return uint8_t temperature in 1 degree resolution
 */
static uint8_t ConvertTemperature(uint16_t adc_temperature) {
  uint16_t ntc_10k[] = {3004, 2968, 2932, 2898, 2862, 2824, 2787, 2749, 2712,
                        2674, 2633, 2596, 2556, 2521, 2477, 2438, 2403, 2360,
                        2323, 2284, 2243, 2200, 2164, 2127, 2088, 2048, 2009,
                        1972, 1933, 1896, 1859, 1822, 1786, 1749, 1713, 1678,
                        1643, 1609, 1574, 1541, 1509, 1475, 1443, 1412, 1380,
                        1349, 1319, 1291, 1261, 1232, 1205, 1177, 1149, 1124,
                        1097, 1071, 1046, 1021, 998,  974,  952};
  uint8_t temperature_result = 60;
  for (uint8_t index = 0; index < 60; ++index) {
    if (adc_temperature > ntc_10k[index]) {
      temperature_result = index;
      break;
    }
  }
  return temperature_result;
}

/**
 * @brief update leds based on main state
 *
 * @param main_state main state
 * @param soc state of charge
 */
static void LedsUpdate(MainStateEnum main_state, double soc, bool low_batt) {
  static MainStateEnum main_state_last = kMainStateStart;
  static double soc_last = 0;
  static bool low_batt_last = false;
  static bool charging_active_last = false;
  if ((main_state_last == main_state) && ((soc_last - soc) < 0.01) &&
      ((soc_last - soc) > -0.01) && (low_batt_last == low_batt) &&
      (charging_active_last == ChargeGetChargingStatus())) {
    return;
  }
  main_state_last = main_state;
  soc_last = soc;
  low_batt_last = low_batt;
  charging_active_last = ChargeGetChargingStatus();

  uint8_t led_level = 1;
  if (soc > 0.8) {
    led_level = 5;
  } else if (soc > 0.6) {
    led_level = 4;
  } else if (soc > 0.4) {
    led_level = 3;
  } else if (soc > 0.2) {
    led_level = 2;
  } else {
    led_level = 1;
  }

  if ((main_state == kMainStateFault) || (main_state == kMainStateFaultEnter)) {
    SetWhiteLedErrorCode(GetSystemSubError());
    SetWhiteLedState(kWhiteLedError);
  } else if ((main_state == kMainStateCharge) && ChargeGetChargingStatus()) {
    SetWhiteLedPulseStep(16 - 2 * led_level);
    SetWhiteLedState(kWhiteLedPulse);
  } else if ((main_state == kMainStateCharge) && (!ChargeGetChargingStatus())) {
    SetWhiteLedState(kWhiteLedDim);
  } else {
    SetWhiteLedState(kWhiteLedOn);
  }

  if ((main_state == kMainStateFault) || (main_state == kMainStateFaultEnter)) {
    SetLedErrorCode((uint8_t)GetSystemErrorFunction(), GetSystemI2cError());
  } else if (low_batt) {
    LedFlashing(1, true);
  } else if ((main_state == kMainStateCharge) && ChargeGetChargingStatus()) {
    LedFlashing(led_level, false);
  } else {
    LedSolid(led_level);
  }
}

#endif