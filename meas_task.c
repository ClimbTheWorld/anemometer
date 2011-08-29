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
// meas_sm.c - Measurement state-machine
//
//*****************************************************************************

/* std lib includes */
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "meas_task.h"
#include "meas_sm.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* FatFs includes */
#include "logging.h"
#include "fatfs/ff.h"
#include "flowrate_sensor.h"


/* Measurement driver includes*/
#include "core/adc/adc.h"


/**
 * Mess Item -> Einzelner Messvorgang Panel Temperatur
 *
  \verbatim
  \dot
  digraph finite_state_machine {
          rankdir=SS;
          size="8,5";
          node [shape = doublecircle]; OFF, IDLE;
          node [shape = circle]; READ;
          OFF -> IDLE [label = "measure()"]
          IDLE -> READ [label = "measure()"]
          READ -> IDLE [label = "meas_sm()"]
  }
  \enddot
  \endverbatim
 *
 */
enum _LOG_ITEM_STATE meas_Temp(char meas_op_key) {
  switch (meas_op_item[meas_op_key].state) {
    case OFF:       { /* WILL NOT BE USED */ 
                      break; }
    case INIT:      { /* init P0.21, ADC1.6 */ 
                      meas_op_item[meas_op_key].state = IDLE; /*  going to wait */
                      break; }
    case IDLE:      { /* measure and calculate from int to voltage */ 
                      meas_op_item[meas_op_key].state = START; /*  going to wait */
                    }
    case START:     { /* launch of measure */
                      meas_op_item[meas_op_key].value = -1;
                      /** TODO: start AD conversion here */
                      portENTER_CRITICAL ();
                      meas_op_item[meas_op_key].measInit(); // adcInit
                      //LUK enter critical
                      meas_op_item[meas_op_key].value = meas_op_item[meas_op_key].measRead(); // adcRead

                      //LUK quit critical
                      portEXIT_CRITICAL ();
                      // LED2 ausschalten
                      GPIO0_FIOSET |= (1<<11);
                      meas_op_item[meas_op_key].value = getTemperatureOfADCValue(meas_op_item[meas_op_key].value);
                      while ( meas_op_item[meas_op_key].value == -1 ); // wait
                      meas_op_item[meas_op_key].state = SAVEVALUE; /*  going to wait */
                    }
//      WAITING:   { /* waiting on end of conversion */ 
//                   break; }
    case SAVEVALUE: { /** - data ready to be saved into queue, SD card / UART....., 
                        * - meas_sm() sets the state back to idle afterwards
                        * - switch off no longer required peripherals (AD...) */ 
                      break; 
                    }
  }
  return meas_op_item[meas_op_key].state;
}

double getTemperatureOfADCValue(int valADC) {

  /*
   *   Rth(uADC) = uADC * R25 / (Vcc - uADC ) = uADC * 12000 / (5 - uADC)
   *
   *   t(Rth) = (1/T0 + 1/B * ln(Rth/R25))^(-1)
   */
    volatile double rTh = 0;
    volatile double temperature = 0, temp=0;
    volatile double uADC = 0; // [mV]
    if (valADC == 0) {

    }
    else {
      /* Berechnung: 
       *
       * f�r Temperaturwiderstand 12kOhm @ 25�C (Typ 2322 640 90004 12kOhm/25�C, http://www.ortodoxism.ro/datasheets/vishay/__23226409.pdf)
       *
       *                      AD->V           calc value to 5V
       * uADC = valADC      * 3.3/1024      * 5/3.3
       *
       * Rth(uADC)
       * rTh  = uADC        * R25           / (Vcc - uADC)
       *
       * T'   = 1/298.15    + 1/3750        * ln(rTh/12000)
       *
       * T[�C]= 1/T'        -293.15
       */
      uADC        = (double)valADC*5/1024.0;
      rTh         = (double) (uADC * 12000 / (5 - uADC));
      temp        = 1/298.15 + 1/3750.0 * (log(rTh)-log(12000));
      temperature = 1/ temp -273.15;
    }

    return temperature;
}
              
