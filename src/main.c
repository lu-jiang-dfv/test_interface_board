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

inline bool check_i2c1_isr(void);
inline bool check_i2c2_isr(void);
void check_i2c_and_reset(uint8_t i2c_port);

int main(void) {
  BoardInit();
  TRISEbits.TRISE0 = TRIS_OUT;
  LATEbits.LATE0 = 1;
  EusartInit();
  I2c1ClientInit();
  I2c2ClientInit();
  CvdInit();

  TRISBbits.TRISB0 = TRIS_OUT;
  LATBbits.LATB0 = 0;

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
  while (1) {
    DelayMs(20);
    if (display_wait_counter > 50) {
      display_wait_counter = 0;
      DisplayAddStr("*");
      GlobalInterruptEnable(false);
      check_i2c_and_reset(1);
      check_i2c_and_reset(2);
      GlobalInterruptEnable(true);
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

  if (I2c1ClientIsActive()) {
    caught = check_i2c1_isr();
  } else if (I2c2ClientIsActive()) {
    caught = check_i2c2_isr();
  } else {
    caught = check_i2c1_isr() || check_i2c2_isr();
    // eusart interrupt
    if (PIR3bits.U1TXIF &&
        PIE3bits.U1TXIE) {  // If interrupt enabled and flag is set
      EusartInterruptHandler();
      caught = true;
    }
  }
  if (!caught) {
    //      LATCbits.LATC6 = 1;
    //      ee_write(0x79, U1ERRIR);
  }
  GlobalInterruptEnable(true);
  LATBbits.LATB4 = 0;
  LATCbits.LATC6 = 0;
}

inline bool check_i2c1_isr(void) {
  bool caught = false;
  if (PIE3bits.I2C1IE && PIR3bits.I2C1IF) {
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
  return caught;
}

inline bool check_i2c2_isr(void) {
  bool caught = false;
  if (PIE6bits.I2C2IE && PIR6bits.I2C2IF) {
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
  return caught;
}

void check_i2c_and_reset(uint8_t i2c_port) {
  const uint16_t kFixedStateLimit =
      60;  // if the i2c state machine is stuck in a fixed state for more than
           // this number of interrupts, reset it
  static uint16_t i2c1_fixed_state_counter = 0;
  static uint8_t i2c1_success_count = 0;
  if (i2c_port == 1) {
    if (I2c1ClientSuccessCountGet() == i2c1_success_count) {
      if (i2c1_fixed_state_counter >= kFixedStateLimit) {
        DisplayAddStr("$i2c1 reset$");
        I2c1ClientInit();
        i2c1_fixed_state_counter = 0;
      } else {
        ++i2c1_fixed_state_counter;
      }
    } else {
      i2c1_success_count = I2c1ClientSuccessCountGet();
      i2c1_fixed_state_counter = 0;
    }
  }

  static uint16_t i2c2_fixed_state_counter = 0;
  static uint8_t i2c2_success_count = 0;
  if (i2c_port == 2) {
    if (I2c2ClientSuccessCountGet() == i2c2_success_count) {
      if (i2c2_fixed_state_counter >= kFixedStateLimit) {
        DisplayAddStr("$i2c2 reset$");
        I2c2ClientInit();
        i2c2_fixed_state_counter = 0;
      } else {
        ++i2c2_fixed_state_counter;
      }
    } else {
      i2c2_success_count = I2c2ClientSuccessCountGet();
      i2c2_fixed_state_counter = 0;
    }
  }
}
#if 0
  static uint8_t i2c1_last_send_state = 0;
  static uint8_t i2c1_last_receive_state = 0;
    if (I2c1ClientIsActive()) {
      if ((I2c1ClientSendStateGet() == i2c1_last_send_state) &&
          (I2c1ClientReceiveStateGet() == i2c1_last_receive_state)) {
        if (i2c1_fixed_state_counter >= kFixedStateLimit) {
          DisplayAddStr("$i2c1 reset$");
          I2c1ClientInit();
          i2c1_fixed_state_counter = 0;
        } else {
          ++i2c1_fixed_state_counter;
        }
      } else {
        i2c1_fixed_state_counter = 0;
        i2c1_last_send_state = I2c1ClientSendStateGet();
        i2c1_last_receive_state = I2c1ClientReceiveStateGet();
      }
    } else {
      i2c1_fixed_state_counter = 0;
    }
  }
  static uint8_t i2c2_fixed_state_counter = 0;
  static uint8_t i2c2_last_send_state = 0;
  static uint8_t i2c2_last_receive_state = 0;
  if (i2c_port == 2) {
    if (I2c2ClientIsActive()) {
      if ((I2c2ClientSendStateGet() == i2c2_last_send_state) &&
          (I2c2ClientReceiveStateGet() == i2c2_last_receive_state)) {
        if (i2c2_fixed_state_counter >= kFixedStateLimit) {
          DisplayAddStr("$i2c2 reset$");
          I2c2ClientInit();
          i2c2_fixed_state_counter = 0;
        } else {
          ++i2c2_fixed_state_counter;
        }
      } else {
        i2c2_fixed_state_counter = 0;
        i2c2_last_send_state = I2c2ClientSendStateGet();
        i2c2_last_receive_state = I2c2ClientReceiveStateGet();
      }
    } else {
      i2c2_fixed_state_counter = 0;
    }
  }
}
#endif
