/**************************************************************************/
/*! 
    \file     adc.h
    \author   Original Code: J.C. Wren
              Modified By: K. Townsend (microBuilder.eu)
    \date     23 September 2009
    \version  1.00
*/
/**************************************************************************/

#ifndef _ADC_H_
#define _ADC_H_

/* 10bit Conversion P0.28 */
int adcRead0_1 (void);
int adcInit0_1 (void);

/* 10bit Conversion P0.29 */
int adcRead0_2 (void);
int adcInit0_2 (void);

/* 10bit Conversion P0.30 */
int adcRead0_3 (void);
int adcInit0_3 (void);

/* 10bit Conversion P0.25 */
int adcRead0_4 (void);
int adcInit0_4 (void);

/* 10bit Conversion P0.8 */
int adcRead1_1 (void);
int adcInit1_1 (void);

/* 10bit Conversion P0.12 */
int adcRead1_3 (void);
int adcInit1_3 (void);

/* 10bit Conversion P0.13 */
int adcRead1_4 (void);
int adcInit1_4 (void);

/* 10bit Conversion P0.21 */
int adcRead1_6 (void);
int adcInit1_6 (void);

/* 10bit Conversion P0.22 */
int adcRead1_7 (void);
int adcInit1_7 (void);

/** TODO: switch off functions --> power saving */

#endif