#ifndef __LED_H__
#define __LED_H__

#include "mcheader.h"
#include <stdint.h>

void PWM_Init();

void LED0_On(); void LED0_Off(); void LED0_Set(int);
void LED1_On(); void LED1_Off(); void LED1_Set(int);
void LED2_On(); void LED2_Off(); void LED2_Set(int);
void LED_On(int); void LED_Off(int); void LED_Set(int, int);
void LED_AllOff();


// Initializes PWM for M1PWM4, M1PWM6, M1PWM7
// PWM outputs are PF0, PF2, PF3
void PWM_Init() {
  RCGCPWM |= 0x2; // turn on PWM 1
  RCGCGPIO |= RCGCGPIO_F; // enable port F
  GPIOAFSEL_F |= 0xD; // enable pins 0, 2, 3

  // I don't know if the next four lines are necessary
  GPIOLOCK_F = GPIOLOCK_OPEN; // allow write to GPIOCR
  GPIOCR_F |= 0xD; // allow write to PF0, PF2, PF3
  GPIODIR_F |= 0xD; // set PF0, PF2, PF3 as outputs
  GPIODEN_F = 0xD; // set pins as digital

  GPIOPCTL_F &= ~0xFF0F; // reset PF0, PF2, PF3
  GPIOPCTL_F |= 0x5505; // configure PF0, PF2, PF3 for PWM
  RCC &= ~0x00100000; // don't divide PWM (USEPWMDIV)

  // configure PWM generators for countdown mode with immediate updates to the parameters
  PWM2CTL_1 = 0x00000000;
  PWM3CTL_1 = 0x00000000;
  PWM2GENA_1 = 0x0000008C; // turn on at load and off at A value
  PWM3GENA_1 = 0x0000008C; // turn on at load and off at A value
  PWM2GENB_1 = 0x0000080C; // turn on at load and off at B value
  PWM3GENB_1 = 0x0000080C; // turn on at load and off at B value
  
  PWM2LOAD_1 = 127; // period of PWM clock /128
  PWM3LOAD_1 = 127; // period of PWM clock /128
  PWM2CMPA_1 = 127; // full-width pulse
  PWM3CMPA_1 = 127; // full-width pulse
  PWM2CTL_1 |= 0x1; // start PWM timer
  PWM3CTL_1 |= 0x1; // start PWM timer
}

// turn on/off LEDs
void LED0_On()  { PWMENABLE_1 |= (1 << 4); }
void LED0_Off() { PWMENABLE_1 &= ~(1 << 4); }
void LED1_On()  { PWMENABLE_1 |= (1 << 6); }
void LED1_Off() { PWMENABLE_1 &= ~(1 << 6); }
void LED2_On()  { PWMENABLE_1 |= (1 << 7); }
void LED2_Off() { PWMENABLE_1 &= ~(1 << 7); }

void LED_On(int i) {
  switch (i)
  {
    case 0: LED0_On(); break;
    case 1: LED1_On(); break;
    case 2: LED2_On(); break;
  }
}

void LED_Off(int i) {
  switch (i)
  {
    case 0: LED0_Off(); break;
    case 1: LED1_Off(); break;
    case 2: LED2_Off(); break;
  }
}

// set PWM level between 127 (on) and 0 (off)
void LED0_Set(int level) { PWM2CMPA_1 = level; PWM3CMPA_1 = level; }
void LED1_Set(int level) { PWM2CMPA_1 = level; PWM3CMPA_1 = level; }
void LED2_Set(int level) { PWM2CMPA_1 = level; PWM3CMPA_1 = level; }

void LED_Set(int i, int level) {
  switch (i)
  {
    case 0: LED0_Set(level); break;
    case 1: LED1_Set(level); break;
    case 2: LED2_Set(level); break;
  }
}

#endif