#ifndef __MAIN_H__
#define __MAIN_H__

#include "SSD2119.h"

void delay();

// stores name (string), time (string), and time remaining (unsigned long timeRem)
struct Med {
    char name[14];
    char time[8];
    unsigned long timeRem;
};

// array for storing medicine data
struct Med medArray[3];

// program state
enum State {
    READY,
    RECEIVE_DATA,
    TIMEUP0,
    TIMEUP0_REPEAT,
    TIMEUP1,
    TIMEUP1_REPEAT,
    TIMEUP2,
    TIMEUP2_REPEAT,
    DONE
};

// state helper array
enum State TIMEUP[3] = {TIMEUP0, TIMEUP1, TIMEUP2};
enum State TIMEUP_REPEAT[3] = {TIMEUP0_REPEAT, TIMEUP1_REPEAT, TIMEUP2_REPEAT};

void delay() { for (int i = 0; i < 1000000; i++); }

#endif