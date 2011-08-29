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

#ifndef MEAS_SM_H_
#define MEAS_SM_H_

/* std lib includes */
#include <string.h>
#include <stdio.h>
#include <time.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* FatFs includes */
#include "logging.h"
#include "fatfs/ff.h"

/* Measurement driver includes*/
#include "core/adc/adc.h"
#include "meas_task.h"

#define enFlowrateInterrupt()  (PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P030_MASK) | PCB_PINSEL1_P030_EINT3)
#define disFlowrateIntuerrupt() (PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P030_MASK) | PCB_PINSEL1_P030_GPIO)

/* Semaphore to lock access to SD Card. Needed because trackLog() and meas_sm() are writing to the SD Card, so we have to lock the access. */
xSemaphoreHandle xSemaphoreSDCard;

/* function declaration */
enum _LOG_ITEM_STATE meas_sm();
signed portBASE_TYPE measSMTaskStart (void);
signed portBASE_TYPE measSMTaskStop (void);

void set_measure(char value);
void clr_measure(void);
char get_measure(void);

static void initMeasure_timestamp(void);
float updateMeasure_timestamp(time_t updatetime);
float getMeasure_timestamp_diff(void);

void clr_valuesReceived(void);
void set_valuesReceived(void);
char valuesReceived(void);

char get_updateLCD(void);
void set_updateLCD(void);
void clr_updateLCD(void);

double get_pumpLastControlSignalOn(void);
void set_pumpLastControlSignalOn(void);
void clr_pumpLastControlSignalOn(void);

/* flowcount is for counting the flow-impulses/ exchanged-volume to calculate the power for every 5 minutes. */
float get_FlowCount(void);
float incr_FlowCount(void);
float clr_FlowCount(void);

static UINT byte_len;
static U16 bw;

/** To calculate timedifference and upsumming flowrate, energy and so on
 *  [0]:act, [1]:old, [2]:delta 
 */
time_t measure_timestamp[3];
static time_t pumpLastControlSignalOn; // when the pump control signal last time changed to high (pump switched on)
struct tm *ts;
static volatile float flowCount = 0; //LUK 2011-06-01: was 'short'
//char datetime[20];

static enum _LOG_ITEM_STATE state_LOGGER        = INIT;

//static char buf[_SLOG_ENTRY_ITEM_SIZE];                      
char buf[21];                      

//static char value[5]; // wert von Int to Char[] Buffer
static volatile char __measure = 0;
static volatile char __valuesReceived = -1; /* -1=stop, 0=start, 1=received */
static volatile char __updateLCD = 0;
static volatile char __trackLog = 0;
#endif
