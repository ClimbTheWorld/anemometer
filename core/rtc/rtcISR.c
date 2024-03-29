/**************************************************************************/
/*! 
    \file     rtcISR.c
    \author   Original Code: J.C. Wren
              Modified By: K. Townsend (microBuilder.eu)
    \date     9 November 2009
    \version  1.00
*/
/**************************************************************************/

#include <stdlib.h>
#include "lpc214x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#if defined CFG_MONITOR_USBSER
#include "../usbser/usbser.h"
#elif defined CFG_MONITOR_UART0
#include "../uart/uart0.h"
#else
#error "Eeek!  No console devices defined!"
#endif

#include "rtcISR.h"
#include "rtc.h"
//#include "meas_sm.h" 

static xQueueHandle consoleQueue = NULL;

void rtcISRInit (void)
{
//#if defined CFG_MONITOR_USBSER
//  usbserGetRxQueue (&consoleQueue);
//#elif defined CFG_MONITOR_UART0
//  uart0GetRxQueue (&consoleQueue);
//#else
//#error "Eeek!  No console devices defined!"
//#endif
}


static void rtcISR_Handler (void)
{
  portBASE_TYPE higherPriorityTaskWoken = pdFALSE;

  RTC_CCR = (RTC_CCR_CLKEN | RTC_CCR_CLKSRC);
  SCB_PCONP |= SCB_PCONP_PCRTC;

  /* if increment alarm interrupt fired - here every minute */
  if (RTC_ILR & RTC_ILR_RTCCIF) 
  {
    U8 c = 0xff;
      startMeasure();
      
      set_measure(1);
      xTaskResumeFromISR(taskHandles[TASKHANDLE_MEASSM]);
      xTaskResumeFromISR(taskHandles[TASKHANDLE_MEASTASK]);
      
//    if (consoleQueue) {
//      xQueueSendFromISR (consoleQueue, &c, &higherPriorityTaskWoken);
//    }

    /* flowCount will be cleared always after the measurement at 23.55h*/

    #if CFG_LCD == 1
    // updateLCD every 5 minutes with an offset of 4 minutes
//    if((RTC_MIN == 42) | (RTC_MIN == 4) | (RTC_MIN == 9) | (RTC_MIN == 14) | (RTC_MIN == 19) | (RTC_MIN == 24) | (RTC_MIN == 29) | (RTC_MIN == 34) | (RTC_MIN == 39) | (RTC_MIN == 44) | (RTC_MIN == 49) | (RTC_MIN == 54) | (RTC_MIN == 59)) {
//      set_updateLCD();
//      xTaskResumeFromISR(taskHandles[TASKHANDLE_LCD]);
//      
//    }
    #endif
    RTC_ILR = RTC_ILR_RTCCIF;
  }

  /* if time specific alarm interrupt fired */
  if (RTC_ILR & RTC_ILR_RTCALF) 
  {
    U8 c = 0xfe;

//    if (consoleQueue)
//      xQueueSendFromISR (consoleQueue, &c, &higherPriorityTaskWoken);

    RTC_ILR = RTC_ILR_RTCALF;
  }

  VIC_VectAddr = (unsigned portLONG) 0;

  RTC_CCR = (RTC_CCR_CLKEN | RTC_CCR_CLKSRC);
  SCB_PCONP &= ~SCB_PCONP_PCRTC;

  if (higherPriorityTaskWoken)
    portYIELD_FROM_ISR ();
}

void rtcISR (void) __attribute__ ((naked));
void rtcISR (void)
{
  portSAVE_CONTEXT ();
  rtcISR_Handler ();
  portRESTORE_CONTEXT ();
}
