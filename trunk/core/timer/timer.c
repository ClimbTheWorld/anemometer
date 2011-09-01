//
//  $Id: timer.c 324 2008-11-09 04:57:15Z jcw $
//  $Revision: 324 $
//  $Author: jcw $
//  $Date: 2008-11-08 23:57:15 -0500 (Sat, 08 Nov 2008) $
//  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/timer/timer.c $
//

//
//  This timer code was contributed by Dave Madden
//
#include <stdio.h>
#include <time.h>
#include "FreeRTOS.h"
#include "core/rtc/rtc.h"

#include "timer.h"


/*************************************************************************************************
 * Timer 1
 ************************************************************************************************/
void timer1Init (void)
{
  SCB_PCONP |= SCB_PCONP_PCTIM1; // Powerup timer1
}

// CAP0.0 at P0.22
void capture13Init(void) 
{
  timer1Init();
  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P021_MASK) | PCB_PINSEL1_P021_CAP13;

  portENTER_CRITICAL();
  
  // Prescale to a frequency that is good enough to get a decent resolution,
  // but not so fast that it overflows all the time.
  /* TimerCounter increments every time when the PrescaleCounter (counts on PCLK) reaches its terminal count defined in the PrescaleRegister.
     for example: PCLK = 48MHz, FrequencyDesired = 1us, PR = 48MHz/(1/1us) = 48.
     configCPU_CLOCK_HZ ^= 48MHz
    */

  T1_PR =  4799;//100us// 4799//47999:1ms // ( configCPU_CLOCK_HZ / 48UL ) - 1UL;

  /* TimerCounter and MR3 enables the system to recognize that there is a flowrate=0.  
     After 10 seconds of no reaction we decide the system-pump is in halt mode / flowrate = 0.
     TC counts up every 1us -> 1s/1us = 10000000
   */
  
  //  Reset timer counter and prescaler counter registers:  
  T1_TCR = 2;
  // Configure capture channel 0 to capture on the rising edge: 
  T1_CCR |= T_CCR_CAP3RE | T_CCR_CAP3I;
  T1_CCR &= ~T_CCR_CAP3FE;
  //Counter Mode: TC is incremented on rising edges on the CAP1.3@P0.21
//  T1_CTCR |= T_CTCR_MODE_PCLK | T_CTCR_CIS_CAPN3;
  // Enable the timer:

  VIC_IntSelect &= ~VIC_IntSelect_Timer1; // (IRQ Interrupt)
  VIC_VectAddr12 = (portLONG) timer1ISR; // VectAddr12 hab ich mal so gewählt (ohne Hintergründe)
  VIC_VectCntl12 = VIC_VectCntl_ENABLE | VIC_Channel_Timer1;
  
  // Interrupt will be enabled as soon as the system wants to take a measurement
  //VIC_IntEnable = VIC_IntEnable_Timer1;
  VIC_IntEnable |= VIC_IntEnable_Timer1;
  portEXIT_CRITICAL ();
}

void timer1ISR(void) __attribute__ ((naked));
void timer1ISR(void) 
{
  portSAVE_CONTEXT ();
  timer1ISR_Handler ();
  portRESTORE_CONTEXT ();
}

static void timer1ISR_Handler (void)
{
  T1_IR |= T_IR_CR3;
  //acknowledge timer1 interrupt (overflow)
  long val = (long) T1_CR3;

  if((fintcount >= 0) && (fintcount <= 10))
  {
    fintcount++;
    if(fintcount==10) {
      __windPeriod = val;
      // Interrupt Disable
      VIC_IntEnable &= ~VIC_IntEnable_Timer1;
      }
  }
  else if(fintcount == -1) 
  {
    fintcount=0;
    T1_TCR = 2;
    T1_TCR = 1;
  }
  VIC_VectAddr = (unsigned portLONG) 0;
}


short getWindPeriod(void)
{
  return (short)__windPeriod;
}

void clrWindPeriod(void)
{
  __windPeriod = -1;
}


//void clrT1capIntCount(void)
//{
//  fintcount = 0;
//  T0_TC = 0;
//}
//
//short getT1capIntCount(void)
//{
//  return fintcount;
//}
//
//long getT1capTime(void)
//{
//  return fintcount;
//}
//
//void incrT1capIntCount()
//{
//  fintcount++;
//}
//
//void timer1FlowRateStart(void) {
//  T0_TC = 0;
//  T0_TCR = T_TCR_CE;
//}
//
//void timer1FlowRateContinue(void) {
//  T0_TCR = T_TCR_CE;
//}
//
//double timer1FlowRateStop(void) {
//  const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;
//  T0_TCR &= ~T_TCR_CE;
//  // long time = T1_TC [x ms] + 1/configCPU_CLOCK_HZ*T0_PC
//  float time = T0_TC + 1/configCPU_CLOCK_HZ * T0_PC;
//  return T0_TC; // T0_TC * 1ms = 
//}
