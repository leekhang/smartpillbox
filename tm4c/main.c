/* Main Function to cycle between lab tasks on the microcontroller */

#include <stdio.h>
#include <stdint.h>
#include "mcheader.h"
#include "taskheader.h"
#include "lab5.c"


int main() {

  lab5();

  return 0;
}

/* This is the ISR for the ADC0 module. Here, you will read the ADC
conversion value and calculate the temperature of the internal temperature sensor. Make
sure to clear the ADC interrupt flag after each conversion. */
void ADC0_Handler() {

  char char_output[8];
  sprintf(char_output, "%.2f\n\r", value);
  for (int i = 0; i < 8; i++) {
    while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy
    UARTDR_0 = char_output[i];
    while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy
  }
  // ----

  ADCISC_0 |= 0x8; // clear the interrupt
  GPTMICR_T0_1632 |= 0x1; // reset the timer
}