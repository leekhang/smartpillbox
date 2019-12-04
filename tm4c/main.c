#include <stdint.h>

#include "mcheader.h"
#include "main.h"
#include "LED.h"
#include "SSD2119.h"
#include "SSD2119.c"
#include "LCD.h"
#include "lab5.c"

void UART_Handler();


int main() {
  // lab5();
  // strcpy(medArray[0].name, "Ibuprofen"); strcpy(medArray[0].time, "10:30 PM");
  // strcpy(medArray[1].name, "Diazepam");  strcpy(medArray[1].time, "02:30 PM");
  // strcpy(medArray[2].name, "Tylenol");   strcpy(medArray[2].time, "06:30 AM");
  
  UART_Init();
  LCD_Init();
  delay();
  LCD_ColorFill(0);
  // Screen_Init();

  while(1) {
    UART_Handler();
  }
  
  return 0;
}

/* This is the ISR for the ADC0 module. Here, you will read the ADC
conversion value and calculate the temperature of the internal temperature sensor. Make
sure to clear the ADC interrupt flag after each conversion. */
void UART_Handler() {
//  if (count == 1) LCD_ColorFill(0); // clear screen before writing first row
  LCD_ColorFill(0);
  delay();
  delay();
  LCD_SetCursor(0,0);
  char output[17];
  sprintf(output, "OVERRUN ERR: %02d\r\n", (UART_RSR_ECR_0 & 0x8));
  LCD_PrintString(output);
  delay();
  sprintf(output, "BREAK ERR:   %02d\r\n", (UART_RSR_ECR_0 & 0x4));
  LCD_PrintString(output);
  delay();
  sprintf(output, "PARITY ERR:  %02d\r\n", (UART_RSR_ECR_0 & 0x2));
  LCD_PrintString(output);
  delay();
  sprintf(output, "FRAMING ERR: %02d\r\n", (UART_RSR_ECR_0 & 0x1));
  LCD_PrintString(output);
  delay();
  delay();
  delay();
  delay();
  // char output = (char) UARTDR_0; 
  // LCD_PrintString(&output);
  
  // char test[4];
  // char output[8];
  // for (int i = 0; i < 4; i++) {
  //   while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
  //   LCD_PrintString("Pass 0x40 signal\r\n");
  //   while ((UARTFR_0 & 0x20) != 0x0); // wait till not busy.
  //   LCD_PrintString("Pass 0x20 signal\r\n");
  //   LCD_PrintString(UARTDR_0);
  //   test[i] = UARTDR_0;
  // }
  // sprintf();
  // LCD_PrintString("Output:");

//  LCD_PrintString(test); // print string
  
//  count = (count == MAX_CHARS_Y) ? 1 : count + 1; // increment row counter
  
//   char output[8] = "PRINTING";
//   for (int i = 0; i < 8; i++) {
//     while ((UARTFR_0 & 0x20) != 0x0); // wait till not busy.
// //    UARTDR_0 = output[i];
//   }
  
  // sprintf(output, "%.2f\n\r", temperature); // format as char array
  // LCD_PrintString(output); // print string
  // ADCISC_0 |= 0x8; // clear the interrupt
  // GPTMICR_T0_1632 |= 0x1; // reset the timer
}

void UART_Handler2() {
   char name[14]; char time[8]; unsigned long timeRem = 0x0000;
   for (int i = 0; i < 14; i++) {
     // while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy.
     while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
     name[i] = UARTDR_0;
   }
   for (int i = 0; i < 8; i++) {
     // while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy.
     while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
     time[i] = UARTDR_0;
   }
   for (int i = 0; i < 4; i++) {
     // while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy.
     while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
     timeRem += UARTDR_0 << i*8;
   }
   strcpy(medArray[0].name, name);
   strcpy(medArray[0].time, time);
//   strcpy(medArray[0].timeRem, timeRem);

   ADCISC_0 |= 0x8; // clear the interrupt
   GPTMICR_T0_1632 |= 0x1; // reset the timer
}