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
static volatile char fintcount = 0;
static volatile short __windPeriod = -1;
static volatile float _tmp = -1.0;
static volatile long save_interrupts=0;
static volatile unsigned long val=-1;
void timer1Init (void);
int capture13Init(void);
void timer1FlowRateInit(void);
static void timer1ISR_Handler (void);
void timer0ISR(void);
void timer1ISR(void) __attribute__ ((naked));

int getWindPeriod(void);
void clrWindPeriod(void);
int getFIntCount(void);
void clrFIntCount(void);
long getVal(void);
=======
int getFIntCount(void);
#endif
