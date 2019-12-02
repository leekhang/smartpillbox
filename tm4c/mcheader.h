#include <stdint.h>

#ifndef __MCHEADER_H__
#define __MCHEADER_H__

// LED COLORS -------------------------------------------------------------

#define RGB    0xE
#define RED    0x2
#define BLUE   0x4
#define GREEN  0x8
#define YELLOW 0xA
#define PURPLE 0x6
#define CYAN   0xC

// SYSTEM TIMER REGISTER DESCRIPTIONS -------------------------------------------------------------

/* Reg 4: Interrupts 0-31   EN0 (offset: 0x100) */
/* Reg 5: Interrupts 31-63  EN1 (offset: 0x104) */
/* Reg 6: Interrupts 64-95  EN2 (offset: 0x108) */
/* Reg 7: Interrupts 96-127 EN3 (offset: 0x10C) */
// 0: On read, interrupt is disabled. On write, no effect.
// 1: On read, interrupt is enabled. On write, enables interrupt.

#define EN0 ( *((volatile uint32_t *) 0xE000E100U ) )
#define EN1 ( *((volatile uint32_t *) 0xE000E104U ) )
#define EN2 ( *((volatile uint32_t *) 0xE000E108U ) )
#define EN3 ( *((volatile uint32_t *) 0xE000E10CU ) )


// SYSTEM CONTROLS -------------------------------------------------------------

/* Reg 4: Raw Interrupt Status (offset: 0x050) */
#define RIS              ( *((volatile uint32_t *) 0x400FE050 ) )

/* Reg 5: Interrupt Mask Control (offset: 0x054) */
#define IMC              ( *((volatile uint32_t *) 0x400FE054 ) )

/* Reg 6: Masked Interrupt Status & Clear (offset: 0x058) */
#define MISC             ( *((volatile uint32_t *) 0x400FE058 ) )

/* Reg 8: Run Mode Clk Config (offset: 0x060) */
// [26:23]: SYSDIV, 22: USESYSDIV, 13: PWRDOWN
// 11: PLLBYPASS, [10:6]: XTAL, [5:4]: OSCSRC
#define RCC              ( *((volatile uint32_t *) 0x400FE060 ) )


/* Reg 10: Run Mode Clk Config 2 (offset: 0x060) */
// [26:23]: SYSDIV, 22: USESYSDIV, 13: PWRDOWN
// 11: PLLBYPASS, [10:6]: XTAL, [5:4]: OSCSRC
#define RCC2             ( *((volatile uint32_t *) 0x400FE070 ) )


/* Reg 11: Main Oscillator Ctrl (offset: 0x07C) */
#define MOSCCTL          ( *((volatile uint32_t *) 0x400FE07C ) )


/* Reg 18: PLL Status (offset: 0x168) */
#define PLLSTAT          ( *((volatile uint32_t *) 0x400FE168 ) )


/* Reg 59: 16/32-Bit General-Purpose Timer RCGC (offset: 0x604) */

#define RCGCTIMER        ( *((volatile uint32_t *) 0x400FE604 ) )
#define RCGCTIMER_T4     0x10
#define RCGCTIMER_T3     0x08
#define RCGCTIMER_T2     0x04
#define RCGCTIMER_T1     0x02
#define RCGCTIMER_T0     0x01

/* Reg 60: Run Mode Clock Gating Control 0x400FE608 (offset: 0x608) */
// RCGCGPIO controls access to clock and module regs.
// When off, clock is disabled & accesses to module regs generate a bus fault.
// bits [5:0] correspond to ports F to A.

#define RCGCGPIO        ( *((volatile uint32_t *) 0x400FE608U) )
#define RCGCGPIO_A      0x01
#define RCGCGPIO_B      0x02
#define RCGCGPIO_C      0x04
#define RCGCGPIO_D      0x08
#define RCGCGPIO_E      0x10
#define RCGCGPIO_F      0x20


/* Reg 63: UART RCGC (offset: 0x618) */

#define RCGCUART        ( *((volatile uint32_t *) 0x400FE618 ) )



/* Reg 68: Analog-to-Digital Converter (offset: 0x638) */
// bit 0: controls whether ADC module 0 is enabled (1) or disabled.
// bit 1: controls whether ADC module 1 is enabled (1) or disabled.

#define RCGCADC ( *((volatile uint32_t *) 0x400FE638) )


/* Register 70: Pulse Width Modulation (PWM) RCGC (offset: 0x640) */
// bit 0: controls whether PWM Module 0 is enabled (1) or disabled
// bit 1: controls whether PWM Module 1 is enabled (1) or disabled

#define RCGCPWM ( *((volatile uint32_t *) 0x400FE640) )


/* Register 73: 32/64-Bit Wide General-Purpose Timer RCGC (offset: 0x65C) */

#define RCGCWTIMER       ( *((volatile uint32_t *)0x400FE065U) )
#define RCGCWTIMER_T4    0x10
#define RCGCWTIMER_T3    0x08
#define RCGCWTIMER_T2    0x04
#define RCGCWTIMER_T1    0x02
#define RCGCWTIMER_T0    0x01


// GENERAL PURPOSE INPUT/OUTPUT ------------------------------------------------

/* Reg 1: GPIO Data (offset: 0x400) */
// Values written to GPIODATA are transferred onto the pins (if they're outputs)
// Values can be read from GPIODATA (if the pins are inputs).
// [7:0] correspond to the 8 bits of each port.

#define GPIODATA_A       ( *((volatile uint32_t *) 0x400043FCU) )
#define GPIODATA_B       ( *((volatile uint32_t *) 0x400053FCU) )
#define GPIODATA_C       ( *((volatile uint32_t *) 0x400063FCU) )
#define GPIODATA_D       ( *((volatile uint32_t *) 0x400073FCU) )
#define GPIODATA_E       ( *((volatile uint32_t *) 0x400243FCU) )
#define GPIODATA_F       ( *((volatile uint32_t *) 0x400253FCU) )


/* Reg 2: GPIO Direction (offset: 0x400) */
// output = 1 and input = 0. All bits become input by a reset.
// All directions are based on Advanced Peripehral Bus (APB).
// [7:0] correspond to the 8 bits of each port.

