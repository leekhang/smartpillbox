#include <stdint.h>
#include <math.h>

#include "mcheader.h"
#include "main.h"
#include "LED.h"
#include "SSD2119.h"
#include "SSD2119.c"
#include "LCD.h"
#include "lab5.c"

void printChar(char);
void printString(char*);
char readChar(void);
// char* readString(void);
void readName(char*);
void readTime(char*);
void readTimeRem(char*);


int main() {
//  strcpy(medArray[0].name, "Ibuprofen");
//  strcpy(medArray[0].time, "10:30 PM");
//  medArray[0].timeRem = 0x000003FF;
//  
//  strcpy(medArray[1].name, "Diazepam");
//  strcpy(medArray[1].time, "02:30 PM");
//  medArray[1].timeRem = 0x000003FF;
//  
//  strcpy(medArray[2].name, "Tylenol");
//  strcpy(medArray[2].time, "06:30 AM");
//  medArray[2].timeRem = 0x000003FF;
  
  LCD_Init();
  LCD_SetCursor(0,0);
  LCD_SetTextColor(0xFF, 0xFF, 0xFF);
  LCD_ColorFill(0);
  UART_Init();
  delay();

  char name[15];
  char time[9];
  unsigned long timeRem = 0;

  while(1) {
    char signal = readChar();
    if (signal == 37) {
      readName(name);
      LCD_PrintString(name); LCD_PrintString("\n\r");
      
      readTime(time);
      LCD_PrintString(time); LCD_PrintString("\n\r");
      
      int num;
      char timeRemChar[15];
      readTimeRem(timeRemChar);
      for (int i = ((int) pow(10,12)); i <= 0; i /= 10) {
        num = (timeRemChar[i] != 48) ? i * ascii_convert(timeRemChar[i]) : 0;
        timeRem += (unsigned long) num;
      }
      LCD_PrintInteger(timeRem);
      LCD_PrintString("\n\r");
    }
    
  }

  lab5();

  return 0;
}

/* This is the ISR for the ADC0 module. Here, you will read the ADC
conversion value and calculate the temperature of the internal temperature sensor. Make
sure to clear the ADC interrupt flag after each conversion. */
void UART_Handler() {
  
}

char readChar(void) {
  char c;
  while ((UARTFR_0 & (1<<4)) != 0);
  c = UARTDR_0;
  return c;
}

void readName(char* name) {
  char c[15];
  for (int i = 0; i < 15; i++) name[i] = readChar();
}

void readTime(char* time) {
  for (int i = 0; i < 9; i++) time[i] = readChar();
}

void readTimeRem(char* timeRemChar) {
  for (int i = 0; i < 15; i++) timeRemChar[i] = readChar();
}

void printChar(char c) {
  while ((UARTFR_0 & (1<<5)) != 0);
  UARTDR_0 = c;
}

void printString(char * str) {
  while (*str) {
    printChar(*(str++));
  }
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