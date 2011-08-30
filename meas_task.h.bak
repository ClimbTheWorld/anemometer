/**
 * \addtogroup logging
 * @{
 *
 * \author Lukas Kempf
 * \brief Measurement state-machine
 *
 *
 */

//*****************************************************************************
//
// meas_sm.h - Measurement state-machine
//
//*****************************************************************************

#ifndef MEAS_TASK_H_
#define MEAS_TASK_H_

/* std lib includes */
#include <string.h>
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* FatFs includes */
#include "logging.h"
#include "fatfs/ff.h"

/* Measurement driver includes*/
#include "core/adc/adc.h"
#include "ProjectConfig.h"

#define MEAS_OP_ITEMS 4

/**
 * Measurement State Machine States
 *
 * { off; Init; Idle; Start; waiting; saveValue }
 *
 */

 /* function declaration */
void doMeasure(void);
enum _LOG_ITEM_STATE meas_task();
signed portBASE_TYPE measTaskStart (void);
signed portBASE_TYPE measTaskStop (void);


typedef struct 
{
    //char name[13]; /* i.e. TPanel or TBoiler_unten */ 
    short value; /* measured value  */
    enum _LOG_ITEM_STATE (*pt2func)(char meas_op_key);
    int (*measInit)(void);
    int (*measRead)(void);
    enum _LOG_ITEM_STATE state; /* state of procedure { OFF, INIT, IDLE, START, SAVEVALUE } */
    //int op; /*  */
}  _MEAS_OP_ITEM;
_MEAS_OP_ITEM meas_op_item[5];
/** meas_op_item: [0]:  Temperatur Panel
 *                [1]:  Temperatur Boiler oben
 *                [2]:  Temeratur Boiler unten
 *                [3]:  Temperatur Rücklauf
 *                [4]:  Flowmeter
 */

/* declaration of measure functions */
enum _LOG_ITEM_STATE meas_Temp(char meas_op_key);
enum _LOG_ITEM_STATE meas_Flowrate(char meas_op_key);
 
double getTemperatureOfADCValue(int valADC);

/** ADCPool enthält die InitFunktion- und ReadFunktion-Pointer der ADCs wiefolgt:
 *  ADCPool[i][j] -> i -> Wahl des MEAS_OP_ITEM, gleicher Index
 *                   j -> Wahl der ReadFunktion: [0]==Init, [1]==Read
 */
//typedef int (*adcPoolTempl)(void); // initialised in meas_sm.c as 'adPool[4][2]'

/** TODO: adcInit gibt nichts zurück, adcRead einen INT */
//adcPoolTempl adcPool[4][2];

void meas_task_init(void);
//typedef void (*myfunc)(int a, char* b); //function pointer declaration.
#endif
