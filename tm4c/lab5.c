#include <stdint.h>
#include "mcheader.h"
#include "main.h"
#include "timers.h"

// void UART_Init();

// program current state
enum State curr_state;
// program next state
enum State next_state;

// one day in clock cycles at 16MHz
#define TWENTY_FOUR_HOURS (16000000 * 60 * 60 * 24)

void lab5() {
  Init();

  while (1) {
    FSM();
  }
}

// set up everything
void Init() {
  // PLL_Init();

  Timers_Init();
  PWM_Init();
  LCD_Init();
  // UART_Init();

  // ADC_Init(); // initiate the ADC
  // Timer0_Init(16000000); // initiate timer
}

// void UART_Init() {
//   RCGCUART |= 0x1; // Enable the UART module 0
//   delay(); delay(); delay();
//   RCGCGPIO |= 0x1; // Enable clk to Port A
//   GPIOAFSEL_A |= 0x3; // Set pins 0 & 1 for port A to be controlled by peripherals.
//   GPIOPCTL_A |= 0x11; // Select loc 0 on mux as peripheral src.
//   GPIODEN_A |= 0x3; // set port A pins as digital

//   float BRD = (16000000.0 / (16.0 * 9600.0)); // measure BRD
//   int intBRD = (int) BRD; // measure IBRD by round down
//   int fracBRD = (int) ((BRD - intBRD) * 64.0 + 0.5); // measure FBRD

//   UARTCTL_0 &= ~0x1; // disable UART module 0
//   UARTIBRD_0 |= intBRD; // write integer BRD to UARTIBRD
//   UARTFBRD_0 |= fracBRD; // write frac BRD to UARTFBRD
//   UARTCTL_0 |= 0x300; // enable Tx and Rx
//   UARTCC_0 |= 0x5; // set clock source to system clock
//   UARTLCRH_0 &= ~0x10; // disable FIFO
//   UARTLCRH_0 |= 0x60; // write serial param (word length to 8 bits)
//   UARTCTL_0 |= 0x1; // enable UART module 0
// }


// handle I/O and get next state
void FSM() {
  int t;
  switch (curr_state) {
    case READY:
      // serial input handler
      if (Serial_HasInput()) {
        next_state = RECEIVE_DATA;
      }
      break;

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
  medArray[timer].timeRem = TWENTY_FOUR_HOURS;
  Screen_Remind(t)imer;
  LED_On(timer);
}

void Handle_TimeUpRepeat(int timer) {
  Timer_Restart(timer);
  Screen_Remind(timer);
  LED_On(timer);
}

// TODO
int Serial_HasInput() {
  return 0;
}