#define GPIODIR_A       ( *((volatile uint32_t *) 0x40004400U) )
#define GPIODIR_B       ( *((volatile uint32_t *) 0x40005400U) )
#define GPIODIR_C       ( *((volatile uint32_t *) 0x40006400U) )
#define GPIODIR_D       ( *((volatile uint32_t *) 0x40007400U) )
#define GPIODIR_E       ( *((volatile uint32_t *) 0x40024400U) )
#define GPIODIR_F       ( *((volatile uint32_t *) 0x40025400U) )


/* Reg 3: GPIO Interrupt Sense (offset: 0x404) */

#define GPIOIS_A       ( *((volatile uint32_t *) 0x40004404U) )
#define GPIOIS_B       ( *((volatile uint32_t *) 0x40005404U) )
#define GPIOIS_C       ( *((volatile uint32_t *) 0x40006404U) )
#define GPIOIS_D       ( *((volatile uint32_t *) 0x40007404U) )
#define GPIOIS_E       ( *((volatile uint32_t *) 0x40024404U) )
#define GPIOIS_F       ( *((volatile uint32_t *) 0x40025404U) )


/* Reg 4: GPIO Interrupt Both Edges (offset: 0x408) */

#define GPIOIBE_A       ( *((volatile uint32_t *) 0x40004408U) )
#define GPIOIBE_B       ( *((volatile uint32_t *) 0x40005408U) )
#define GPIOIBE_C       ( *((volatile uint32_t *) 0x40006408U) )
#define GPIOIBE_D       ( *((volatile uint32_t *) 0x40007408U) )
#define GPIOIBE_E       ( *((volatile uint32_t *) 0x40024408U) )
#define GPIOIBE_F       ( *((volatile uint32_t *) 0x40025408U) )


/* Reg 5: GPIO Interrupt Event (offset: 0x40C) */

#define GPIOIEV_A       ( *((volatile uint32_t *) 0x4000440CU) )
#define GPIOIEV_B       ( *((volatile uint32_t *) 0x4000540CU) )
#define GPIOIEV_C       ( *((volatile uint32_t *) 0x4000640CU) )
#define GPIOIEV_D       ( *((volatile uint32_t *) 0x4000740CU) )
#define GPIOIEV_E       ( *((volatile uint32_t *) 0x4002440CU) )
#define GPIOIEV_F       ( *((volatile uint32_t *) 0x4002540CU) )


/* Reg 6: GPIO Interrupt Mask (offset: 0x410) */

#define GPIOIM_A          ( *((volatile uint32_t *) 0x40004410U) )
#define GPIOIM_B          ( *((volatile uint32_t *) 0x40005410U) )
#define GPIOIM_C          ( *((volatile uint32_t *) 0x40006410U) )
#define GPIOIM_D          ( *((volatile uint32_t *) 0x40007410U) )
#define GPIOIM_E          ( *((volatile uint32_t *) 0x40024410U) )
#define GPIOIM_F          ( *((volatile uint32_t *) 0x40025410U) )


/* Reg 7: GPIO Raw Interrupt Status (offset: 0x414) */

#define GPIORIS_A          ( *((volatile uint32_t *) 0x40004414U) )
#define GPIORIS_B          ( *((volatile uint32_t *) 0x40005414U) )
#define GPIORIS_C          ( *((volatile uint32_t *) 0x40006414U) )
#define GPIORIS_D          ( *((volatile uint32_t *) 0x40007414U) )
#define GPIORIS_E          ( *((volatile uint32_t *) 0x40024414U) )
#define GPIORIS_F          ( *((volatile uint32_t *) 0x40025414U) )


/* Reg 9: GPIO Interrupt Clear (offset: 0x41C) */

#define GPIOICR_A          ( *((volatile uint32_t *) 0x4000441CU) )
#define GPIOICR_B          ( *((volatile uint32_t *) 0x4000541CU) )
#define GPIOICR_C          ( *((volatile uint32_t *) 0x4000641CU) )
#define GPIOICR_D          ( *((volatile uint32_t *) 0x4000741CU) )
#define GPIOICR_E          ( *((volatile uint32_t *) 0x4002441CU) )
#define GPIOICR_F          ( *((volatile uint32_t *) 0x4002541CU) )


/* Reg 10: GPIO Alternate Function Select (offset 0x420) */
// 0: pin is used as GPIO and is controlled by the GPIO register.
// 1: configures pin to be controlled by an associated peripheral.

#define GPIOAFSEL_A       ( *((volatile uint32_t *) 0x40004420U) )
#define GPIOAFSEL_B       ( *((volatile uint32_t *) 0x40005420U) )
#define GPIOAFSEL_C       ( *((volatile uint32_t *) 0x40006420U) )
#define GPIOAFSEL_D       ( *((volatile uint32_t *) 0x40007420U) )
#define GPIOAFSEL_E       ( *((volatile uint32_t *) 0x40024420U) )
#define GPIOAFSEL_F       ( *((volatile uint32_t *) 0x40025420U) )


/* Reg 15: GPIO Pull-Up Select (offset 0x510) */
// Setting GPIOPUR to 1 auto-clears the corresponding bit in GPIOPDR.
// Write access to this reg is protected by GPIOCR.
// [7:0] correspond to the 8 bits of each port.

#define GPIOPUR_A       ( *((volatile uint32_t *) 0x40004510U) )
#define GPIOPUR_B       ( *((volatile uint32_t *) 0x40005510U) )
#define GPIOPUR_C       ( *((volatile uint32_t *) 0x40006510U) )
#define GPIOPUR_D       ( *((volatile uint32_t *) 0x40007510U) )
#define GPIOPUR_E       ( *((volatile uint32_t *) 0x40024510U) )
#define GPIOPUR_F       ( *((volatile uint32_t *) 0x40025510U) )


/* Reg 18: GPIO Digital Enable APB (offset: 0x51C) */
// Default: GPIO signals (except for PA[5:0], PB[3:2], PC[3:0], PD[7], PF[0]) are tristated.
// This means that they don't drive logic value and don't allow pin voltage.
// [7:0] correspond to the 8 bits of each port.

