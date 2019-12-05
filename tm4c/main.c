#include <stdint.h>
#include <math.h>

#include "mcheader.h"
#include "main.h"
#include "LED.h"
#include "SSD2119.h"
#include "SSD2119.c"
#include "LCD.h"
#include "lab5.c"

#define DATA_LENGTH 36
#define NAME_LENGTH 15
#define TIME_LENGTH 9
#define TIMEREM_LENGTH 14

void printChar(char);
void printString(char*);
char readChar(void);
void readData(char*);
void readName(char*, char*);
void readTime(char*, char*);
void readTimeRem(char*, char*);

int main() {
  LCD_Init();
  UART_Init();
  delay();

  for (int i = 0; i < 3; i++) {
    strcpy(medArray[i].name, "");
    strcpy(medArray[i].time, "--------");
    medArray[i].index = -1;
  }

  int inputIndex, deleteIndex;
  char name[15];
  char time[9];
  char timeRemChar[14];
  char data[37];
  
  unsigned long long int timeRem, digit;
  unsigned long long int mult = 1;
  char signal;

  Screen_Init();

  while(1) {
    signal = readChar();
    if (signal == 37) {

      readData(data);
      inputIndex = ((int) data[0]) - 48;
      medArray[inputIndex].index = inputIndex;

      readName(name, data);
      readTime(time, data);
      readTimeRem(timeRemChar, data);
      strcpy(medArray[inputIndex].name, name);
      strcpy(medArray[inputIndex].time, time);

      // LCD_PrintString("Index:"); LCD_PrintInteger(medArray[inputIndex].index); LCD_PrintString("\n\r");
      // LCD_PrintString("Name:"); LCD_PrintString(medArray[inputIndex].name); LCD_PrintString("\n\r");
      // LCD_PrintString("Time:"); LCD_PrintString(medArray[inputIndex].time); LCD_PrintString("\n\r");
      // LCD_PrintString("TimeRemChar:"); LCD_PrintString(timeRemChar); LCD_PrintString("\n\r");
      
      timeRem = 0; mult = 1;
      for (int i = 12; i >= 0; i--) {
        digit = ((unsigned long long int) timeRemChar[i]) - 48;
        if (digit && digit <= 9) {
          digit *= mult;
          mult *= 10;              
        } else { 
          digit = 0;
        }
        timeRem += digit;
      }
      medArray[inputIndex].timeRem = timeRem;
      strcpy(name, "");
      strcpy(data, "");
      // unsigned long right = (unsigned long) timeRem;
      // unsigned long left = (unsigned long) (timeRem >> 32);
      // LCD_PrintString("T.Rem Val: "); LCD_PrintHex(left,0); LCD_PrintHex(right,0); LCD_PrintString("\n\r");
      
      Screen_Init();
      delay();
      
    } else if (signal == 94) {
      
      deleteIndex = ((int) readChar()) - 48;
      strcpy(medArray[deleteIndex].name, "");
      strcpy(medArray[deleteIndex].time, "");
      medArray[deleteIndex].index = -1;

      Screen_Init();
      delay();
    }
  }
      // LCD_PrintString("Index:"); LCD_PrintInteger(index-48); LCD_PrintString("\n\r");
      // LCD_PrintString("Name:"); LCD_PrintString(name); LCD_PrintString("\n\r");
      // LCD_PrintString("Time:"); LCD_PrintString(time); LCD_PrintString("\n\r");
      // LCD_PrintString("T.Rem:"); LCD_PrintString(timeRemChar); LCD_PrintString("\n\r");
      
      // unsigned long num;
      // unsigned long mult = 1000000000000;
      // timeRem = 0;
      // for (int i = 0; i < 13; i++) {
      //   mult /= i * 10;
      //   num = (timeRemChar[i] != 48) ? mult * (timeRemChar[i]-48) : 0;        
      //   timeRem += num;
      //   LCD_PrintInteger(timeRem); LCD_PrintString(",  ");
      // }
      // LCD_PrintString("\n\r");
      // LCD_PrintString("T.Rem Val: "); LCD_PrintInteger(timeRem); LCD_PrintString("\n\r");

//  lab5();

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

void readData(char* data) {
  for (int i = 0; i < DATA_LENGTH-1; i++) {
    data[i] = readChar();
    if (data[i] == 0) break;
  }
  data[DATA_LENGTH-1] = 0;
}

void readName(char* name, char* data) {
  int i;
  for (i = 0; i < NAME_LENGTH-1; i++) {
    if (data[i+1] == 32) break;
    name[i] = data[i+1];
  }
  name[i] = 0;
}

void readTime(char* time, char*data) {
  for (int i = 0; i < TIME_LENGTH-1; i++) time[i] = data[i+15];
  time[TIME_LENGTH-1] = 0;
}

void readTimeRem(char* timeRemChar, char* data) {
  for (int i = 0; i < TIMEREM_LENGTH-1; i++) timeRemChar[i] = data[i+23];
  timeRemChar[TIMEREM_LENGTH-1] = 0;
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