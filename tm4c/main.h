#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include "SSD2119.h"

void delay();
void UART_Handler();
unsigned long ascii_convert(char);

// stores name (string), time (string), & time remaining (unsigned long timeRem)
struct Med {
    int index;
    char name[14];
    char time[8];
    unsigned long long int timeRem;
};

// array for storing medicine data
struct Med medArray[3];

// program state
enum State {
  READY,
  TIMEUP,
  RECEIVE_DATA,
};

// function to delay 
void delay() { for (int i = 0; i < 1000000; i++); }

// function to initialize the UART0 module
void UART_Init() {
  RCGCUART |= 0x1; // Enable the UART module 0
  delay();
  
  RCGCGPIO |= 0x1; // Enable clk to Port A
  GPIOAFSEL_A |= 0x3; // Set pins 0 & 1 for port A to be controlled by peripherals.
  GPIOPCTL_A |= (1<<0) | (1<<4); // Select loc 0 on mux as peripheral src.
  GPIODEN_A |= 0x3; // set port A pins as digital

  UARTCTL_0 &= ~0x1; // disable UART module 0
  UARTIBRD_0 |= 104; // write integer BRD to UARTIBRD
  UARTFBRD_0 |= 11; // write frac BRD to UARTFBRD
  UARTCC_0 |= 0x5; // set clock source to system clock
  // UARTLCRH_0 &= ~0x10; // disable FIFO
  UARTLCRH_0 |= 0x60; // write serial param (word length to 8 bits)
  UARTCTL_0 |= (1<<0) | (1<<8) | (1<<9); // enable UART module 0 and Tx and Rx
  
  // NVIC_EN0_R =(1<<5);//INT EN
  // UARTIM |=(1<<4);
  // UARTICR|=(1<<4);//clear RX INT
}

unsigned long ascii_convert(char c) {
  return (unsigned long) c - 48;
}

#endif