#define GPIODEN_A        ( *((volatile uint32_t *) 0x4000451C) )
#define GPIODEN_B        ( *((volatile uint32_t *) 0x4000551C) )
#define GPIODEN_C        ( *((volatile uint32_t *) 0x4000651C) )
#define GPIODEN_D        ( *((volatile uint32_t *) 0x4000751C) )
#define GPIODEN_E        ( *((volatile uint32_t *) 0x4002451C) )
#define GPIODEN_F        ( *((volatile uint32_t *) 0x4002551C) )


/* Reg 19: GPIO Lock (offset: 0x520) */
// GPIOLOCK controls write access to the GPIOCR.
// Writing 0x4C4F434B (32 bits) to GPIOLOCK unlocks GPIOCR.
// Reg takes a 32 bit value [31:0].

#define GPIOLOCK_A       ( *((volatile uint32_t *) 0x40004520) )
#define GPIOLOCK_B       ( *((volatile uint32_t *) 0x40005520) )
#define GPIOLOCK_C       ( *((volatile uint32_t *) 0x40006520) )
#define GPIOLOCK_D       ( *((volatile uint32_t *) 0x40007520) )
#define GPIOLOCK_E       ( *((volatile uint32_t *) 0x40024520) )
#define GPIOLOCK_F       ( *((volatile uint32_t *) 0x40025520) )
#define GPIOLOCK_OPEN   0x4C4F434BU


/* Reg 20: GPIO Commit (offset: 0x524) */
// GPIOCR determines which bits of GPIOAFSEL, GPIOPUR, GPIOPDR, & GPIODEN are committed.
// GPIOCR can only be modified if GPIOLOCK is unlocked.
// [7:0] determines whether a pin can(1) or cannot(0) be written.

#define GPIOCR_A          ( *((volatile uint32_t *) 0x40004524) )
#define GPIOCR_B          ( *((volatile uint32_t *) 0x40005524) )
#define GPIOCR_C          ( *((volatile uint32_t *) 0x40006524) )
#define GPIOCR_D          ( *((volatile uint32_t *) 0x40007524) )
#define GPIOCR_E          ( *((volatile uint32_t *) 0x40024524) )
#define GPIOCR_F          ( *((volatile uint32_t *) 0x40025524) )


/* Reg 21: GPIO Analog Mode Select (offset: 0x528) */
// GPIOAMSEL controls isolation circuits to the analog side of a unified I/O pad.
// 0: analog disabled, isolation enabled. 1: analog func enabled, isolation disabled.
// [7:0] correspond to 8 pins of a port.

#define GPIOAMSEL_A       ( *((volatile uint32_t *) 0x40004528) )
#define GPIOAMSEL_B       ( *((volatile uint32_t *) 0x40005528) )
#define GPIOAMSEL_C       ( *((volatile uint32_t *) 0x40006528) )
#define GPIOAMSEL_D       ( *((volatile uint32_t *) 0x40007528) )
#define GPIOAMSEL_E       ( *((volatile uint32_t *) 0x40024528) )
#define GPIOAMSEL_F       ( *((volatile uint32_t *) 0x40025528) )


/* Reg 22: GPIO Port Control (offset: 0x52C) */
// Used with GPIOAFSEL & selects the specific peripheral signal for each GPIO pin when using the alternate function mode.
// When GPIOAFSEL is set, the corresponding GPIO is controlled by a peripheral.
// GPIOPCTL selects one out of a set of peripherals. Each pin has a 4 bit mux.

#define GPIOPCTL_A       ( *((volatile uint32_t *) 0x4000452C) )
#define GPIOPCTL_B       ( *((volatile uint32_t *) 0x4000552C) )
#define GPIOPCTL_C       ( *((volatile uint32_t *) 0x4000652C) )
#define GPIOPCTL_D       ( *((volatile uint32_t *) 0x4000752C) )
#define GPIOPCTL_E       ( *((volatile uint32_t *) 0x4002452C) )
#define GPIOPCTL_F       ( *((volatile uint32_t *) 0x4002552C) )


// GENERAL PURPOSE TIMER ------------------------------------------------

/* Reg 4: GPTM Control (offset: 0x00C) */

#define GPTMCTL_T0_1632  ( *((volatile uint32_t *) 0x4003000C) )
#define GPTMCTL_T1_1632  ( *((volatile uint32_t *) 0x4003100C) )
#define GPTMCTL_T2_1632  ( *((volatile uint32_t *) 0x4003200C) )
#define GPTMCTL_T3_1632  ( *((volatile uint32_t *) 0x4003300C) )
#define GPTMCTL_T4_1632  ( *((volatile uint32_t *) 0x4003400C) )
#define GPTMCTL_T5_1632  ( *((volatile uint32_t *) 0x4003500C) )

#define GPTMCTL_T0_3264  ( *((volatile uint32_t *) 0x4003600C) )
#define GPTMCTL_T1_3264  ( *((volatile uint32_t *) 0x4003700C) )
#define GPTMCTL_T2_3264  ( *((volatile uint32_t *) 0x4004C00C) )
#define GPTMCTL_T3_3264  ( *((volatile uint32_t *) 0x4004D00C) )
#define GPTMCTL_T4_3264  ( *((volatile uint32_t *) 0x4004E00C) )
#define GPTMCTL_T5_3264  ( *((volatile uint32_t *) 0x4004F00C) )


/* Reg 1: GPTM Config (offset: 0x000) */

#define GPTMCFG_T0_1632  ( *((volatile uint32_t *) 0x40030000) )
#define GPTMCFG_T1_1632  ( *((volatile uint32_t *) 0x40031000) )
#define GPTMCFG_T2_1632  ( *((volatile uint32_t *) 0x40032000) )
#define GPTMCFG_T3_1632  ( *((volatile uint32_t *) 0x40033000) )
#define GPTMCFG_T4_1632  ( *((volatile uint32_t *) 0x40034000) )
#define GPTMCFG_T5_1632  ( *((volatile uint32_t *) 0x40035000) )

#define GPTMCFG_T0_3264  ( *((volatile uint32_t *) 0x40036000) )
#define GPTMCFG_T1_3264  ( *((volatile uint32_t *) 0x40037000) )
#define GPTMCFG_T2_3264  ( *((volatile uint32_t *) 0x4004C000) )
#define GPTMCFG_T3_3264  ( *((volatile uint32_t *) 0x4004D000) )
#define GPTMCFG_T4_3264  ( *((volatile uint32_t *) 0x4004E000) )
#define GPTMCFG_T5_3264  ( *((volatile uint32_t *) 0x4004F000) )


