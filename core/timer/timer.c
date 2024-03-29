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
#include "lpc214x.h"
#include <stdio.h>
#include <time.h>
#include "FreeRTOS.h"
#include "core/rtc/rtc.h"
#include "meas_sm.h"
#include "logging.h"
#include "timer.h"


/*************************************************************************************************
 * Timer 1
 ************************************************************************************************/
void timer1Init (void)
{
  SCB_PCONP |= SCB_PCONP_PCTIM1; // Powerup timer1
}

// CAP0.0 at P0.22
int capture13Init(void) 
{
  #define P021CAP13
  //#define P022CAP00
  timer1Init();
  #ifdef P021CAP13
  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P021_MASK) | PCB_PINSEL1_P021_CAP13;
  #endif
  #ifdef P022CAP00
  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P022_MASK) | PCB_PINSEL1_P022_CAP00;
  #endif
  portENTER_CRITICAL();
  
  // Prescale to a frequency that is good enough to get a decent resolution,
  // but not so fast that it overflows all the time.
  /* TimerCounter increments every time when the PrescaleCounter (counts on PCLK) reaches its terminal count defined in the PrescaleRegister.
     for example: PCLK = 48MHz, FrequencyDesired = 1us, PR = 48MHz/(1/1us) = 48.
     configCPU_CLOCK_HZ ^= 48MHz
    */

  T1_PR =  11999;//1199=250us^=4kHz;//4799=1ms^=1kHz;//100us// 4799//47999:1ms // ( configCPU_CLOCK_HZ / 48UL ) - 1UL;

  /* TimerCounter and MR3 enables the system to recognize that there is a flowrate=0.  
     After 10 seconds of no reaction we decide the system-pump is in halt mode / flowrate = 0.
     TC counts up every 1us -> 1s/1us = 10000000
   */
  
  //  Reset timer counter and prescaler counter registers:  
  T1_TCR = 2;
  // Configure capture channel 0 to capture on the rising edge: 
  #ifdef P021CAP13
  T1_CCR |= T_CCR_CAP3RE | T_CCR_CAP3I;
  T1_CCR &= ~T_CCR_CAP3FE;
  //Counter Mode: TC is incremented on rising edges on the CAP1.3@P0.21
  T1_CTCR |= (T_CTCR_MODE_PCLK | T_CTCR_CIS_CAPN3);
  #endif
  #ifdef P022CAP00
  T1_CCR |= (T_CCR_CAP0RE | T_CCR_CAP0I);
  T1_CCR &= ~T_CCR_CAP0FE;
  //Counter Mode: TC is incremented on rising edges on the CAP1.3@P0.21
  T1_CTCR |= T_CTCR_MODE_PCLK;
  T1_CTCR &= ~T_CTCR_CIS_CAPN0;
  #endif
  VIC_IntSelect &= ~VIC_IntSelect_Timer1; // (IRQ Interrupt)
  VIC_VectAddr12 = (portLONG) timer1ISR; // VectAddr12 hab ich mal so gewählt (ohne Hintergründe)
  VIC_VectCntl12 = (VIC_VectCntl_ENABLE | VIC_Channel_Timer1);
  fintcount = 0;
      // Interrupt will be enabled as soon as the system wants to take a measurement
  VIC_IntEnable |= VIC_IntEnable_Timer1;
  portEXIT_CRITICAL ();
  return 0;
}

//void timer1ISR(void) __attribute__ ((naked));
void timer1ISR(void)__attribute__ ((interrupt("IRQ")));
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

  val = T1_CR3;
  
  meas_op_item[1].value = 0;
  //if((fintcount >= 0) && (fintcount <= 1))
  if(fintcount == 1)
  {
      // Interrupt Disable
      T1_TCR = 2;
      VIC_IntEnClr |= VIC_IntEnable_Timer1;
      SCB_PCONP &= ~SCB_PCONP_PCTIM1; // Powerdown timer1
      //meas_op_item[1].value = val;
      //setWindFrequency(val);
      //fintcount = 0; -> will be done in meas_task; to be able to detect windless
      //xTaskResumeFromISR(taskHandles[TASKHANDLE_MEASTASK]);
      //VIC_IntEnable = save_interrupts;
      VIC_IntEnable &= ~VIC_IntEnable_Timer1;
      SCB_PCONP |= SCB_PCONP_PCTIM1; // Powerdown timer1
      setWindPeriod(val);
      //meas_op_item[1].value = val;
      //setWindPeriodTime(val);
      fintcount = 0;
      // not in use 'cause of the task is on-going and has to stop the interrupt when no interrupt fires(no wind)
      // xTaskResumeFromISR(taskHandles[TASKHANDLE_MEASTASK]);
      xTaskResumeFromISR(taskHandles[TASKHANDLE_MEASSM]);
      //VIC_IntEnable = save_interrupts;
  }
  // first time in this routine; start timer. Do NOT enter this routine when finished, that's why the check on '&& (VIC_IntEnable & VIC_IntEnable_Timer1)' 
  else if((fintcount == 0) && (VIC_IntEnable & VIC_IntEnable_Timer1)) 
  {
    fintcount=1;
    //save_interrupts = VIC_IntEnable & ~VIC_IntEnable_Timer1;
    //VIC_IntEnClr = save_interrupts;
    VIC_IntEnable |= VIC_IntEnable_Timer1;
    T1_TCR = 2;
    T1_CR3 = 0;
    //save_interrupts = VIC_IntEnable & ~VIC_IntEnable_Timer1;
    //VIC_IntEnClr = save_interrupts;
    //VIC_IntEnable |= VIC_IntEnable_Timer1;
    T1_TCR = 1;
  }
  VIC_VectAddr = (unsigned portLONG) 0;
}

void clrWindPeriod(void)
{
  __windPeriod = -1;
}

void setWindPeriod(short value)
{
  __windPeriod = value;
}

int getWindPeriod(void)
{
  return __windPeriod;
}

int getFIntCount(void)
{
  return fintcount;
}

void clrFIntCount(void)
{
  fintcount = 0;
}

long getVal(void)
{
  return val;
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
