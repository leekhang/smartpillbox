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
void interpretData(char*, char*, char*, char*);
void readName(char*, char*);
void readTime(char*, char*);
void readTimeRem(char*, char*);

int main() {
  Touch_Init();
  LCD_Init();
  UART_Init();
  Timers_Init();
  PWM_Init();
  LED_AllOff();
  delay();

  for (int i = 0; i < 3; i++) {
    strcpy(medArray[i].name, "");
    strcpy(medArray[i].time, "--------");
    medArray[i].index = -1;
  }

  int inputIndex, deleteIndex, count = 0;
  char signal;
  char name[15];
  char time[9];
  char timeRemChar[14];
  char data[37];
  
  unsigned long long int timeRem, digit;
  unsigned long long int mult = 1;
  
  Screen_Init();

  while(1) {
    if (count == 3) { 
      lab5();
    } else {
      signal = readChar();
      if (signal == 37) { // add an item (signal: "%")
        readData(data);
        inputIndex = ((int) data[0]) - 48;
        medArray[inputIndex].index = inputIndex;
        interpretData(name, time, timeRemChar, data);

        strcpy(medArray[inputIndex].name, name);
        strcpy(medArray[inputIndex].time, time);
        
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
        
        // LCD_PrintString("Index: "); LCD_PrintInteger(inputIndex); LCD_PrintString("\n\r");
        // LCD_PrintString("Name: "); LCD_PrintString(medArray[inputIndex].name); LCD_PrintString("\n\r");
        // LCD_PrintString("Time: "); LCD_PrintString(medArray[inputIndex].time); LCD_PrintString("\n\r");

        strcpy(name, ""); strcpy(data, "");
        Screen_Init();
        count++;
        
      } else if (signal == 94) { // delete an item (signal: "^")
        
        deleteIndex = ((int) readChar()) - 48;
        strcpy(medArray[deleteIndex].name, "");
        strcpy(medArray[deleteIndex].time, "");
        medArray[deleteIndex].index = -1;
        
        Screen_Init();
        count--;
      }
    }
  }
  return 0;
}

char checkChar(void) {
  char c = ' ';
  if (UARTFR_0 & (1<<4) == 0) c = UARTDR_0;
  return c;
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

void interpretData(char* name, char* time, char* timeRemChar, char* data) {
  readName(name, data);
  readTime(time, data);
  readTimeRem(timeRemChar, data);
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