/* Reg 2: GPTM Config (offset: 0x004) */

#define GPTMTAMR_T0_1632 ( *((volatile uint32_t *) 0x40030004) )
#define GPTMTAMR_T1_1632 ( *((volatile uint32_t *) 0x40031004) )
#define GPTMTAMR_T2_1632 ( *((volatile uint32_t *) 0x40032004) )
#define GPTMTAMR_T3_1632 ( *((volatile uint32_t *) 0x40033004) )
#define GPTMTAMR_T4_1632 ( *((volatile uint32_t *) 0x40034004) )
#define GPTMTAMR_T5_1632 ( *((volatile uint32_t *) 0x40035004) )

#define GPTMTAMR_T0_3264 ( *((volatile uint32_t *) 0x40036004) )
#define GPTMTAMR_T1_3264 ( *((volatile uint32_t *) 0x40037004) )
#define GPTMTAMR_T2_3264 ( *((volatile uint32_t *) 0x4004C004) )
#define GPTMTAMR_T3_3264 ( *((volatile uint32_t *) 0x4004D004) )
#define GPTMTAMR_T4_3264 ( *((volatile uint32_t *) 0x4004E004) )
#define GPTMTAMR_T5_3264 ( *((volatile uint32_t *) 0x4004F004) )


/* Reg 6: GPTM Interrupt Mask (offset: 0x018) */

#define GPTMIMR_T0_1632  ( *((volatile uint32_t *) 0x40030018) )
#define GPTMIMR_T1_1632  ( *((volatile uint32_t *) 0x40031018) )
#define GPTMIMR_T2_1632  ( *((volatile uint32_t *) 0x40032018) )
#define GPTMIMR_T3_1632  ( *((volatile uint32_t *) 0x40033018) )
#define GPTMIMR_T4_1632  ( *((volatile uint32_t *) 0x40034018) )
#define GPTMIMR_T5_1632  ( *((volatile uint32_t *) 0x40035018) )

#define GPTMIMR_T0_3264  ( *((volatile uint32_t *) 0x40036018) )
#define GPTMIMR_T1_3264  ( *((volatile uint32_t *) 0x40037018) )
#define GPTMIMR_T2_3264  ( *((volatile uint32_t *) 0x4004C018) )
#define GPTMIMR_T3_3264  ( *((volatile uint32_t *) 0x4004D018) )
#define GPTMIMR_T4_3264  ( *((volatile uint32_t *) 0x4004E018) )
#define GPTMIMR_T5_3264  ( *((volatile uint32_t *) 0x4004F018) )


/* Reg 7: GPTM Raw Interupt Status (offset: 0x01C) */

#define GPTMRIS_T0_1632  ( *((volatile uint32_t *) 0x4003001C) )
#define GPTMRIS_T1_1632  ( *((volatile uint32_t *) 0x4003101C) )
#define GPTMRIS_T2_1632  ( *((volatile uint32_t *) 0x4003201C) )
#define GPTMRIS_T3_1632  ( *((volatile uint32_t *) 0x4003301C) )
#define GPTMRIS_T4_1632  ( *((volatile uint32_t *) 0x4003401C) )
#define GPTMRIS_T5_1632  ( *((volatile uint32_t *) 0x4003501C) )

#define GPTMRIS_T0_3264  ( *((volatile uint32_t *) 0x4003601C) )
#define GPTMRIS_T1_3264  ( *((volatile uint32_t *) 0x4003701C) )
#define GPTMRIS_T2_3264  ( *((volatile uint32_t *) 0x4004C01C) )
#define GPTMRIS_T3_3264  ( *((volatile uint32_t *) 0x4004D01C) )
#define GPTMRIS_T4_3264  ( *((volatile uint32_t *) 0x4004E01C) )
#define GPTMRIS_T5_3264  ( *((volatile uint32_t *) 0x4004F01C) )


/* Reg 9: GPTM Interrupt Clear (offset: 0x024) */

#define GPTMICR_T0_1632  ( *((volatile uint32_t *) 0x40030024) )
#define GPTMICR_T1_1632  ( *((volatile uint32_t *) 0x40031024) )
#define GPTMICR_T2_1632  ( *((volatile uint32_t *) 0x40032024) )
#define GPTMICR_T3_1632  ( *((volatile uint32_t *) 0x40033024) )
#define GPTMICR_T4_1632  ( *((volatile uint32_t *) 0x40034024) )
#define GPTMICR_T5_1632  ( *((volatile uint32_t *) 0x40035024) )

#define GPTMICR_T0_3264  ( *((volatile uint32_t *) 0x40036024) )
#define GPTMICR_T1_3264  ( *((volatile uint32_t *) 0x40037024) )
#define GPTMICR_T2_3264  ( *((volatile uint32_t *) 0x4004C024) )
#define GPTMICR_T3_3264  ( *((volatile uint32_t *) 0x4004D024) )
#define GPTMICR_T4_3264  ( *((volatile uint32_t *) 0x4004E024) )
#define GPTMICR_T5_3264  ( *((volatile uint32_t *) 0x4004F024) )


/* Reg 10: GPTM Timer A Interval Load (offset: 0x028) */

#define GPTMTAILR_T0_1632  ( *((volatile uint32_t *) 0x40030028) )
#define GPTMTAILR_T1_1632  ( *((volatile uint32_t *) 0x40031028) )
#define GPTMTAILR_T2_1632  ( *((volatile uint32_t *) 0x40032028) )
#define GPTMTAILR_T3_1632  ( *((volatile uint32_t *) 0x40033028) )
#define GPTMTAILR_T4_1632  ( *((volatile uint32_t *) 0x40034028) )
#define GPTMTAILR_T5_1632  ( *((volatile uint32_t *) 0x40035028) )

#define GPTMTAILR_T0_3264  ( *((volatile uint32_t *) 0x40036028) )
#define GPTMTAILR_T1_3264  ( *((volatile uint32_t *) 0x40037028) )
#define GPTMTAILR_T2_3264  ( *((volatile uint32_t *) 0x4004C028) )
#define GPTMTAILR_T3_3264  ( *((volatile uint32_t *) 0x4004D028) )
#define GPTMTAILR_T4_3264  ( *((volatile uint32_t *) 0x4004E028) )
#define GPTMTAILR_T5_3264  ( *((volatile uint32_t *) 0x4004F028) )



