/**************************************************************************/
/*! 
    \file     spi.h
    \author   Original Code: J.C. Wren
              Modified By: K. Townsend (microBuilder.eu)
              Modified By. L. Kempf (lukaskempf@gmail.com)
    \date     17.3.2011
    \version  1.00
*/
/**************************************************************************/

#ifndef _SPI_H_
#define _SPI_H_

#include "FreeRTOS.h"

void spi1Init (void);
U8 spi1Put (U8 valueIn);

#endif
