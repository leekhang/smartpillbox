/* Helper Functions for ADC, Timers, and LCD Touchscreen */

#ifndef __LCD_H__
#define __LCD_H__

#include "main.h"
#include "SSD2119.h"

int Med_Name_Length(int);
void Screen_Print_Name(int);
void Screen_Print_Time(int);
void LCD_DrawFilledRoundedRect(unsigned short, unsigned short, short, short, unsigned short, unsigned short);
void Screen_Remind(int);

// Function initializes the LCD screen
void Screen_Init() {
  // unsigned short brand = convertColor(0x00, 0xD9, 0xEA);
  // unsigned short brand = convertColor(0x00, 0x85, 0xFF);
  LCD_ColorFill(Color4[15]); // white background
  
  for (int i = 0; i < 3; i++) {
    LCD_DrawFilledRoundedRect(10+104*i, 10, 94, (LCD_HEIGHT-20), 10, convertColor(0x00, 0xD9, 0xEA));
    Screen_Print_Name(i);
    Screen_Print_Time(i);
  }

  // Initialize the button pressing
  // SS_NORMAL(); // draw start/stop button
  // PED_NORMAL(); // draw pedestrian button
}

void LCD_DrawFilledRoundedRect(unsigned short x, unsigned short y, short w, short h, unsigned short rad, unsigned short color) {
  LCD_DrawFilledCircle(x+rad, y+rad, rad, color); // fill top-left corner
  LCD_DrawFilledCircle(x+rad, y+h-rad, rad, color); // fill top-right corner
  LCD_DrawFilledCircle(x+w-rad, y+rad, rad, color); // fill bottom-left corner
  LCD_DrawFilledCircle(x+w-rad, y+h-rad, rad, color); // fill bottom right corner
  
  LCD_DrawFilledRect(x+rad, y, w-2*rad, rad, color); // fill top edge
  LCD_DrawFilledRect(x, y+rad, rad, h-2*rad, color); // fill left edge
  LCD_DrawFilledRect(x+w-rad, y+rad, rad, h-2*rad, color); // fill right edge
  LCD_DrawFilledRect(x+rad, y+h-rad, w-2*rad, rad, color); // fill bottom edge

  LCD_DrawFilledRect(x+rad, y+rad, w-2*rad, h-2*rad, color); // fill main body
}

void Screen_Print_Name(int i) {
  LCD_SetTextColor(0xFF, 0xFF, 0xFF); // white text
  int count = 14 - Med_Name_Length(i);
  LCD_SetCursor(22 + i*104 + 2*count, 100);
  LCD_PrintString(medArray[i].name);
}

void Screen_Print_Time(int i) {
  LCD_DrawFilledRect(10*(i+1) + 94*i + 18, 112, 60, 18, Color4[15]);
  LCD_SetTextColor(0x00, 0xD9, 0xEA); // dark text
  LCD_SetCursor(10*(i+1) + 94*i + 24, 100+18);
  LCD_PrintString(medArray[i].time);
}

int Med_Name_Length(int i) {
  char * name = medArray[i].name;
  int len = 0;
  while (name[len] != 0) len++;
  return len;
}

void Screen_Remind(int i) {
  LCD_ColorFill(Color4[15]); // white background
  LCD_DrawFilledRoundedRect(10, 10, (LCD_WIDTH-20), (LCD_HEIGHT-20), 10, convertColor(0x00, 0xF0, 0xEA));
  
  LCD_SetTextColor(0xFF, 0xFF, 0xFF); // white text
  LCD_SetCursor(105, 90);
  LCD_PrintString("Time To Take Your:");

  LCD_SetTextColor(0x00, 0xD9, 0xEA); // dark text
  int count = Med_Name_Length(i);
  LCD_DrawFilledRect(150-2*count-6, 104, count*7+4, 18, Color4[15]);
  LCD_SetCursor(150-2*count, 108);
  LCD_PrintString(medArray[i].name);

  LCD_SetTextColor(0xFF, 0xFF, 0xFF); // white text
  LCD_SetCursor(135, 126);
  LCD_PrintString("Medicine");
}

// Functions to turn on and off lights on screen
void RED_ON() { LCD_DrawFilledCircle(55, 55,  30, Color4[12]); }
void RED_OFF() { LCD_DrawFilledCircle(55, 55,  30, Color4[8]); }
void YELLOW_ON() { LCD_DrawFilledCircle(55, 120, 30, Color4[14]); }
void YELLOW_OFF() { LCD_DrawFilledCircle(55, 120, 30, Color4[8]); }
void GREEN_ON() { LCD_DrawFilledCircle(55, 185, 30, Color4[10]); }
void GREEN_OFF() { LCD_DrawFilledCircle(55, 185, 30, Color4[8]); }

// Functions to turn on and off buttons on screen
void SS_NORMAL() { LCD_DrawFilledRect(205, 10, 105, 105, 0); }
void SS_TOUCH() { LCD_DrawFilledRect(205, 10, 105, 105, Color4[7]); }
void PED_NORMAL() { LCD_DrawFilledRect(205, 125, 105, 105, 0); }
void PED_TOUCH() { LCD_DrawFilledRect(205, 125, 105, 105, Color4[7]); }

// Reads the pedestrian button touch input
unsigned long PED_IN(void) {
  Touch_ReadX(); Touch_ReadY(); // get values from touchscreen
  long coords = Touch_GetCoords(); // compute coordinates
  long xPos = coords >> 16; // extract x position of touch event
  long yPos = coords & 0xFFFF; // extract y posistion of touch event
  return (xPos >= 50 && xPos <= 150 && yPos >= 120 && yPos <= 210); // check if in bounding box
}

// Reads the start/stop button touch input
unsigned long SS_IN(void) {
  Touch_ReadX(); Touch_ReadY(); // get values from touchscreen
  long coords = Touch_GetCoords(); // compute coordinates
  long xPos = coords >> 16; // extract x position of touch event
  long yPos = coords & 0xFFFF; // extract y posistion of touch event
  return (xPos >= 50 && xPos <= 150 && yPos >= 30 && yPos <= 120); // check if in bounding box
}

#endif