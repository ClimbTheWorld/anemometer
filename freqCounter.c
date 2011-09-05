///*
// * Copyright(C) Paul und Scherer (mct.de/mct.net)
// * http://mct.de/download/armsamples/map.html
// * This example demonstrates how to...
// *
// *  ... build a frequency counter
// *      using timer counter mode.
// */
//
//#include <stdio.h>
//#include "lpc214x.h"
////#include <sys/arm7tdmi.h>
////#include <target.h>
//
//static int count;				// counts/s =frequency [Hz]
//
///*
// * Timer0 interrupt service
// *
// * Timer0 generates the gate (1s). During this
// * time, Timer1 counts falling edges at P0.10.
// */
//static void __attribute__((interrupt))		// handle as ISR!
//t0_isr(void)
//{
//	/*
//	 * Read t1 counter
//	 *
//	 * As the gate time is 1 second, the counter
//	 * represents exactly the frequency in Hertz.
//	 */
//	count = T0_TCR;			// update count
//
//	T0_IR = 1;			// clear int flag
//	Intern_vicvectaddr = 0;			// reset VIC priority logic
//
//	Intern_t1tcr = 2;			// restart t1
//	Intern_t1tcr = 1;			//  counter
//	Intern_t0tcr = 2;			// restart
//	Intern_t0tcr = 1;			//  gate time
//}
//
//int
//main(void)
//{
//	Intern_vicvectaddr0 = (long)t0_isr;	// set ISR addr
//	Intern_vicintenable = 0x10;		// enable t0 int
//	Intern_vicvectcntl0 = 0x24;		//  vector
//
//	/*
//	 * Set the gate time to 1 second (subtract the time
//	 * needed to service the interrupt, ca. 40 counts).
//	 */
//	Intern_t0mr0  = _PCLK-1-40;
//	Intern_t0mcr |= 1;			// int on MR0
//
//	/*
//	 * Comment the next line to count the internal clock
//	 * instead of pulses at P0.10. This allows adjusting
//	 * the gate time (the exact value of _PCLK should be
//	 * measured).
//	 */
//	Intern_t1ctcr = 2;			// count CAP1.0 falling edges
//
//	Intern_t1tcr  = 2;			// start t1
//	Intern_t1tcr  = 1;			//  counter
//	Intern_t0tcr  = 1;			// start gate time
//
//	Intern_pinsel0 |= 0x200000;		// enable CAP1.0 (P0.10)
//	ENABLE_INTERRUPTS;			//        core ints
//
//	/*
//	 * Connect P0.10 to a pulse signal source. A simple test:
//	 * Using a short cable as "antenna", "f = 50Hz" should be
//	 * displayed.
//	 *
//	 * Alternatively you can use a PWM output to generate the
//	 * test signal: Choose the desired frequency and tie PWM5
//	 * (=P0.21) to P0.10. The selected frequency should match
//	 * the displayed frequency.
//	 */
//	#define f	100000			// f [Hz]
//	#define T	(_PCLK/f)
//	Intern_pwmmr0   = T;			// set MR0 (rate)
//	Intern_pwmmr5	= T/2;			// 50% duty cycle
//	Intern_pwmmcr  |= 2;			// reset on MR0
//	Intern_pwmpcr  |= 0x2000;		// PWM5 output
//	Intern_pinsel1 |= 0x400;		//      enable
//	Intern_pwmtcr	= 9;			// PWM mode, go...
//
//	while (1) if (count >= 0) printf("f = %dHz\n", count), count = -1;
//}
//
//
//
//
////************************************************************************************
//Enable pin 0.2 as capture channel 0:
//PINSEL0 = 0x00000020;
//Load prescaler with 1 micro second tick value:
//T0PR = 0x0000001E;
//Reset timer counter and prescaler counter registers:
//T0TCR = 0x00000002;
//Configure capture channel 0 to capture on the rising edge: T0CCR = 0x00000005;
//Enable the timer:
//T0TCR = 0x00000001;
//In the interrupt routine copy the capture value into a dummy variable:
//Value = T0CR0;
//Compile and load the code into the debugger
//Run the program and check the following
//Test the capture interrupt is working by setting a breakpoint on the timer ISR, and running
//the code.
//In the simulator a script has been added to the toolbox to generate a pulse on 0.02. If you are
//using the MCB2100 you need to pull the port pin up to Vcc via a 10K resistor.