// ANALOG TO DIGITAL CONVERTER ------------------------------------------------

/* Reg 1: ADC Active Sample Sequencer (offset: 0x000) */
// [16]: Set ADC to busy (1) or idle (0).
// [3:0]: enable (1) or disable (0) SS#

#define ADCACTSS_0         ( *((volatile uint32_t *) 0x40038000) )
#define ADCACTSS_1         ( *((volatile uint32_t *) 0x40039000) )


/* Reg 2: ADC Raw Interrupt Status (offset: 0x004) */
// [16]: Digital comparator interrupt status.
// [3:0]: interrupt status for SS#

#define ADCRIS_0           ( *((volatile uint32_t *) 0x40038004) )
#define ADCRIS_1           ( *((volatile uint32_t *) 0x40039004) )


/* Reg 3: ADC Interrupt Mask (offset: 0x008) */
// [19:16]: Digital comparator interrupt mask for SS#
// [3:0]: interrupt mask for SS#

#define ADCIM_0            ( *((volatile uint32_t *) 0x40038008) )
#define ADCIM_1            ( *((volatile uint32_t *) 0x40039008) )


/* Reg 4: ADC Interrupt Status & Clear (offset: 0x00C) */
// [19:16]: Digital comparator interrupt status for SS#
// [3:0]: interrupt status for SS#

#define ADCISC_0           ( *((volatile uint32_t *) 0x4003800C) )
#define ADCISC_1           ( *((volatile uint32_t *) 0x4003900C) )


/* Reg 6: ADC Event Mux Select (offset: 0x014) */
// [15:12] SS3, [11:8] SS2, [7:4] SS1, [3:0] SS0
// Takes values 0x0 to 0xF

#define ADCEMUX_0          ( *((volatile uint32_t *) 0x40038014) )
#define ADCEMUX_1          ( *((volatile uint32_t *) 0x40039014) )


/* Reg 11: ADC Processor SS Initiate (offset: 0x028) */
// 31: GSYNC || 27: SYNCWAIT || [3:0]: begin sampling at SS#.

#define ADCPSSI_0          ( *((volatile uint32_t *) 0x40038028) )
#define ADCPSSI_1          ( *((volatile uint32_t *) 0x40039028) )

/* Reg 27: ADCSS Input Mux Sel 1  (offset: 0x060) */
/* Reg 28: ADCSS Input Mux Sel 2  (offset: 0x080) */
/* Reg 35: ADCSS Input Mux Sel 3  (offset: 0x0A0) only MUX0 avail. */
// [15:12] MUX3 || [11:8] MUX2 || [7:4] MUX1 || [3:0] MUX0

#define ADCSSMUX1_0        ( *((volatile uint32_t *) 0x40038060) )
#define ADCSSMUX1_1        ( *((volatile uint32_t *) 0x40039060) )

#define ADCSSMUX2_0        ( *((volatile uint32_t *) 0x40038080) )
#define ADCSSMUX2_1        ( *((volatile uint32_t *) 0x40039080) )

#define ADCSSMUX3_0        ( *((volatile uint32_t *) 0x400380A0) )
#define ADCSSMUX3_1        ( *((volatile uint32_t *) 0x400390A0) )


/* Reg 16: ADCSS Control 0  (offset: 0x044) (all bits avail) */
/* Reg 29: ADCSS Control 1  (offset: 0x064) (15:0 avail) */
/* Reg 30: ADCSS Control 2  (offset: 0x084) (15:0 avail) */
/* Reg 36: ADCSS Control 3  (offset: 0x0A4) (only 3:0 avail) */
// every 4 bits: nth sample temp sel (TS#), sample interrupt enable (IE#),
//               end of sequence (END#), sample diff input sel (D#)

#define ADCSSCTL0_0        ( *((volatile uint32_t *) 0x40038044) )
#define ADCSSCTL0_1        ( *((volatile uint32_t *) 0x40039044) )

#define ADCSSCTL1_0        ( *((volatile uint32_t *) 0x40038064) )
#define ADCSSCTL1_1        ( *((volatile uint32_t *) 0x40039064) )

#define ADCSSCTL2_0        ( *((volatile uint32_t *) 0x40038084) )
#define ADCSSCTL2_1        ( *((volatile uint32_t *) 0x40039084) )

#define ADCSSCTL3_0        ( *((volatile uint32_t *) 0x400380A4) )
#define ADCSSCTL3_1        ( *((volatile uint32_t *) 0x400390A4) )


/* Reg 17: ADCSS Result FIFO 0 (offset: 0x048) */
/* Reg 18: ADCSS Result FIFO 1 (offset: 0x068) */
/* Reg 19: ADCSS Result FIFO 2 (offset: 0x088) */
/* Reg 20: ADCSS Result FIFO 3 (offset: 0x0A8) */
// [11:0] Data conv result.

#define ADCSSFIFO0_0        ( *((volatile uint32_t *) 0x40038048) )
#define ADCSSFIFO0_1        ( *((volatile uint32_t *) 0x40039048) )

#define ADCSSFIFO1_0        ( *((volatile uint32_t *) 0x40038068) )
#define ADCSSFIFO1_1        ( *((volatile uint32_t *) 0x40039068) )

#define ADCSSFIFO2_0        ( *((volatile uint32_t *) 0x40038088) )
#define ADCSSFIFO2_1        ( *((volatile uint32_t *) 0x40039088) )

#define ADCSSFIFO3_0        ( *((volatile uint32_t *) 0x400380A8) )
#define ADCSSFIFO3_1        ( *((volatile uint32_t *) 0x400390A8) )


// UART -----------------------------------------------

/* Reg 1: UART Data (offset: 0x000) */
// 11: Overrun Error, 10: Break Error, 9: Parity Error, 8: Framing Error
// [7:0]: Data Transmitted / Received.

#define UARTDR_0        ( *((volatile uint32_t *) 0x4000C000) )
#define UARTDR_1        ( *((volatile uint32_t *) 0x4000D000) )
#define UARTDR_2        ( *((volatile uint32_t *) 0x4000E000) )
#define UARTDR_3        ( *((volatile uint32_t *) 0x4000F000) )
#define UARTDR_4        ( *((volatile uint32_t *) 0x40010000) )
#define UARTDR_5        ( *((volatile uint32_t *) 0x40011000) )
#define UARTDR_6        ( *((volatile uint32_t *) 0x40012000) )
#define UARTDR_7        ( *((volatile uint32_t *) 0x40013000) )


