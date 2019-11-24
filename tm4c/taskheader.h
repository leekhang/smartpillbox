#ifndef __LAB5_H__
#define __LAB5_H__

#include "mcheader.h"
#include <stdint.h>

// variables used in both tasks
typedef enum {SLOW, MED, FAST} Switch;
Switch cur_state = MED, next_state;
double value = 0;

void delay();
void PLL_Init();
void PortF_Init();
void ADC_Init();
void Timer0_Init(unsigned long count);

void RED_ON(); void RED_OFF();
void BLUE_ON(); void BLUE_OFF();
void GREEN_ON(); void GREEN_OFF();
unsigned long SW0(); unsigned long SW1();

/* This function configured the GPIO Port F pins, enabling LEDs and switches. */
void PortF_Init() {
  RCGCGPIO |= RCGCGPIO_F; // turn on port F
  GPIOLOCK_F = GPIOLOCK_OPEN; // allow write to GPIOCR
  GPIOCR_F = 0x1F; // allow write to GPIOPUR on PF0 & PF4
  GPIODIR_F = RGB; // set LEDs as outputs and SW as inputs
  GPIODEN_F = 0x1F; // set all pins as digital
  GPIOPUR_F = 0x11; // attach pull-up resistors to PF0 & PF4
}

/* This function configures the ADC module. */
void ADC_Init() {
  RCGCADC |= 0x1; // enable ADC module 1
  delay(); // set delay after enabling ADC module
  ADCACTSS_0 &= ~0x8; // disable SS3
  ADCEMUX_0 |= 0x5000; // set trigger src for SS3 to timer
  ADCSSMUX3_0 = 0x0; // select sample input
  ADCSSCTL3_0 |= 0xE; // 1st sample, enable interrupt, end of seq.
  EN0 |= 0x20000; // enable interrupt controller for ADC
  ADCIM_0 |= 0x8; // send SS3 interrupt controller
  ADCACTSS_0 |= 0x8; // enable SS3
}

/* This function initializes the timer and configured to trigger the ADC.
   A maximum counter value is passed in as a variable. */
void Timer0_Init(unsigned long count) {
  RCGCTIMER |= RCGCTIMER_T0; // turn on timer 0
  GPTMCTL_T0_1632 &= 0xFFFFFFFE; // disable timer A only
  GPTMCFG_T0_1632 &= 0x0; // set 32 bit mode on 16/32 bit timer
  GPTMTAMR_T0_1632 |= 0x02; // set countdown & periodic timer
  GPTMTAILR_T0_1632 = count; // (0xF42400: 16,000,000)
  GPTMICR_T0_1632 |= 0x01; // clear timer complete indicator
  GPTMCTL_T0_1632 |= 0X20; // enable Timer A trigger ADC
  GPTMCTL_T0_1632 |= 0X01; // enable timer 0
}

/* This function initializes the PLL. */
void PLL_Init() {
  // SETUP
  RCC |= 0x800; // set Bypass for RCC
  RCC2 |= 0x800; // set Bypass for RCC2
  RCC2 |= 0x80000000; // override RCC fields with RCC2
  RCC &= ~0x400000; // disable USESYSDIV
  RCC |= 0x540; // set crystal (16 MHz)
  RCC2 &= ~0x70; // choose main oscillator (RCC override)
  RCC &= ~0x2000; // Activate PLL w/ PWDRN2 (RCC override)
  RCC2 &= ~0x2000; // Activate PLL w/ PWDRN2 (RCC override)
  RCC2 |= 0x40000000; //set DIV400 on RCC2
  RCC2 &= ~0x1FC00000; // clear SYSDIV2 (RCC override)
  RCC2 |= 0x6000000; // set SYSDIV2 value (RCC override)
  RCC |= 0x400000; // enable USESYSDI
  // LOCK
  while ((RIS & 0x40) != 0x40); // wait for PLL to lock
  RCC2 &= ~0x800; // clear bypass for RCC2 (use PLL)
  MISC |= 0x40; // clear the interrupt in RIS
}

// turn on red LED
void RED_ON() { GPIODATA_F |= 0x2; }

// turn on blue LED
void BLUE_ON() { GPIODATA_F |= 0x4; }

// turn on green LED
void GREEN_ON() { GPIODATA_F |= 0x8; }

// turn off red LED
void RED_OFF() { GPIODATA_F &= ~0x2; }

// turn off blue LED
void BLUE_OFF() { GPIODATA_F &= ~0x4; }

// turn off green LED
void GREEN_OFF() { GPIODATA_F &= ~0x8; }

// Returns SW0 status
unsigned long SW0() { return !(GPIODATA_F & 0x1); }

// Returns SW1 status
unsigned long SW1() { return !(GPIODATA_F & 0x10); }

void delay() { for (int i = 0; i < 1000000; i++); }

#endif