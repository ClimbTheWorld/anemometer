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

struct tm actTime;

void timer0Init (void)
{
  SCB_PCONP |= SCB_PCONP_PCTIM0; // Powerup Timer0
}

void timer1Init (void)
{
  SCB_PCONP |= SCB_PCONP_PCTIM1; // Powerup Timer1
}

// CAP0.0 at P0.30
void capture00Init(void) {
  
}

void timer1FlowRateInit(void) {
  const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;
  
  portENTER_CRITICAL ();

  //PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P016_MASK) | PCB_PINSEL1_P016_EINT0;

  //SCB_EXTPOLAR &= ~SCB_EXTPOLAR_EINT0;
  //SCB_EXTMODE  |=  SCB_EXTMODE_EINT0;
  //SCB_EXTINT   |=  SCB_EXTINT_EINT0;

  // Power up timer1
  SCB_PCONP |= SCB_PCONP_PCTIM1;
      
  // Reset the timer
  T1_TCR = TCR_COUNT_RESET;
      
  // Just count up
  T1_CTCR = CTCR_CTM_TIMER;
  T1_MCR |= (T_MCR_MR3I | T_MCR_MR3R); // Interrupt on MATCH CHANNEL 3 and reset of the counter register


  //T1_MR3 = (unsigned)0xFFFFFFFF;

  // Prescale to a frequency that is good enough to get a decent resolution,
  // but not so fast that it overflows all the time.
  /* TimerCounter increments every time when the PrescaleCounter (counts on PCLK) reaches its terminal count defined in the PrescaleRegister.
     for example: PCLK = 48MHz, FrequencyDesired = 1ms, PR = 48MHz/(1/1ms) = 48000.
     configCPU_CLOCK_HZ ^= 48MHz
    */

  T1_PR =  ( configCPU_CLOCK_HZ / 48000UL ) - 1UL;

  /* TimerCounter and MR3 enables the system to recognize that there is a flowrate=0.  
     After 10 seconds of no reaction we decide the system-pump is in halt mode / flowrate = 0.
     TC counts up every 1ms -> 10s/1ms = 10000
   */
  T1_MR3 = 10000;

  /* ISR */
  VIC_IntSelect |= VIC_IntSelect_Timer1;
  VIC_VectAddr5 = (portLONG) timer1ISR; // VectAddr5 hab ich mal so gewählt (ohne Hintergründe)
  VIC_VectCntl5 = VIC_VectCntl_ENABLE | VIC_Channel_Timer1;
  VIC_IntEnable = VIC_IntEnable_Timer1;

  portEXIT_CRITICAL ();

    // Start the counter
    //T1_TCR = TCR_COUNT_ENABLE;
}

void timer1FlowRateStart(void) {
const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;
  T1_TC = 0;
  T1_TCR = TCR_COUNT_ENABLE;
}

void timer1FlowRateContinue(void) {
const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;
  T1_TCR = TCR_COUNT_ENABLE;
}



double timer1FlowRateStop(void) {
  const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;
  T1_TCR &= ~TCR_COUNT_ENABLE;
  // long time = T1_TC [x ms] + 1/configCPU_CLOCK_HZ*T1_PC
  double time = T1_TC + 1/configCPU_CLOCK_HZ * T1_PC;
  return T1_TC; // T1_TC * 1ms = 
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
  //acknowledge timer1 interrupt (overflow)
  T1_IR |= T_IR_MR3;
  
//  timer1OverflowCnt++;
//  debug_printf("val: %d\r\n", timer1OverflowCnt);
  
  getRtcRead(&actTime);
  char datetime[3];
//  strftime(datetime, sizeof("ss"), "%S", &actTime); 
//  debug_printf("time %s\r\n", datetime);

  //SCB_EXTINT |= SCB_EXTINT_EINT3;

  // Do something

  VIC_VectAddr = (unsigned portLONG) 0;
}