void meas_task_init(void) {
//  strcpy(meas_op_item[0].name, "TPanel");
  meas_op_item[0].value    = -1;
  meas_op_item[0].pt2func  = meas_Temp;
  meas_op_item[0].measInit = adcPanelInit;
  meas_op_item[0].measRead = adcPanelRead;
  meas_op_item[0].state    = INIT;
  
//  strcpy(meas_op_item[1].name, "TBoiler_oben");
  meas_op_item[1].value    = -1;
  meas_op_item[1].pt2func  = meas_Temp;
  meas_op_item[1].measInit = adcBoilerObenInit;
  meas_op_item[1].measRead = adcBoilerObenRead;
  meas_op_item[1].state    = INIT;
  
//  strcpy(meas_op_item[2].name, "TBoiler_unten");
  meas_op_item[2].value   = -1;
  meas_op_item[2].pt2func = meas_Temp;
  meas_op_item[2].measInit = adcBoilerUntenInit;
  meas_op_item[2].measRead = adcBoilerUntenRead;
  meas_op_item[2].state   = INIT;
  
//  strcpy(meas_op_item[3].name, "TRuecklauf");
  meas_op_item[3].value   = -1;
  meas_op_item[3].pt2func = meas_Temp;
  meas_op_item[3].measInit = adcRuecklaufInit;
  meas_op_item[3].measRead = adcRuecklaufRead;
  meas_op_item[3].state   = INIT;
     
  /** meas_op_item: [0]:  Temperatur Panel
   *                [1]:  Temperatur Boiler oben
   *                [2]:  Temeratur Boiler unten
   *                [3]:  Temperatur R�cklauf
   *                [4]:  Flowmeter
   */
}

void doMeasure(void) {
  /** here we call the ADCs and measure the impulstime from the flowrate. 
      afterwards we set the values_received flag and kill ourselves from the tasklist 
  */
  int i=0;
  enum _LOG_ITEM_STATE ret_state = START;
  for(i=0; i< MEAS_OP_ITEMS; i++) {
    ret_state = meas_op_item[i].pt2func(i);
      //      if(ret_state != SAVEVALUE)/* not every meas_op was successful (eventually there is some exception handling todo) */
      //        printf ("not every meas_op was successful");
    meas_op_item[i].state = IDLE;
  }
  set_valuesReceived();
}

/**************************************************************************/
/*! 
    The main code that will execute as long as the task is active.
    The first parameter (vMyTask in this case) needs to match the
    name used when the task is created in the method just below.
*/
/**************************************************************************/
static portTASK_FUNCTION(vMeasTask, pvParameters __attribute__((unused)))
{
  // Do any required initialisation or 
  // set up any hardware before the task
  // begins executing for the first time

  // ToDo: ...

  // The code within the for loop is your actual
  // task that will continously execute
  
  for (;;)
  {
    if(valuesReceived() == -1); // wait - do nothing
    else if(valuesReceived() == 0) {  // start measure
      doMeasure();
    }
    

    vTaskResume(taskHandles[TASKHANDLE_MEASSM]);
    // suspend this task
    vTaskSuspend(NULL);

    // vTaskDelay will cause the task to be delayed for 
    // a specified number of ticks
    // vTaskDelay(100);  // Wait 100 ticks or 1 second
  }
}


/**************************************************************************/
/*! 
    Creates a new task for the FreeRTOS Kernel and add it to the
    scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE measTaskStart (void)
{
  return xTaskCreate (
    vMeasTask,
    (const signed portCHAR * const) "Measure_Task",
    configMINIMAL_STACK_SIZE, // ^= ((unsigned portSHORT) 128)^=configMINIMAL_STACK_SIZE
    NULL,
    (tskIDLE_PRIORITY + 4),
    &taskHandles [TASKHANDLE_MEASTASK]);
}

/**************************************************************************/
/*! 
    Stops the task and deletes it from the task scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE measTaskStop (void)
{
  if (!taskHandles [TASKHANDLE_MEASTASK])
    return 0;
  
  vTaskDelete (taskHandles [TASKHANDLE_MEASTASK]);
  taskHandles [TASKHANDLE_MEASTASK] = NULL;

  return 1;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
