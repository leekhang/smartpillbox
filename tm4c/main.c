#include <stdint.h>

#include "mcheader.h"
#include "SSD2119.h"
#include "SSD2119.c"

#include "main.h"
#include "LED.h"
#include "LCD.h"

#include "lab5.c"

int main() {
  // lab5();
  strcpy(medArray[0].name, "Ibuprofen");
  strcpy(medArray[0].time, "10:30 PM");

  strcpy(medArray[1].name, "Diazepam");
  strcpy(medArray[1].time, "02:30 PM");

  strcpy(medArray[2].name, "Tylenol");
  strcpy(medArray[2].time, "06:30 AM");

  LCD_Init();
  delay();
  Screen_Init();


  
  while(1) {
  
  }
  
  return 0;
}

/* This is the ISR for the ADC0 module. Here, you will read the ADC
conversion value and calculate the temperature of the internal temperature sensor. Make
sure to clear the ADC interrupt flag after each conversion. */
// void ADC0_Handler() {

//   char char_output[8];
//   sprintf(char_output, "%.2f\n\r", value);
//   for (int i = 0; i < 8; i++) {
//     while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy
//     UARTDR_0 = char_output[i];
//     while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy
//   }
//   // ----

//   ADCISC_0 |= 0x8; // clear the interrupt
//   GPTMICR_T0_1632 |= 0x1; // reset the timer
// }