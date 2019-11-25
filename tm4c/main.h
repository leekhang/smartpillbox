#ifndef __MAIN_H__
#define __MAIN_H__

#include "SSD2119.h"

void delay();

struct Med {
    char name[14];
    char time[8];
    unsigned long timeRem;
};

struct Med medArray[3];

void delay() { for (int i = 0; i < 1000000; i++); }

#endif