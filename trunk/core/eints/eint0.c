//
//  $Id: eint0.c 159 2008-10-17 01:32:05Z jcw $
//  $Revision: 159 $
//  $Author: jcw $
//  $Date: 2008-10-16 21:32:05 -0400 (Thu, 16 Oct 2008) $
//  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/eints/eint0.c $
//

#include "FreeRTOS.h"

#include "eint0.h"
#include "eint0ISR.h"

//
//
//
void eint0Init (void)
{
  portENTER_CRITICAL ();

  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P016_MASK) | PCB_PINSEL1_P016_EINT0;

  #ifdef CFG_LCD
  /** use the buttons for changing between the screeens.
      B2(Button closer to the potentiometer to go backwards */
  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P016_MASK) | PCB_PINSEL1_P016_EINT0;
  //
  //  Set for low-active/falling-edge sensitive & edge sensitive, then clear interrupt
  //
  SCB_EXTPOLAR &= ~SCB_EXTPOLAR_EINT0; // falling edge 
  SCB_EXTMODE  |=  SCB_EXTMODE_EINT0; // edge sensitive
  SCB_EXTINT   |=  SCB_EXTINT_EINT0;
  #endif

//  SCB_EXTPOLAR &= ~SCB_EXTPOLAR_EINT0; // falling edge 
//  SCB_EXTMODE  |=  SCB_EXTMODE_EINT0;  // edge sensitive
//  SCB_EXTINT   |=  SCB_EXTINT_EINT0;

  VIC_IntSelect &= ~VIC_IntSelect_EINT0;
  VIC_VectAddr4 = (portLONG) eint0ISR;
  VIC_VectCntl4 = VIC_VectCntl_ENABLE | VIC_Channel_EINT0;
  VIC_IntEnable = VIC_IntEnable_EINT0;

  portEXIT_CRITICAL ();
}

void eint0Deinit (void)
{
  VIC_IntEnClr = VIC_IntEnClr_EINT0;

  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P016_MASK) | PCB_PINSEL1_P016_GPIO;
}
