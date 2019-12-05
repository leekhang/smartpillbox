#include <stdint.h>
#include "mcheader.h"
#include "main.h"
#include "timers.h"
#include "LCD.h"
#include "LED.h"

void UART_Init(void);
void lab5();
void MC_Init();
void FSM();
void Handle_TimeUp(int);
void Handle_TimeUpRepeat(int);
void Handle_Done();
void PWM_Pulse();
int SerialHasInput(void);

// program current state
enum State curr_state = READY;
// program next state
enum State next_state = READY;

// duty for PWM Pulse
volatile int duty = PERIOD - 1;
// direction of PWM pulse
volatile int direction = 0;

// one day in clock cycles at 16MHz
#define TWENTY_FOUR_HOURS ((unsigned long) 16000000 * 60 * 60 * 24)

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
  LED_AllOff();
  Touch_Init();
  LCD_Init();
  Screen_Init();
  UART_Init();
  
  // set all timers up from medArray
  for (int i = 0; i < 3; i++) {
    if (medArray[i].timeRem) {
      Timer_Start(i, medArray[i].timeRem);
    }
  }
}

// handle I/O and get next state
void FSM() {
  switch (curr_state) {
    case READY:
      // serial input handler
      // if (SerialHasInput()) next_state = RECEIVE_DATA;

      // timer handlers
      for (int i = 0; i < 3; i++) {
        if (Timer_IsDone(i)) {
          next_state = TIMEUP;
          if (medArray[i].timeRem < TWENTY_FOUR_HOURS) {
            Handle_TimeUp(i);
          } else {
            Handle_TimeUpRepeat(i);
          }
        }
      }
      break;

    case TIMEUP:
      if (Done_Pressed()) {
        next_state = READY;
        Handle_Done();
      } else {
        PWM_Pulse();
      }
      break;

    default:
      next_state = READY;
      break;
  }
  curr_state = next_state;
}

// starts the time at 24 hours for the given timer, shows the reminder screen, and turns on the LED
void Handle_TimeUp(int timer) {
  Timer_Start(timer, TWENTY_FOUR_HOURS);
  medArray[timer].timeRem = TWENTY_FOUR_HOURS;
  Screen_Remind(timer);
  LED_On(timer);
}

// restarts the given timer, shows the reminder screen, and turns on the LED
void Handle_TimeUpRepeat(int timer) {
  Timer_Restart(timer);
  Screen_Remind(timer);
  LED_On(timer);
}

// handles done pressed by returning to the home screen and turning off LEDs
void Handle_Done() {
  Screen_Init();
  LED_AllOff();
}

// bounces duty cycle back and forth from 0 to max, creating a pulse
void PWM_Pulse() {
  for (int i = 0; i < 30000; i++); // slight delay; adjust shorter as needed
  if (direction == 0) {
    if (duty == 4) {
      direction = 1;
    }
    LED0_Set(duty--);
  } else {
    if (duty == PERIOD - 4) {
      direction = 0;
    }
    LED0_Set(duty++);
  }
}

// TODO
int SerialHasInput() {
  return 0;
}

// case RECEIVE_DATA:
//       next_state = READY;
//       // TODO: load data
//       // eg. i received
//       // update medArray[i]
//       // Timer_Start(i);
//       // Screen_Init();
//       break;