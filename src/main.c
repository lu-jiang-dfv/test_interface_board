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
#include I2C_CLIENT_H
#include "code_base/libs/dfv_i2c_registers.h"
#include "code_base/libs/display.h"

int main(void) {
  // EepromInit();
  BoardInit();
  TRISEbits.TRISE0 = TRIS_OUT;
  LATEbits.LATE0 = 1;
  // AdcInit();
  // ChargeInit();
  // HeadlightInit();
  // LedInit();
  // WhiteLedInit();
  EusartInit();
  I2c2ClientInit();
  CvdInit();
//  I2C2_Initialize();

  TRISBbits.TRISB0 = TRIS_OUT;
  LATBbits.LATB0 = 0;

  //I2cRegisterConfig();

  // I2cClientSetCommType(kI2cRegister);
  // uint8_t data[10];
  // for (uint8_t i = 0; i < 10; ++i) {
  //   data[i] = 0;
  // }
  // data[kHeadLightID] = kHeadLightMini;  // ID for mini board
  // data[kHeadLightPolarity] = kPolarityDental;  // polarity for mini
  // data[kHeadLightCurrentLimit] = 70;  // current limit for mini 10mA per unit
  // I2cClientSetRegisters(0, data, 10);

  TRISBbits.TRISB4 = TRIS_OUT;
  LATBbits.LATB4 = 0;

  TRISCbits.TRISC6 = TRIS_OUT;
  LATCbits.LATC6 = 0;

  GlobalInterruptEnable(true);

  DisplayAddStr("$$reboot");
  DisplayAddStr("$test_interface_board");
  DisplayAddStr("$compiled ");
  DisplayAddStr(__DATE__);
  DisplayAddStr(" ");
  DisplayAddStr(__TIME__);
  DisplayAddStr("$pcon0");
  DisplayAddNum8(GetPcon0());
  DisplayAddStr("$status");
  DisplayAddNum8(GetStatus());
  DisplayAddStr("$");
  DisplayAndWait(150);

  uint16_t display_wait_counter = 0;
  uint16_t display_line_counter = 0;
  while(1) {
    DelayMs(20);
    if (display_wait_counter > 50) {
      display_wait_counter = 0;
      DisplayAddStr("*");
      if (display_line_counter >= 60) {
        display_line_counter = 0;
        DisplayAddStr("$");
      } else {
        ++display_line_counter;
      }
      PetWatchDog();
    } else {
      DisplayOneItem();
      ++display_wait_counter;
    }
    uint32_t cvd_read = CvdRead();
    uint16_t value1 = cvd_read >> 16;
    uint16_t value2 = cvd_read & 0xFFFF;
    if (value1 >= value2) {
      LATEbits.LATE0 = 1;
    } else {
      LATEbits.LATE0 = 0;
    }
//    DisplayAddNum32(CvdRead());
//    DisplayAddStr(" ");
  }
}

/**
 * Interrupt handler
 */
void __interrupt(irq(default), base(0x4008)) DEFAULT_ISR(void) {
  LATBbits.LATB4 = 1;
  bool caught = false; 
  GlobalInterruptEnable(false);
  // eusart interrupt
  if (PIR3bits.U1TXIF && PIE3bits.U1TXIE) {  // If interrupt enabled and flag is set
      EusartInterruptHandler();
      caught = true;
  }

  if (PIE6bits.I2C2IE && PIR6bits.I2C2IF)  {
    I2c2ClientIsr();
    caught = true;
  } else if (PIE5bits.I2C2TXIE && PIR5bits.I2C2TXIF) {
    I2c2ClientIsr();
    caught = true;
  } else if (PIE5bits.I2C2RXIE && PIR5bits.I2C2RXIF) {
    I2c2ClientIsr();
    caught = true;
  } else if (PIE6bits.I2C2EIE && PIR6bits.I2C2EIF) {
    I2c2ClientErrorIsr();
    caught = true;
  }

  if (PIE3bits.I2C1IE && PIR3bits.I2C1IF)  {
    I2c1ClientIsr();
    caught = true;
  } else if (PIE3bits.I2C1TXIE && PIR3bits.I2C1TXIF) {
    I2c1ClientIsr();
    caught = true;
  } else if (PIE2bits.I2C1RXIE && PIR2bits.I2C1RXIF) {
    I2c1ClientIsr();
    caught = true;
  } else if (PIE3bits.I2C1EIE && PIR3bits.I2C1EIF) {
    I2c1ClientErrorIsr();
    caught = true;
  }

  if (!caught) {
//      LATCbits.LATC6 = 1;
//      ee_write(0x79, U1ERRIR);
  }
  GlobalInterruptEnable(true);
  LATBbits.LATB4 = 0;
  LATCbits.LATC6 = 0;
}
