#include <stdint.h>
#include "mcheader.h"
#include "main.h"
#include "timers.h"

void UART_Init();

void lab5() {
  // PLL_Init();
  // PortF_Init(); // initiate port F for LEDs & switches

  UART_Init();

  // ADC_Init(); // initiate the ADC
  // Timer0_Init(16000000); // initiate timer

  while (1) {
    // if (cur_state == SLOW) { // cur_state == 80MHz
    //   if (!SW0() && SW1() && (next_state != FAST)) {
    //     next_state = FAST;
    //     Timer0_Init(80000000);
    //   } else if (!SW0() && !SW1() && (next_state != MED)) {
    //     next_state = MED;
    //     Timer0_Init(16000000);
    //   }
    //   RCC2 &= ~0x1FC00000; // clear SYSDIV2
    //   RCC2 |= 0x18C00000; // set SYSDIV2 to 99
    // } else if (cur_state == FAST) {
    //   if (SW0() && !SW1() && (next_state != SLOW)) {
    //     next_state = SLOW;
    //     Timer0_Init(4000000);
    //   } else if (!SW0() && !SW1() && (next_state != MED)) {
    //     next_state = MED;
    //     Timer0_Init(16000000);
    //   }
    //   RCC2 &= ~0x1FC00000; // clear SYSDIV2
    //   RCC2 |= 0x1000000; // set SYSDIV2 to 4
    // } else { // cur_state == 16MHz
    //   if (SW0() && !SW1() && (next_state != SLOW)) {
    //     next_state = SLOW;
    //     Timer0_Init(4000000);
    //   } else if (!SW0() && SW1() && (next_state != FAST)) {
    //     next_state = FAST;
    //     Timer0_Init(80000000);
    //   }
    //   RCC2 &= ~0x1FC00000; // clear SYSDIV2
    //   RCC2 |= 0x6000000; /// set SYSDIV2 to 24
    // }
    // cur_state = next_state;
  }
}

void UART_Init() {
  RCGCUART |= 0x1; // Enable the UART module 0
  delay(); delay(); delay();
  RCGCGPIO |= 0x1; // Enable clk to Port A
  GPIOAFSEL_A |= 0x3; // Set pins 0 & 1 for port A to be controlled by peripherals.
  GPIOPCTL_A |= 0x11; // Select loc 0 on mux as peripheral src.
  GPIODEN_A |= 0x3; // set port A pins as digital

  float BRD = (16000000.0 / (16.0 * 9600.0)); // measure BRD
  int intBRD = (int) BRD; // measure IBRD by round down
  int fracBRD = (int) ((BRD - intBRD) * 64.0 + 0.5); // measure FBRD

  UARTCTL_0 &= ~0x1; // disable UART module 0
  UARTIBRD_0 |= intBRD; // write integer BRD to UARTIBRD
  UARTFBRD_0 |= fracBRD; // write frac BRD to UARTFBRD
  UARTCTL_0 |= 0x300; // enable Tx and Rx
  UARTCC_0 |= 0x5; // set clock source to system clock
  UARTLCRH_0 &= ~0x10; // disable FIFO
  UARTLCRH_0 |= 0x60; // write serial param (word length to 8 bits)
  UARTCTL_0 |= 0x1; // enable UART module 0
}