/* Reg 3: UART Flag (offset: 0x018) */
// 7: Tx FIFO Empty, 6: Rx FIFO full, 5: Tx FIFO full, 4: Rx FIFO empty
// 3: UART Busy, 0: Clear to Send

#define UARTFR_0        ( *((volatile uint32_t *) 0x4000C018) )
#define UARTFR_1        ( *((volatile uint32_t *) 0x4000D018) )
#define UARTFR_2        ( *((volatile uint32_t *) 0x4000E018) )
#define UARTFR_3        ( *((volatile uint32_t *) 0x4000F018) )
#define UARTFR_4        ( *((volatile uint32_t *) 0x40010018) )
#define UARTFR_5        ( *((volatile uint32_t *) 0x40011018) )
#define UARTFR_6        ( *((volatile uint32_t *) 0x40012018) )
#define UARTFR_7        ( *((volatile uint32_t *) 0x40013018) )


/* Reg 5: UART Integer Baud-Rate Divisor (offset: 0x024) */
// [15:0] Integer Baud-Rate Divisor

#define UARTIBRD_0        ( *((volatile uint32_t *) 0x4000C024) )
#define UARTIBRD_1        ( *((volatile uint32_t *) 0x4000D024) )
#define UARTIBRD_2        ( *((volatile uint32_t *) 0x4000E024) )
#define UARTIBRD_3        ( *((volatile uint32_t *) 0x4000F024) )
#define UARTIBRD_4        ( *((volatile uint32_t *) 0x40010024) )
#define UARTIBRD_5        ( *((volatile uint32_t *) 0x40011024) )
#define UARTIBRD_6        ( *((volatile uint32_t *) 0x40012024) )
#define UARTIBRD_7        ( *((volatile uint32_t *) 0x40013024) )


/* Reg 6: UART Fractional BRD (offset: 0x028) */
// [15:0] Fractional Baud-Rate Divisor

#define UARTFBRD_0        ( *((volatile uint32_t *) 0x4000C028) )
#define UARTFBRD_1        ( *((volatile uint32_t *) 0x4000D028) )
#define UARTFBRD_2        ( *((volatile uint32_t *) 0x4000E028) )
#define UARTFBRD_3        ( *((volatile uint32_t *) 0x4000F028) )
#define UARTFBRD_4        ( *((volatile uint32_t *) 0x40010028) )
#define UARTFBRD_5        ( *((volatile uint32_t *) 0x40011028) )
#define UARTFBRD_6        ( *((volatile uint32_t *) 0x40012028) )
#define UARTFBRD_7        ( *((volatile uint32_t *) 0x40013028) )


/* Reg 7: UART Line Control (offset: 0x02C) */
// 7: Stick Parity Sel, 6:5 UART Word Length, 4: En FIFOs, 3: Two Stop Bit Sel
// 2: Even Parity Sel, 1: UART Parity En, 0: UART Send Break

#define UARTLCRH_0        ( *((volatile uint32_t *) 0x4000C02C) )
#define UARTLCRH_1        ( *((volatile uint32_t *) 0x4000D02C) )
#define UARTLCRH_2        ( *((volatile uint32_t *) 0x4000E02C) )
#define UARTLCRH_3        ( *((volatile uint32_t *) 0x4000F02C) )
#define UARTLCRH_4        ( *((volatile uint32_t *) 0x4001002C) )
#define UARTLCRH_5        ( *((volatile uint32_t *) 0x4001102C) )
#define UARTLCRH_6        ( *((volatile uint32_t *) 0x4001202C) )
#define UARTLCRH_7        ( *((volatile uint32_t *) 0x4001302C) )


/* Reg 8: UART Control (offset: 0x030) */
// 15: CTSEN, 14: RTSEN, 11: RTS, 9: RXE, 8:TXE, 7:LBE
// 5: HSE, 4: EOT, 3: SMART, 2: SIRLP, 1: SIREN, 0: UARTEN

#define UARTCTL_0        ( *((volatile uint32_t *) 0x4000C030) )
#define UARTCTL_1        ( *((volatile uint32_t *) 0x4000D030) )
#define UARTCTL_2        ( *((volatile uint32_t *) 0x4000E030) )
#define UARTCTL_3        ( *((volatile uint32_t *) 0x4000F030) )
#define UARTCTL_4        ( *((volatile uint32_t *) 0x40010030) )
#define UARTCTL_5        ( *((volatile uint32_t *) 0x40011030) )
#define UARTCTL_6        ( *((volatile uint32_t *) 0x40012030) )
#define UARTCTL_7        ( *((volatile uint32_t *) 0x40013030) )


/* Reg 18: UART Clk Config (offset: 0xFC8) */
// [3:0]: Sys Clk (0x0), PIOSC (0x5),

#define UARTCC_0        ( *((volatile uint32_t *) 0x4000CFC8) )
#define UARTCC_1        ( *((volatile uint32_t *) 0x4000DFC8) )
#define UARTCC_2        ( *((volatile uint32_t *) 0x4000EFC8) )
#define UARTCC_3        ( *((volatile uint32_t *) 0x4000FFC8) )
#define UARTCC_4        ( *((volatile uint32_t *) 0x40010FC8) )
#define UARTCC_5        ( *((volatile uint32_t *) 0x40011FC8) )
#define UARTCC_6        ( *((volatile uint32_t *) 0x40012FC8) )
#define UARTCC_7        ( *((volatile uint32_t *) 0x40013FC8) )


// PULSE WIDTH MODULATOR (PWM) -----------------------------------------------

/* Reg 1: PWM Master Control (offset: 0x000) */

#define PWMCTL_0        ( *((volatile uint32_t *) 0x40028000) )
#define PWMCTL_1        ( *((volatile uint32_t *) 0x40029000) )


/* Reg 2: PWM Time Base Sync (offset: 0x004) */

#define PWMSYNC_0       ( *((volatile uint32_t *) 0x40028004) )
#define PWMSYNC_1       ( *((volatile uint32_t *) 0x40029004) )


