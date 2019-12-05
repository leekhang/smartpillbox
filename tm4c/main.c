#include <stdint.h>

#include "mcheader.h"
#include "main.h"
#include "LED.h"
#include "SSD2119.h"
#include "SSD2119.c"
#include "LCD.h"
#include "lab5.c"

int main() {
  strcpy(medArray[0].name, "Ibuprofen");
  strcpy(medArray[0].time, "10:30 PM");
  medArray[0].timeRem = 0x000003FF;
  
  strcpy(medArray[1].name, "Diazepam");
  strcpy(medArray[1].time, "02:30 PM");
  medArray[1].timeRem = 0x000003FF;
  
  strcpy(medArray[2].name, "Tylenol");
  strcpy(medArray[2].time, "06:30 AM");
  medArray[2].timeRem = 0x000003FF;

  LCD_ColorFill(0);
  delay();
  LCD_SetCursor(0,0);

  while(1) {
    UART_Handler();
  }

  lab5();

  return 0;
}

/* This is the ISR for the ADC0 module. Here, you will read the ADC
conversion value and calculate the temperature of the internal temperature sensor. Make
sure to clear the ADC interrupt flag after each conversion. */
void UART_Handler() {
  char test[4];
  char output[8];
  for (int i = 0; i < 4; i++) {
    while ((UARTFR_0 & 0x10) != 0x0); // wait till receiver is available.
    test[i] = UARTDR_0;
  }
  LCD_PrintString("Output:");
  LCD_PrintString(test);
  sprintf(output, "%s \n\r", test); // format as char array
  LCD_PrintString(output); // print string
}

void UART_Handler2() {
   char name[14]; char time[8]; unsigned long timeRem = 0x0000;
   for (int i = 0; i < 14; i++) {
     while ((UARTFR_0 & 0x8) != 0x0); // wait till receiver is available.
    //  while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
     name[i] = UARTDR_0;
   }
   for (int i = 0; i < 8; i++) {
     while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy.
    //  while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
     time[i] = UARTDR_0;
   }
   for (int i = 0; i < 4; i++) {
     while ((UARTFR_0 & 0x8) != 0x0); // wait till not busy.
    //  while ((UARTFR_0 & 0x40) != 0x0); // wait till receiver is available.
     timeRem += UARTDR_0 << i*8;
   }
   strcpy(medArray[0].name, name);
   strcpy(medArray[0].time, time);
//   strcpy(medArray[0].timeRem, timeRem);
}

// sprintf(output, "OVERRUN ERR: %02d\r\n", (UART_RSR_ECR_0 & 0x8));
// LCD_PrintString(output);
// delay();
// sprintf(output, "BREAK ERR:   %02d\r\n", (UART_RSR_ECR_0 & 0x4));
// LCD_PrintString(output);
// delay();
// sprintf(output, "PARITY ERR:  %02d\r\n", (UART_RSR_ECR_0 & 0x2));
// LCD_PrintString(output);
// delay();
// sprintf(output, "FRAMING ERR: %02d\r\n", (UART_RSR_ECR_0 & 0x1));
// LCD_PrintString(output);
// delay();
// delay();
// delay();