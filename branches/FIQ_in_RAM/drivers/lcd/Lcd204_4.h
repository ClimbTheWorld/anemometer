/**
 * \addtogroup lcd
 * @{
 *
 * \author Lukas Kempf
 * \brief Logging entries and message and queue2file handling
 * 
 * 
 *
 *
 */

//*****************************************************************************
//
// logging.h - Prototypes for handling log files
//
//*****************************************************************************

#ifndef _LCDTASK_H_
#define _LCDTASK_H_

#include "FreeRTOS.h"
#include "task.h"

// Typendefinition
//typedef unsigned char BYTE;
//typedef unsigned int  word;
//typedef unsigned long dword;

/** TODO: LCD on wird später über GPIO und FET geschaltet. Bis dahin fix eingeschaltet. */

#define LCD_BLIGHT_ON() (GPIO0_FIOSET  |= (1<<2))  // P0.2         
#define LCD_E1_SET()    (GPIO1_FIOPIN2 |= (1<<5)) // P1.21
#define LCD_RS_SET()    (GPIO1_FIOPIN2 |= (1<<7)) // P1.23
#define LCD_RW_SET()    (GPIO1_FIOPIN2 |= (1<<6)) // P1.22
#define LCD_RES_SET()   (GPIO1_FIOPIN2 |= (1<<0)) // P1.16 Reset 
#define LCD_DATA7_SET() (GPIO1_FIOPIN2 |= (1<<1)) // P1.17
#define LCD_DATA6_SET() (GPIO1_FIOPIN2 |= (1<<2)) // P1.18
#define LCD_DATA5_SET() (GPIO1_FIOPIN2 |= (1<<3)) // P1.19
#define LCD_DATA4_SET() (GPIO1_FIOPIN2 |= (1<<4)) // P1.20

#define LCD_BLIGHT_OFF() (GPIO0_FIOCLR |= (1<<2))            
#define LCD_E1_CLR()    (GPIO1_FIOPIN2 &= ~(1<<5)) 
#define LCD_RS_CLR()    (GPIO1_FIOPIN2 &= ~(1<<7)) 
#define LCD_RW_CLR()    (GPIO1_FIOPIN2 &= ~(1<<6)) 
#define LCD_RES_CLR()   (GPIO1_FIOPIN2 &= ~(1<<0)) 
#define LCD_DATA7_CLR() (GPIO1_FIOPIN2 &= ~(1<<1))
#define LCD_DATA6_CLR() (GPIO1_FIOPIN2 &= ~(1<<2)) 
#define LCD_DATA5_CLR() (GPIO1_FIOPIN2 &= ~(1<<3)) 
#define LCD_DATA4_CLR() (GPIO1_FIOPIN2 &= ~(1<<4)) 

#define LCD_ON
#define LCD_E1()    (GPIO1_FIOPIN2 |= (1>>5)) 
#define LCD_RS()    (GPIO1_FIOPIN2 |= (1>>7)) 
#define LCD_RW()    (GPIO1_FIOPIN2 |= (1>>6)) 
#define LCD_RES()   (GPIO1_FIOPIN2 |= (1>>0)) 
#define LCD_DATA7() (GPIO1_FIOPIN2 & (1<<1))
#define LCD_DATA6() (GPIO1_FIOPIN2 |= (1>>2)) 
#define LCD_DATA5() (GPIO1_FIOPIN2 |= (1>>3)) 
#define LCD_DATA4() (GPIO1_FIOPIN2 |= (1>>4)) 
#define SPALTEN_MAX   20
#define ZEILEN_MAX    4

signed portBASE_TYPE lcdTaskStart (void);
signed portBASE_TYPE lcdTaskStop (void);

void init_screenpool(void);

#endif