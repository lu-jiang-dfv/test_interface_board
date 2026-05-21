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
//#include "code_base/drivers/nano_pic18f47k42/i2c2.h"
#include "code_base/libs/dfv_i2c_registers.h"
#include "code_base/libs/display.h"

uint8_t e[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
  I2cClientInit(0);
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

  TRISBbits.TRISB1 = TRIS_IN;
  TRISBbits.TRISB2 = TRIS_IN;

  TRISBbits.TRISB4 = TRIS_OUT;
  LATBbits.LATB4 = 0;

  TRISCbits.TRISC6 = TRIS_OUT;
  LATCbits.LATC6 = 0;

//  ee_write(0x79, 0);

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

  uint16_t counter = 0;
  while(1) {
    DelayMs(20);
    // if (counter > 10) {
    //   counter = 0;
    //   DisplayAddStr("*");
    //   PetWatchDog();
    // } else {
    //   DisplayOneItem();
    //   counter++;
    // }
    if (counter > 100) {
      counter = 0;
      // DisplayAddNum8(PIE0);
      // DisplayAddNum8(PIE1);
      // DisplayAddNum8(PIE2);
      // DisplayAddNum8(PIE3);
      // DisplayAddNum8(PIE4);
      // DisplayAddNum8(PIE5);
      // DisplayAddNum8(PIE6);
      // DisplayAddNum8(PIE7);
      // DisplayAddNum8(PIE8);
      // DisplayAddNum8(PIE9);
      // DisplayAddNum8(PIE10);
      DisplayAddNum8(I2C1CON1);
      DisplayAddNum8(I2C2STAT0);
      DisplayAddNum8(I2C1STAT1);
      DisplayAddNum8(I2C1ERR);
      DisplayAddStr("$");
    } else {
      DisplayOneItem();
      counter++;
    }
    PetWatchDog();
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
//  if (CheckUsartTxIntEnabled() &&
//      CheckUsartTxIntFlag()) {  // If interrupt enabled and flag is set
//  if (PIR3bits.U1TXIF) {  // If interrupt enabled and flag is set
//    if (!I2cClientIsActive()) {
  if (PIR3bits.U1TXIF && PIE3bits.U1TXIE) {  // If interrupt enabled and flag is set
      PIR3bits.U1TXIF = 0;  // Clear the interrupt flag
      EusartInterruptHandler();
      caught = true;
//    }
  }

  if (PIE3bits.I2C1IE && PIR3bits.I2C1IF)  {
    I2cClientIsr();
    caught = true;
  } else if (PIE3bits.I2C1TXIE && PIR3bits.I2C1TXIF) {
    I2cClientIsr();
    caught = true;
  } else if (PIE2bits.I2C1RXIE && PIR2bits.I2C1RXIF) {
    I2cClientIsr();
    caught = true;
  } else if (PIE3bits.I2C1EIE && PIR3bits.I2C1EIF) {
    I2cClientErrorIsr();
    caught = true;
  }
    // if(PIE6bits.I2C2EIE == 1 && PIR6bits.I2C2EIF == 1)
    // {
    //     I2C2_ISR();
    //     caught = true;
    //   }
    // else if(PIE5bits.I2C2RXIE == 1 && PIR5bits.I2C2RXIF == 1)
    // {
    //     I2C2_ISR();
    //     caught = true;
    // }
    // else if(PIE6bits.I2C2IE == 1 && PIR6bits.I2C2IF == 1)
    // {
    //     I2C2_ISR();
    //     caught = true;
    // }
    // else if(PIE5bits.I2C2TXIE == 1 && PIR5bits.I2C2TXIF == 1)
    // {
    //     I2C2_ISR();
    //     caught = true;
    // }
  
  if (!caught) {
//      LATCbits.LATC6 = 1;
//      ee_write(0x79, U1ERRIR);
  }
  GlobalInterruptEnable(true);
  LATBbits.LATB4 = 0;
  LATCbits.LATC6 = 0;
}
