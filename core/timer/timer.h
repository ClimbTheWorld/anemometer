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
void timer1Init (void);
void timer1FlowRateInit(void);
static void timer1ISR_Handler (void);
//void timer0ISR(void);
void timer1ISR(void) __attribute__ ((naked));

// counts the capture interrupts. after 10 periods the frequency will be calculated.
static short T1capIntCount = -1;

// after 10 periods the value of the T1_CR13 will be saved in this variable. It's the 1/10 frequency.
static long T1capTimeCount = 0;

static short T1capFrequency = 0;

void clrT1capIntCount(void);

long getT1capTimeCount(void);
#endif
