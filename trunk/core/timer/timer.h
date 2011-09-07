//
//  $Id: timer.h 324 2008-11-09 04:57:15Z jcw $
//  $Revision: 324 $
//  $Author: jcw $
//  $Date: 2008-11-08 23:57:15 -0500 (Sat, 08 Nov 2008) $
//  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/timer/timer.h $
//

#ifndef _TIMER_H_
#define _TIMER_H_

//
//
//
static volatile short fintcount = -1;
static volatile long __windPeriod = -1;
static volatile long save_interrupts=0;
void timer1Init (void);
void capture13Init(void);
void timer1FlowRateInit(void);
static void timer1ISR_Handler (void);
void timer0ISR(void);
void timer1ISR(void) __attribute__ ((naked));

short getWindPeriod(void);
void clrWindPeriod(void);
#endif