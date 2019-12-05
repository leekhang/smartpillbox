/* Timer Helper Functions */

#include "mcheader.h"

#ifndef __TIMERS_H__
#define __TIMERS_H__


void Timers_Init();

void Timer_Start(int timer, unsigned long count);
void Timer0_Start(unsigned long count);
void Timer1_Start(unsigned long count);
void Timer2_Start(unsigned long count);

int Timer_IsDone(int timer);
int Timer0_IsDone();
int Timer1_IsDone();
int Timer2_IsDone();

void Timer_Restart(int timer);
void Timer0_Restart();
void Timer1_Restart();
void Timer2_Restart();

// This function initializes three timers. It should be run once.
void Timers_Init()
{
  // turn on clock for wide 32/64 timers
  RCGCTIMER |= RCGCTIMER_T0;
  RCGCTIMER |= RCGCTIMER_T1;
  RCGCTIMER |= RCGCTIMER_T2;

  // disable timer A
  GPTMCTL_T0_1632 = 0x0;
  GPTMCTL_T1_1632 = 0x0;
  GPTMCTL_T2_1632 = 0x0;

  // set 64-bit mode on 32/64 bit timer
  GPTMCFG_T0_1632 &= ~0x1;
  GPTMCFG_T1_1632 &= ~0x1;
  GPTMCFG_T2_1632 &= ~0x1;

  // set as countdown and periodic timer
  GPTMTAMR_T0_1632 |= 0x02;
  GPTMTAMR_T1_1632 |= 0x02;
  GPTMTAMR_T2_1632 |= 0x02;

  // clear timer complete indicator
  GPTMICR_T0_1632 |= 0x01;
  GPTMICR_T1_1632 |= 0x01;
  GPTMICR_T2_1632 |= 0x01;
}

// This sets the timer to the count passed in and starts the countdown.
void Timer0_Start(unsigned long count)
{
  GPTMCTL_T0_1632 &= ~0x0101; // disable timer A and B
  GPTMICR_T0_1632 |= 0x1;
  GPTMTAILR_T0_1632 = count; // set timer to count
  GPTMCTL_T0_1632 |= 0x0101; // enable timer A and B
}

// This sets the timer to the count passed in and starts the countdown.
void Timer1_Start(unsigned long count)
{
  GPTMCTL_T1_1632 &= ~0x0101; // disable timer A and B
  GPTMICR_T1_1632 |= 0x1;
  GPTMTAILR_T1_1632 = count;  // set timer to count
  GPTMCTL_T1_1632 |= 0x0101;  // enable timer A and B
}

// This sets the timer to the count passed in and starts the countdown.
void Timer2_Start(unsigned long count)
{
  GPTMCTL_T2_1632 &= ~0x0101; // disable timer A and B
  GPTMICR_T2_1632 |= 0x1;
  GPTMTAILR_T2_1632 = count;  // set timer to count
  GPTMCTL_T2_1632 |= 0x0101;  // enable timer A and B
}

// This sets the timer to the count passed in and starts the countdown.
void Timer_Start(int timer, unsigned long count)
{
  switch (timer)
  {
    case 0: Timer0_Start(count); break;
    case 1: Timer1_Start(count); break;
    case 2: Timer2_Start(count); break;
  }
}

// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer0_IsDone() { return (GPTMRIS_T0_1632 & 0x1); }

// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer1_IsDone() { return (GPTMRIS_T1_1632 & 0x1); }

// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer2_IsDone() { return (GPTMRIS_T2_1632 & 0x1); }

// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer_IsDone(int timer) {
  int out = 0;
  switch (timer) {
    case 0: out = Timer0_IsDone(); break;
    case 1: out = Timer1_IsDone(); break;
    case 2: out = Timer2_IsDone(); break;
  }
  return out;
}

// This clears the timer complete indicator, which restarts the timer
void Timer0_Restart() { GPTMICR_T0_1632 |= 0x1; }

// This clears the timer complete indicator, which restarts the timer
void Timer1_Restart() { GPTMICR_T1_1632 |= 0x1; }

// This clears the timer complete indicator, which restarts the timer
void Timer2_Restart() { GPTMICR_T2_1632 |= 0x1; }

// This clears the timer complete indicator, which restarts the timer
void Timer_Restart(int timer) {
  
  switch (timer) {
    case 0: Timer0_Restart(); break;
    case 1: Timer1_Restart(); break;
    case 2: Timer2_Restart(); break;
  }
}

#endif