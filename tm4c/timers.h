#include "mcheader.h"

#ifndef __TIMERS__
#define __TIMERS__


void Timers_Init();

void Timer0_Start(unsigned long count);
void Timer1_Start(unsigned long count);
void Timer2_Start(unsigned long count);

int Timer0_IsDone();
int Timer1_IsDone();
int Timer2_IsDone();

void Timer0_Restart();
void Timer1_Restart();
void Timer2_Restart();

// This function initializes three timers. It should be run once.
void Timers_Init()
{
  // turn on clock for wide 32/64 timers
  RCGCWTIMER |= RCGCWTIMER_T0;
  RCGCWTIMER |= RCGCWTIMER_T1;
  RCGCWTIMER |= RCGCWTIMER_T2;

  // disable timer A and B
  GPTMCTL_T0_3264 &= ~0x0101;
  GPTMCTL_T1_3264 &= ~0x0101;
  GPTMCTL_T2_3264 &= ~0x0101;

  // set 64-bit mode on 32/64 bit timer
  GPTMCFG_T0_3264 &= ~0x1;
  GPTMCFG_T1_3264 &= ~0x1;
  GPTMCFG_T2_3264 &= ~0x1;

  // set as countdown and periodic timer
  GPTMTAMR_T0_3264 |= 0x02;
  GPTMTAMR_T1_3264 |= 0x02;
  GPTMTAMR_T2_3264 |= 0x02;

  // clear timer complete indicator
  GPTMICR_T0_3264 |= 0x01;
  GPTMICR_T1_3264 |= 0x01;
  GPTMICR_T2_3264 |= 0x01;
}

// This sets the timer to the count passed in and starts the countdown.
void Timer0_Start(unsigned long count)
{
  GPTMCTL_T0_3264 &= ~0x0101; // disable timer A and B
  GPTMTAILR_T0_3264 = count; // set timer to count
  GPTMCTL_T0_3264 |= 0x0101; // enable timer A and B
}

// This sets the timer to the count passed in and starts the countdown.
void Timer1_Start(unsigned long count)
{
  GPTMCTL_T1_3264 &= ~0x0101; // disable timer A and B
  GPTMTAILR_T1_3264 = count;  // set timer to count
  GPTMCTL_T1_3264 |= 0x0101;  // enable timer A and B
}

// This sets the timer to the count passed in and starts the countdown.
void Timer2_Start(unsigned long count)
{
  GPTMCTL_T2_3264 &= ~0x0101; // disable timer A and B
  GPTMTAILR_T2_3264 = count;  // set timer to count
  GPTMCTL_T2_3264 |= 0x0101;  // enable timer A and B
}


// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer0_IsDone() { return (GPTMRIS_T0_3264 & 0x1); }

// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer1_IsDone() { return (GPTMRIS_T1_3264 & 0x1); }

// This returns whether or not the timer is done (0 for not done, 1 for done)
int Timer2_IsDone() { return (GPTMRIS_T2_3264 & 0x1); }


// This clears the timer complete indicator, which restarts the timer
void Timer0_Restart() { GPTMICR_T0_3264 |= 0x1; }

// This clears the timer complete indicator, which restarts the timer
void Timer1_Restart() { GPTMICR_T1_3264 |= 0x1; }

// This clears the timer complete indicator, which restarts the timer
void Timer2_Restart() { GPTMICR_T2_3264 |= 0x1; }


#endif