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

#include "FreeRTOS.h"

#include "timer.h"
#include "core/rtc/rtc.h"
#include <time.h>

/*************************************************************************************************
 * Timer 1
 ************************************************************************************************/
void timer1Init (void)
{
  SCB_PCONP |= SCB_PCONP_PCTIM1; // Powerup timer1
}
int counter=0;

// CAP0.0 at P0.22
void capture13Init(void) 
{
  timer1Init();
  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P021_MASK) | PCB_PINSEL1_P021_CAP13;

  VIC_IntSelect &= ~VIC_IntSelect_Timer1; // IRQ Interrupt
  VIC_VectAddr12 = (portLONG) timer1ISR; // VectAddr12 hab ich mal so gewählt (ohne Hintergründe)
  VIC_VectCntl12 = VIC_VectCntl_ENABLE | VIC_Channel_Timer1;
  VIC_IntEnable = VIC_IntEnable_Timer1;
  portENTER_CRITICAL();
  
  // Prescale to a frequency that is good enough to get a decent resolution,
  // but not so fast that it overflows all the time.
  /* TimerCounter increments every time when the PrescaleCounter (counts on PCLK) reaches its terminal count defined in the PrescaleRegister.
     for example: PCLK = 48MHz, FrequencyDesired = 1us, PR = 48MHz/(1/1us) = 48.
     configCPU_CLOCK_HZ ^= 48MHz
    */

  T1_PR =  0xBB79;// 47000-1ms // ( configCPU_CLOCK_HZ / 48UL ) - 1UL; // 499999

  /* TimerCounter and MR3 enables the system to recognize that there is a flowrate=0.  
     After 10 seconds of no reaction we decide the system-pump is in halt mode / flowrate = 0.
     TC counts up every 1us -> 1s/1us = 10000000
   */
  
  //  Reset timer counter and prescaler counter registers:  
  T1_TCR = 2;
  // Configure capture channel 0 to capture on the rising edge: 
  T1_CCR |= T_CCR_CAP3RE | T_CCR_CAP3I;
  // Enable the timer:
  T1_TCR = 1;
  //Counter Mode: TC is incremented on rising edges on the CAP1.3@P0.21
  T1_CTCR =  1;

  portEXIT_CRITICAL ();

}

void timer1FlowRateStart(void) {
  T0_TC = 0;
  T0_TCR = T_TCR_CE;
}

void timer1FlowRateContinue(void) {
  T0_TCR = T_TCR_CE;
}

double timer1FlowRateStop(void) {
  const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;
  T0_TCR &= ~T_TCR_CE;
  // long time = T1_TC [x ms] + 1/configCPU_CLOCK_HZ*T0_PC
  float time = T0_TC + 1/configCPU_CLOCK_HZ * T0_PC;
  return T0_TC; // T0_TC * 1ms = 
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
  //acknowledge timer0 interrupt (overflow)
  T1_IR |= T_IR_CR3;
  
  
  if(T1capIntCount == -1)
  {
    //  Reset timer counter and prescaler counter registers:  
    T1_TCR = 2;  
  }
  
  if(T1capIntCount == 10) 
  {
    // 10 periods counted; calculate frequency;
    // In the interrupt routine copy the capture value into a dummy variable:
    T1capTimeCount = T1_CR3;
    T1capFrequency = (short)(1000.0/T1_CR3);
    debug_printf("f: %d\r\n", T1capFrequency);
    
    //  Reset timer counter and prescaler counter registers:  
    T1_TCR = 2;
    // Disable the timer:
    T1_TCR &= ~(1<<1);

    T1capIntCount = 0;
  }
  else
    T1capIntCount += 1;
  
  VIC_VectAddr = (unsigned portLONG) 0;
}

void clrT1capIntCount(void)
{
  T1capIntCount = 0;
  T0_TC = 0;
}

short getT1capIntCount(void)
{
  return T1capIntCount;
}

long getT1capTime(void)
{
  return T1capTimeCount;
}

