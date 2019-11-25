#ifndef __LED_H__
#define __LED_H__

#include "mcheader.h"
#include <stdint.h>


void PortA_Init();

void LED0_ON(); void LED0_OFF();
void LED1_ON(); void LED1_OFF();
void LED2_ON(); void LED2_OFF();

// CHANGE THIS TO PORT A FOR LED OUTPUTS
void PortA_Init() {
  RCGCGPIO |= RCGCGPIO_F; // turn on port F
  GPIOLOCK_F = GPIOLOCK_OPEN; // allow write to GPIOCR
  GPIOCR_F = 0x1F; // allow write to GPIOPUR on PF0 & PF4
  GPIODIR_F = RGB; // set LEDs as outputs and SW as inputs
  GPIODEN_F = 0x1F; // set all pins as digital
  GPIOPUR_F = 0x11; // attach pull-up resistors to PF0 & PF4
}

// ADD THIS MODULE!
void PWM_Init() {


}

// CHANGE TO TURN ON / OFF LEDS
// CHANGE TO TURN ON / OFF LEDS
// CHANGE TO TURN ON / OFF LEDS
void LED2_ON() { GPIODATA_F |= 0x2; }
void LED0_OFF() { GPIODATA_F |= 0x2; }
void LED1_OFF() { GPIODATA_F |= 0x2; }
void LED2_OFF() { GPIODATA_F |= 0x2; }



#endif