/* Reg 3: PWM Output Enable (offset: 0x008) */

#define PWMENABLE_0     ( *((volatile uint32_t *) 0x40028008) )
#define PWMENABLE_1     ( *((volatile uint32_t *) 0x40029008) )


/* Reg 4: PWM Output Inversion (offset: 0x00C) */

#define PWMINVERT_0     ( *((volatile uint32_t *) 0x4002800C) )
#define PWMINVERT_1     ( *((volatile uint32_t *) 0x4002900C) )


/* Reg 5: PWM Output Fault (offset: 0x010) */

#define PWMFAULT_0      ( *((volatile uint32_t *) 0x40028010) )
#define PWMFAULT_1      ( *((volatile uint32_t *) 0x40029010) )


/* Reg 6: PWM Interrupt Enable (offset: 0x014) */

#define PWMINTEN_0      ( *((volatile uint32_t *) 0x40028014) )
#define PWMINTEN_1      ( *((volatile uint32_t *) 0x40029014) )


/* Reg 7: PWM Raw Interrupt Status (offset: 0x018) */

#define PWMRIS_0        ( *((volatile uint32_t *) 0x40028018) )
#define PWMRIS_1        ( *((volatile uint32_t *) 0x40029018) )


/* Reg 8: PWM Interrupt Status and Clear (offset: 0x01C) */

#define PWMISC_0        ( *((volatile uint32_t *) 0x4002801C) )
#define PWMISC_1        ( *((volatile uint32_t *) 0x4002901C) )


/* Reg 9: PWM Status (offset: 0x020) */

#define PWMSTATUS_0     ( *((volatile uint32_t *) 0x40028020) )
#define PWMSTATUS_1     ( *((volatile uint32_t *) 0x40029020) )


/* Reg 10: PWM Fault Condition Value (offset: 0x024) */

#define PWMFAULTVAL_0   ( *((volatile uint32_t *) 0x40028024) )
#define PWMFAULTVAL_1   ( *((volatile uint32_t *) 0x40029024) )


/* Reg 11: PWM Enable Update (offset: 0x028) */

#define PWMENUPD_0      ( *((volatile uint32_t *) 0x40028028) )
#define PWMENUPD_1      ( *((volatile uint32_t *) 0x40029028) )


/* Reg 12: PWM0 Control (offset: 0x040) */
/* Reg 13: PWM1 Control (offset: 0x080) */
/* Reg 14: PWM2 Control (offset: 0x0C0) */
/* Reg 15: PWM3 Control (offset: 0x100) */

#define PWM0CTL_0       ( *((volatile uint32_t *) 0x40028040) )
#define PWM0CTL_1       ( *((volatile uint32_t *) 0x40029040) )
#define PWM1CTL_0       ( *((volatile uint32_t *) 0x40028080) )
#define PWM1CTL_1       ( *((volatile uint32_t *) 0x40029080) )
#define PWM2CTL_0       ( *((volatile uint32_t *) 0x400280C0) )
#define PWM2CTL_1       ( *((volatile uint32_t *) 0x400290C0) )
#define PWM3CTL_0       ( *((volatile uint32_t *) 0x40028100) )
#define PWM3CTL_1       ( *((volatile uint32_t *) 0x40029100) )


/* Reg 16: PWM0 Interrupt and Trigger Enable (offset: 0x044) */
/* Reg 17: PWM1 Interrupt and Trigger Enable (offset: 0x084) */
/* Reg 18: PWM2 Interrupt and Trigger Enable (offset: 0x0C4) */
/* Reg 19: PWM3 Interrupt and Trigger Enable (offset: 0x104) */

#define PWM0INTEN_0     ( *((volatile uint32_t *) 0x40028044) )
#define PWM0INTEN_1     ( *((volatile uint32_t *) 0x40029044) )
#define PWM1INTEN_0     ( *((volatile uint32_t *) 0x40028084) )
#define PWM1INTEN_1     ( *((volatile uint32_t *) 0x40029084) )
#define PWM2INTEN_0     ( *((volatile uint32_t *) 0x400280C4) )
#define PWM2INTEN_1     ( *((volatile uint32_t *) 0x400290C4) )
#define PWM3INTEN_0     ( *((volatile uint32_t *) 0x40028104) )
#define PWM3INTEN_1     ( *((volatile uint32_t *) 0x40029104) )


/* Reg 20: PWM0 Raw Interrupt Status (offset: 0x048) */
/* Reg 21: PWM1 Raw Interrupt Status (offset: 0x088) */
/* Reg 22: PWM2 Raw Interrupt Status (offset: 0x0C8) */
/* Reg 23: PWM3 Raw Interrupt Status (offset: 0x108) */

#define PWM0RIS_0       ( *((volatile uint32_t *) 0x40028048) )
#define PWM0RIS_1       ( *((volatile uint32_t *) 0x40029048) )
#define PWM1RIS_0       ( *((volatile uint32_t *) 0x40028088) )
#define PWM1RIS_1       ( *((volatile uint32_t *) 0x40029088) )
#define PWM2RIS_0       ( *((volatile uint32_t *) 0x400280C8) )
#define PWM2RIS_1       ( *((volatile uint32_t *) 0x400290C8) )
#define PWM3RIS_0       ( *((volatile uint32_t *) 0x40028108) )
#define PWM3RIS_1       ( *((volatile uint32_t *) 0x40029108) )


/* Reg 24: PWM0 Interrupt Status and Clear (offset: 0x04C) */
/* Reg 25: PWM1 Interrupt Status and Clear (offset: 0x08C) */
/* Reg 26: PWM2 Interrupt Status and Clear (offset: 0x0CC) */
/* Reg 27: PWM3 Interrupt Status and Clear (offset: 0x10C) */

#define PWM0ISC_0       ( *((volatile uint32_t *) 0x4002804C) )
#define PWM0ISC_1       ( *((volatile uint32_t *) 0x4002904C) )
#define PWM1ISC_0       ( *((volatile uint32_t *) 0x4002808C) )
#define PWM1ISC_1       ( *((volatile uint32_t *) 0x4002908C) )
#define PWM2ISC_0       ( *((volatile uint32_t *) 0x400280CC) )
#define PWM2ISC_1       ( *((volatile uint32_t *) 0x400290CC) )
#define PWM3ISC_0       ( *((volatile uint32_t *) 0x4002810C) )
#define PWM3ISC_1       ( *((volatile uint32_t *) 0x4002910C) )


