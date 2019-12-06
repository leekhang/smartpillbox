/* Helper Functions for ADC, Timers, and LCD Touchscreen */

#ifndef __LCD_H__
#define __LCD_H__

#include "SSD2119.h"
#include "main.h"

void Screen_Init(void);
void Screen_Print_Name(int);
void Screen_Print_Time(int);
void LCD_DrawFilledRoundedRect(unsigned short, unsigned short, short, short, unsigned short, unsigned short);
void Screen_Remind(int);
unsigned long Done_Pressed(void);

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
  LCD_SetCursor(22 + i*104 + 10, 100);
  if (medArray[i].index != -1) {
    LCD_PrintString(medArray[i].name);
  } else {
    LCD_PrintString("Empty");
  }
  
}

void Screen_Print_Time(int i) {
  LCD_DrawFilledRect(10*(i+1) + 94*i + 18, 112, 60, 18, Color4[15]);
  LCD_SetTextColor(0x00, 0xD9, 0xEA); // dark text
  LCD_SetCursor(10*(i+1) + 94*i + 24, 100+18);
  if (medArray[i].index != -1) {
    LCD_PrintString(medArray[i].time);
  } else {
    LCD_PrintString("--------");
  }
}

// int Med_Name_Length(int i) {
//   char * name = medArray[i].name;
//   int len = 0;
//   for (int j = 0; j < 15; j++) {
//     if (name[i] >= 65 && name[i] <= 122) len++;
//     else break;
//   }
//   return len;
// }

void Screen_Remind(int i) {
  LCD_ColorFill(Color4[15]); // white background
  LCD_DrawFilledRoundedRect(10, 10, (LCD_WIDTH-20), (LCD_HEIGHT-20), 10, convertColor(0x00, 0xF0, 0xEA));
  
  LCD_SetTextColor(0xFF, 0xFF, 0xFF); // white text
  LCD_SetCursor(105, 90);
  LCD_PrintString("Time To Take Your:");

  LCD_SetTextColor(0x00, 0xD9, 0xEA); // dark text
  LCD_DrawFilledRect(150-16-6, 104, 60, 18, Color4[15]);
  LCD_SetCursor(150-16, 108);
  LCD_PrintString(medArray[i].name);

  LCD_SetTextColor(0xFF, 0xFF, 0xFF); // white text
  LCD_SetCursor(135, 126);
  LCD_PrintString("Medicine");

  LCD_DrawFilledRoundedRect((LCD_WIDTH/2-40), 160, 80, 40, 6, 0);
  LCD_SetCursor((LCD_WIDTH/2-12), 176);
  LCD_PrintString("DONE");
}

// function checks if the DONE button is tapped.
unsigned long Done_Pressed(void) {
  Touch_ReadX(); Touch_ReadY(); // get values from touchscreen
  long coords = Touch_GetCoords(); // compute coordinates
  long xPos = coords >> 16; // extract x position of touch event
  long yPos = coords & 0xFFFF; // extract y posistion of touch event
  return (xPos >= 100 && xPos <= 175 && yPos >= 140 && yPos <= 210); // check if in bounding box
}

#endif