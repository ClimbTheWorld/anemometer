//
//  $Id: eint0ISR.c 128 2008-10-11 14:54:27Z jcw $
//  $Revision: 128 $
//  $Author: jcw $
//  $Date: 2008-10-11 10:54:27 -0400 (Sat, 11 Oct 2008) $
//  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/eints/eint0ISR.c $
//

#include "FreeRTOS.h"

#include "eint0ISR.h"
#include "meas_sm.h"

//
//
//
static void eint0ISR_Handler (void)
{
  #if CFG_LCD
  if(PCB_PINSEL1_P016_GPIO == 0) {
    // go onwards
    set_updateLCD();
    incrementScreen();
    
    xTaskResumeFromISR(taskHandles[TASKHANDLE_LCD]);
  }
  #endif
  
  SCB_EXTINT |= SCB_EXTINT_EINT0;
  
  // determine if Pumpenstellsignal interrupted; read IOPIN0.1 (um10139, Rev. 01 — 15 August 2005, lpp.25)
  /**
  if(P0.1-EINT0-Flag && (GPIO0_IOPIN == 0)) { // hat ausgeschaltet
    disFlowrateInterrupt();
    updateMeasure_timestamp();

    calc volume from flowCount

    update slog; write2SD
    update cdaylog that it switched off
  }
  else if(P0.1-EINT0-Flag && (GPIO0_IOPIN == 1)) // hat eingeschaltet
    clearFlowCount();
    enFlowrateSensor();
    updateMeasure_timestamp();
    
  */
  

  VIC_VectAddr = (unsigned portLONG) 0;
}

void eint0ISR (void) __attribute__ ((naked));
void eint0ISR (void)
{
  portSAVE_CONTEXT ();
  eint0ISR_Handler ();
  portRESTORE_CONTEXT ();
}
