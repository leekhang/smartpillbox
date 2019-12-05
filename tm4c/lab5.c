#include <stdint.h>
#include "mcheader.h"
#include "main.h"
#include "timers.h"

void UART_Init(void);
void lab5();
void MC_Init();
void FSM();
void Handle_TimeUp(int);
void Handle_TimeUpRepeat(int);
int SerialHasInput(void);

// program current state
enum State curr_state;
// program next state
enum State next_state;

// one day in clock cycles at 16MHz
#define TWENTY_FOUR_HOURS (unsigned long) 16000000 * 60 * 60 * 24

void lab5() {
  MC_Init();

  while (1) {
    FSM();
  }
}

// set up everything
void MC_Init() {
  Timers_Init();
  PWM_Init();
  Touch_Init();
  LCD_Init();
  UART_Init();
}

// handle I/O and get next state
void FSM() {
  int t;
  switch (curr_state) {
    case READY:
      // serial input handler
      if (SerialHasInput()) next_state = RECEIVE_DATA;
      // timer handlers
      for (int i = 0; i < 3; i++) {
        if (Timer_IsDone(i)) {
          if (medArray[i].timeRem < TWENTY_FOUR_HOURS) {
            next_state = TIMEUP[i];
          } else {
            next_state = TIMEUP_REPEAT[i];
          }
          Screen_Remind(i);
          LED_On(i);
        }
      }
      break;

    case RECEIVE_DATA:
      next_state = READY;
      // TODO: load data
      // eg. i received
      // update medArray[i]
      // Timer_Start(i);
      // Screen_Init();
      break;

    case TIMEUP0: next_state = DONE; Handle_TimeUp(0); break;
    case TIMEUP1: next_state = DONE; Handle_TimeUp(1); break;
    case TIMEUP2: next_state = DONE; Handle_TimeUp(2); break;

    case TIMEUP0_REPEAT: next_state = DONE; Handle_TimeUpRepeat(0); break;
    case TIMEUP1_REPEAT: next_state = DONE; Handle_TimeUpRepeat(1); break;
    case TIMEUP2_REPEAT: next_state = DONE; Handle_TimeUpRepeat(2); break;

    case DONE:
      next_state = READY;
      Screen_Init();
      LED_AllOff();
      break;

    default:
      next_state = READY;
      break;
  }
  curr_state = next_state;
}

void Handle_TimeUp(int timer) {
  Timer_Start(timer, TWENTY_FOUR_HOURS);
  medArray[timer].timeRem = (unsigned long) TWENTY_FOUR_HOURS;
  Screen_Remind(timer);
  LED_On(timer);
}

void Handle_TimeUpRepeat(int timer) {
  Timer_Restart(timer);
  Screen_Remind(timer);
  LED_On(timer);
}

// TODO
int SerialHasInput() {
  return 0;
}