/* Reg 28: PWM0 Load (offset: 0x050) */
/* Reg 29: PWM1 Load (offset: 0x090) */
/* Reg 30: PWM2 Load (offset: 0x0D0) */
/* Reg 31: PWM3 Load (offset: 0x110) */

#define PWM0LOAD_0      ( *((volatile uint32_t *) 0x40028050) )
#define PWM0LOAD_1      ( *((volatile uint32_t *) 0x40029050) )
#define PWM1LOAD_0      ( *((volatile uint32_t *) 0x40028090) )
#define PWM1LOAD_1      ( *((volatile uint32_t *) 0x40029090) )
#define PWM2LOAD_0      ( *((volatile uint32_t *) 0x400280D0) )
#define PWM2LOAD_1      ( *((volatile uint32_t *) 0x400290D0) )
#define PWM3LOAD_0      ( *((volatile uint32_t *) 0x40028110) )
#define PWM3LOAD_1      ( *((volatile uint32_t *) 0x40029110) )


/* Reg 32: PWM0 Counter (offset: 0x054) */
/* Reg 33: PWM1 Counter (offset: 0x094) */
/* Reg 34: PWM2 Counter (offset: 0x0D4) */
/* Reg 35: PWM3 Counter (offset: 0x114) */

#define PWM0COUNT_0     ( *((volatile uint32_t *) 0x40028054) )
#define PWM0COUNT_1     ( *((volatile uint32_t *) 0x40029054) )
#define PWM1COUNT_0     ( *((volatile uint32_t *) 0x40028094) )
#define PWM1COUNT_1     ( *((volatile uint32_t *) 0x40029094) )
#define PWM2COUNT_0     ( *((volatile uint32_t *) 0x400280D4) )
#define PWM2COUNT_1     ( *((volatile uint32_t *) 0x400290D4) )
#define PWM3COUNT_0     ( *((volatile uint32_t *) 0x40028114) )
#define PWM3COUNT_1     ( *((volatile uint32_t *) 0x40029114) )


/* Reg 36: PWM0 Compare A (offset: 0x058) */
/* Reg 37: PWM1 Compare A (offset: 0x098) */
/* Reg 38: PWM2 Compare A (offset: 0x0D8) */
/* Reg 39: PWM3 Compare A (offset: 0x118) */

#define PWM0CMPA_0      ( *((volatile uint32_t *) 0x40028058) )
#define PWM0CMPA_1      ( *((volatile uint32_t *) 0x40029058) )
#define PWM1CMPA_0      ( *((volatile uint32_t *) 0x40028098) )
#define PWM1CMPA_1      ( *((volatile uint32_t *) 0x40029098) )
#define PWM2CMPA_0      ( *((volatile uint32_t *) 0x400280D8) )
#define PWM2CMPA_1      ( *((volatile uint32_t *) 0x400290D8) )
#define PWM3CMPA_0      ( *((volatile uint32_t *) 0x40028118) )
#define PWM3CMPA_1      ( *((volatile uint32_t *) 0x40029118) )


/* Reg 40: PWM0 Compare B (offset: 0x05C) */
/* Reg 41: PWM1 Compare B (offset: 0x09C) */
/* Reg 42: PWM2 Compare B (offset: 0x0DC) */
/* Reg 43: PWM3 Compare B (offset: 0x11C) */

#define PWM0CMPB_0      ( *((volatile uint32_t *) 0x4002805C) )
#define PWM0CMPB_1      ( *((volatile uint32_t *) 0x4002905C) )
#define PWM1CMPB_0      ( *((volatile uint32_t *) 0x4002809C) )
#define PWM1CMPB_1      ( *((volatile uint32_t *) 0x4002909C) )
#define PWM2CMPB_0      ( *((volatile uint32_t *) 0x400280DC) )
#define PWM2CMPB_1      ( *((volatile uint32_t *) 0x400290DC) )
#define PWM3CMPB_0      ( *((volatile uint32_t *) 0x4002811C) )
#define PWM3CMPB_1      ( *((volatile uint32_t *) 0x4002911C) )


/* Reg 44: PWM0 Generator A Control (offset: 0x060) */
/* Reg 45: PWM1 Generator A Control (offset: 0x0A0) */
/* Reg 46: PWM2 Generator A Control (offset: 0x0E0) */
/* Reg 47: PWM3 Generator A Control (offset: 0x120) */

#define PWM0GENA_0      ( *((volatile uint32_t *) 0x40028060) )
#define PWM0GENA_1      ( *((volatile uint32_t *) 0x40029060) )
#define PWM1GENA_0      ( *((volatile uint32_t *) 0x400280A0) )
#define PWM1GENA_1      ( *((volatile uint32_t *) 0x400290A0) )
#define PWM2GENA_0      ( *((volatile uint32_t *) 0x400280E0) )
#define PWM2GENA_1      ( *((volatile uint32_t *) 0x400290E0) )
#define PWM3GENA_0      ( *((volatile uint32_t *) 0x40028120) )
#define PWM3GENA_1      ( *((volatile uint32_t *) 0x40029120) )


/* Reg 48: PWM0 Generator B Control (offset: 0x064) */
/* Reg 49: PWM1 Generator B Control (offset: 0x0A4) */
/* Reg 50: PWM2 Generator B Control (offset: 0x0E4) */
/* Reg 51: PWM3 Generator B Control (offset: 0x124) */

#define PWM0GENB_0      ( *((volatile uint32_t *) 0x40028064) )
#define PWM0GENB_1      ( *((volatile uint32_t *) 0x40029064) )
#define PWM1GENB_0      ( *((volatile uint32_t *) 0x400280A4) )
#define PWM1GENB_1      ( *((volatile uint32_t *) 0x400290A4) )
#define PWM2GENB_0      ( *((volatile uint32_t *) 0x400280E4) )
#define PWM2GENB_1      ( *((volatile uint32_t *) 0x400290E4) )
#define PWM3GENB_0      ( *((volatile uint32_t *) 0x40028124) )
#define PWM3GENB_1      ( *((volatile uint32_t *) 0x40029124) )


#endif