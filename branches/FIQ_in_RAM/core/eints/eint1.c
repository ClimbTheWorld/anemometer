//
//  $Id: eint1.c 159 2008-10-17 01:32:05Z jcw $
//  $Revision: 159 $
//  $Author: jcw $
//  $Date: 2008-10-16 21:32:05 -0400 (Thu, 16 Oct 2008) $
//  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/eints/eint1.c $
//

#include "FreeRTOS.h"

#include "eint1.h"
#include "eint1ISR.h"

//
//
//
#define eint1SetRisingEdge()               ( SCB_EXTPOLAR |= SCB_EXTPOLAR_EINT1 )
#define eint1SetFallingEdge()              ( SCB_EXTPOLAR &= ~SCB_EXTPOLAR_EINT1 )

void eint1Init (void)
{
  portENTER_CRITICAL ();

  //PCB_PINSEL0 = (PCB_PINSEL0 & ~PCB_PINSEL0_P014_MASK) | PCB_PINSEL0_P014_EINT1;
  PCB_PINSEL0 = (PCB_PINSEL0 & ~PCB_PINSEL0_P03_MASK) | PCB_PINSEL0_P03_EINT1;

  // first as rising edge
  SCB_EXTPOLAR |= SCB_EXTPOLAR_EINT1; //  if edge, 1: rising edge
  SCB_EXTMODE  |=  SCB_EXTMODE_EINT1;  // 1: edge sensitive
  SCB_EXTINT   |=  SCB_EXTINT_EINT1;

  VIC_IntSelect &= ~VIC_IntSelect_EINT1;
  VIC_VectAddr8 = (portLONG) eint1ISR;
  VIC_VectCntl8 = VIC_VectCntl_ENABLE | VIC_Channel_EINT1;
  VIC_IntEnable = VIC_IntEnable_EINT1;

  portEXIT_CRITICAL ();
}

void eint1Deinit (void)
{
  VIC_IntEnClr = VIC_IntEnClr_EINT1;

  //PCB_PINSEL0 = (PCB_PINSEL0 & ~PCB_PINSEL0_P014_MASK) | PCB_PINSEL0_P014_GPIO;
  PCB_PINSEL0 = (PCB_PINSEL0 & ~PCB_PINSEL0_P03_MASK) | PCB_PINSEL0_P03_GPIO;
}