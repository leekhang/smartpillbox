/**************************************************
 *
 * This file contains an interrupt vector for Cortex-M written in C.
 * The actual interrupt functions must be provided by the application developer.
 *
 * Copyright 2007-2017 IAR Systems AB.
 *
 * $Revision: 112610 $
 *
 **************************************************/

#pragma language=extended
#pragma segment="CSTACK"

extern void __iar_program_start( void );

extern void NMI_Handler( void );
extern void HardFault_Handler( void );
extern void MemManage_Handler( void );
extern void BusFault_Handler( void );
extern void UsageFault_Handler( void );
extern void SVC_Handler( void );
extern void DebugMon_Handler( void );
extern void PendSV_Handler( void );
extern void SysTick_Handler( void );

// extern void UART_Handler( void );

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

// The vector table is normally located at address 0.
// When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
// If you need to define interrupt service routines,
// make a copy of this file and include it in your project.
// The name "__vector_table" has special meaning for C-SPY, which
// is where to find the SP start value.
// If vector table is not located at address 0, the user has to initialize
// the  NVIC vector table register (VTOR) before using interrupts.


#pragma location = ".intvec"
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) }, //00
  __iar_program_start,  //01

  NMI_Handler,          //02
  HardFault_Handler,    //03
  MemManage_Handler,    //04
  BusFault_Handler,     //05
  UsageFault_Handler,   //06
  0,                    //07
  0,                    //08
  0,                    //09
  0,                    //10
  SVC_Handler,          //11
  DebugMon_Handler,     //12
  0,                    //13
  PendSV_Handler,       //14
  SysTick_Handler,      //15
  0,                    //16
  0,                    //17
  0,                    //18
  0,                    //19
  0,                    //20
  0, // UART_Handler,         //21
  0,                    //22
  0,                    //23
  0,                    //24
  0,                    //25
  0,                    //26
  0,                    //27
  0,                    //28
  0,                    //29
  0,                    //30
  0,                    //31
  0,                    //32
  ADC0_Handler,         //33
  0,                    //34
  0,                    //35
  0,                    //36
  0,                    //37
  0,                    //38
  0,                    //39
  0,                    //40
  0,                    //41
  0,                    //42
  0,                    //43
  0,                    //44
  0,                    //45
  0,                    //46
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

#pragma call_graph_root = "interrupt"
__weak void NMI_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void HardFault_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void MemManage_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void BusFault_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void UsageFault_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void SVC_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void DebugMon_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void PendSV_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void SysTick_Handler( void ) { while (1) {} }

// #pragma call_graph_root = "interrupt"
// __weak void UART_Handler (void) { while (1) {} }

void __cmain( void );
__weak void __iar_init_core( void );
__weak void __iar_init_vfp( void );

#pragma required=__vector_table
void __iar_program_start( void )
{
  __iar_init_core();
  __iar_init_vfp();
  __cmain();
}
