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
#include <time.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
//#include "queue.h"

/* FatFs includes */
#include "fatfs/ff.h"

/* Measurement driver includes*/
#include "core/adc/adc.h"
#include "core/timer/timer.h"
#include "ProjectConfig.h"
#include "meas_sm.h"
#include "meas_task.h"
#include "logging.h"
#include "core/eints/eint3.h"
#include "flowrate_sensor.h"

/**
 * Mess State-Machine -> verwaltet die einzelnen meas_item()
 * @return State of the state machine

\dot
digraph finite_state_machine {
	rankdir=SS;
	size="8,5"
	node [shape = doublecircle]; OFF;
	node [shape = circle]; INIT, IDLE, START, SAVEVALUE; 
	OFF  -> INIT  [ label = "startup" ];
        INIT -> IDLE [ label = "init system" ];
        IDLE -> START [ label = "rtc interrupt" ];
        START -> SAVEVALUE [ label = "wait on complete" ];
        SAVEVALUE -> IDLE [ label = "save on SD" ];
}
\enddot

 */
enum _LOG_ITEM_STATE meas_sm() {
  switch (state_LOGGER) {
    case OFF:       { clr_measure();
                      break; 
                    }
    case INIT:      { /* call measurement item init functions */
                      /* iterate through */
                      int i=0; 
                      /*LUK 2011-03-24: wird in Pumpenstellsignal/ und Pumpenstellsignal\ verwendet.*/ // initMeasure_timestamp();
                      initMeasure_timestamp();
                      clr_measure();
                      clr_valuesReceived();
                      clr_updateLCD();

                      setWsPrice(WsPriceRappenStandardValue);
                      init_daysLogging(); 
                      
                      // init meas_op items
                      for(i=0; i<(MEAS_OP_ITEMS); i++) {
                        meas_op_item[i].pt2func(i);
                      }
                      initFlowrateSensor();
                      
                      state_LOGGER = IDLE; /* state change from INIT to IDLE*/
                      clr_measure();
                      break; 
                    }
    case IDLE:      { if (get_measure() == 2 ) { 
                        state_LOGGER = START; // go directly (within this interrupt) to START
                        //clr_measure(); 
                      }
                      else { /* do nothing, wait until RTC kicks */ }
                    }
    case START:     { /* call measure functions */ 
                      
//*START***********this will be done in a seperate task *****************************************************************************************/
//                      /* get new values */
//                      enum _LOG_ITEM_STATE ret_state = START;
//                      //LUK for(i=0; i<MEAS_OP_ITEMS; i++) {
//                      for(i=MEAS_OP_ITEMS-1; i>=0; i--) {
//                        ret_state = meas_op_item[i].pt2func(i);
//                          if(ret_state != SAVEVALUE)/* not every meas_op was successful (eventually there is some exception handling todo) */
//                            printf ("not every meas_op was successful");
//                        meas_op_item[i].state = IDLE;
//                        taskYIELD();
//                      }
//                      // wait on all measurements have completed
//                      // fill slog_entry_item
//*END*************************************************************************************************************************************END**/
//                        int i=0;
//                        enum _LOG_ITEM_STATE ret_state = START;
//                        for(i=0; i< MEAS_OP_ITEMS; i++) {
//                          ret_state = meas_op_item[i].pt2func(i);
//                      //      if(ret_state != SAVEVALUE)/* not every meas_op was successful (eventually there is some exception handling todo) */
//                      //        printf ("not every meas_op was successful");
//                          meas_op_item[i].state = IDLE;
//                        }
  //set_valuesReceived();

                      //startMeasure();
                      //vTaskResume(taskHandles[TASKHANDLE_MEASTASK]);
                      //vTaskSuspend(NULL);
                      // waiting until 
                      //while(0 == valuesReceived()) {
                      //  taskYIELD();                      
                      //}
                        meas_op_item[0].value = 30;
                        meas_op_item[1].value = 33;
                        meas_op_item[2].value = 32;
                        meas_op_item[3].value = 31;
                        //meas_op_item[].value = 66;
                      stopMeasure();

                      //strcpy(datetime, "YYYY-MM-DD;HH-mm-ss");
                      getRtcRead (ts);
//                      ts.tm_year += 1900;
//                      ts.tm_mon += 1;
                      /*LUK 2011-03-24: wird in Pumpenstellsignal/ und Pumpenstellsignal\ verwendet.*/ //updateMeasure_timestamp(mktime(ts)); /** TODO: mktime macht vermutlich nicht die richtige Zeit aus ts */
                      updateMeasure_timestamp(mktime(ts));
                      /* Format and print the time, "YYYY-MM-DD;HH(24h)-mm-ss" */
                      //getDateTime(datetime);
                      fillSlogEntryItem(meas_op_item[0].value, meas_op_item[1].value, meas_op_item[2].value, meas_op_item[3].value);
                      //fillSlogEntryItem(datetime, (unsigned short)3300, (unsigned short)2300, (unsigned short)1200, (unsigned short)1024, (unsigned short)100);
                      
                      // add to SDCARD BUFFER
                      // slog_entry_item.datetime, .val_adc1, .val_adc2, .val_adc3, .val_adc4, .flowvolume, .power
            //LUK 2011-05-25: neu ist buf von 59 auf 20 verkleinert worden. Erhoffe mir weniger stack probleme.
//                      strftime(buf, sizeof("YYYY-MM-DD;HH-mm-ss;"), "%Y-%m-%d;%T;", ts); // length = 20
                      
                      //sprintf(buf+20, "%d;%d;%d;%d;%2.1f;%d;\r\n", slog_entry_item.val_adc1, slog_entry_item.val_adc2, slog_entry_item.val_adc3, slog_entry_item.val_adc4, slog_entry_item.flowvolume, slog_entry_item.power);
//                      sprintf(buf+20, "%d;%d;%d;%d;%f;%d;\r\n", slog_entry_item.val_adc1, slog_entry_item.val_adc2, slog_entry_item.val_adc3, slog_entry_item.val_adc4, slog_entry_item.flowvolume, slog_entry_item.power);
                      
                     
                      state_LOGGER = SAVEVALUE; // go directly to the SAVEVALUE state
                      //taskYIELD();
                      //clr_measure();
                    }
    case SAVEVALUE: { /* enqueue, update continues reports, write2SD  */
                      /*
                       *   if (11 == uxQueueMessagesWaiting( slog_queue )) {
                       *     char buf[] = 0; // SDCARD BUFFER
                       *     enqueue
                       *     _SLOG_ENTRY_ITEM queuedEntry;
                       *     while ((queuedEntry = xQueueReceive()) != 0) {
                       *       update cday
                       *       buf += queuedEntry 
                       *     }
                       *     flush queue
                       *     if (hour == 23) {
                       *       update cdaylog_entry_item
                       *       buf += cdaylog_entry_item
                       *       update cmonthlog_entry_item
                       *       update 
                       *       if (last_day_of_month)
                       *         buf += cmonthlog_entry_item
                       *     }
                       *     write buf2SD
                       *     
                       */ 
                      /*********************************************************************/
                        
                      /*********************************************************************/
                      #if 1
                      #ifdef LOG2FATFS
                      int ret=-1;
/* append to continuous log file created on startup */
                      //printf("OPEN contLog.txt %d\n", f_open(&FileContLog, "contLog.txt", FA_OPEN_EXISTING | FA_WRITE | FA_READ));
                      getLogFilename(contLog, logFilename);
                      if(FR_EXIST == f_open(&FileContLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ)) {
                        ret = f_open(&FileContLog, logFilename, FA_OPEN_EXISTING | FA_WRITE | FA_READ);
                      }
                      /* Move to end of the file to append data */
                      ret = f_lseek(&FileContLog, FileContLog.fsize); //LUK param2 von f_lseek war FileContLog->fsize --> error 2011-01-08
                      
                      strftime(buf, sizeof("YYYY-MM-DD;HH-mm-ss;"), "%Y-%m-%d;%T;", ts); // length = 20
                      ret = f_write(&FileContLog, buf, strlen(buf), &bw);
                      sprintf(buf, "%d;%d;%d;%d;%3.1f;%d;\r\n", slog_entry_item.val_adc1, slog_entry_item.val_adc2, slog_entry_item.val_adc3, slog_entry_item.val_adc4, slog_entry_item.flowvolume, slog_entry_item.power);
                      ret = f_write(&FileContLog, buf, strlen(buf), &bw);
                      ret = f_close(&FileContLog);
                      #endif 

                      #ifdef logCDaySummary
                      /** update cdayLog; will be saved to SD from trackLog Task */
                      updateCDayLogEntryItem();
                      #endif
                     
                      #ifdef logAllTimeSummary
                      /** update clog; will be saved every last day of month in getLogFilename(allTimeSummery) */  
                      updateCLogEntryItem();
                      #endif
                      
                      int i=0;
                      for(i=0;i<MEAS_OP_ITEMS;i++) {
                        meas_op_item[i].state = IDLE;
                      }
                      state_LOGGER = IDLE;
                      clr_measure();
                      //trackLogTaskStart();
                      #endif
                    }
  }
  return state_LOGGER;
}


/**************************************************************************/
/*! 
    The main code that will execute as long as the task is active.
    The first parameter (vMeasSM in this case) needs to match the
    name used when the task is created in the method just below.
*/
/**************************************************************************/
static portTASK_FUNCTION(vMeasSM, pvParameters __attribute__((unused)))
{
  // Do any required initialisation or 
  // set up any hardware before the task
  // begins executing for the first time
  
  // ToDo: ...
  enum _LOG_ITEM_STATE item_state;

  ts =  (struct tm *)malloc(sizeof(struct tm));

  /** structure holding all measure-jobs; here we switch on/off the processes 
  * we want  to get measured by the system.
  * If the initial state is OFF --> no values will be measured
  * If the initial state is INIT --> values will be measured
  */
  
  /* set structs to a defined state */
//  strcpy(slog_entry_item.datetime, "00000000000000000000");       /* YYYY-MM-DD_HH-mm(24h)-ss */
  slog_entry_item.val_adc1=-1;      /* Value 0-Aref(3300) [mV] */
  slog_entry_item.val_adc2=-1;      /* Value 0-Aref(3300) [mV] */
  slog_entry_item.val_adc3=-1;      /* Value 0-Aref(3300) [mV] */
  slog_entry_item.val_adc4=-1;      /* Value 0-Aref(3300) [mV] */
  //slog_entry_item.val_flowrate=-1;  /* Value to be defined */

  // meas_task_init is called at meas_task startup
    
//#if 0
//  slog_queue =  xQueueCreate( 12, 28 /* sizeof(_SLOG_ENTRY_ITEM) = 19+2+2+2+2+1 = 28 */ );
//    if (slog_queue ==  0)
//      printf("slog_queue couldn't be created. Logging not possible!!! Restart application.");
//    vQueueAddToRegistry( slog_queue, "slog_queue" );
//#endif


  /* init FS */
  //#ifdef LOG2FATFS
/* init files: if they already exists, the function fails, but 'das tangiärt iis periphär */
// FA_CREATE_NEW	Creates a new file. The function fails with FR_EXIST if the file is existing.
//getLogFilename(0, logFilename);
//f_open(&FileContLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ);
//getLogFilename(1, logFilename);
//f_open(&FileDayLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ);
//getLogFilename(2, logFilename);
//f_open(&FileMonthLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ);

//    printf("OPEN YYYY-dayLog.txt %d\n", f_open(&FileDayLog, logFilename[1], FA_CREATE_ALWAYS | FA_WRITE | FA_READ));
//    printf("WRITE %d\n", f_write(&FileDayLog, "LogFile created and holds the following: dayLog entries\r\n", strlen("LogFile created and holds the following: dayLog entries\r\n"), &bw));
//    printf("CLOSE %d\n", f_close(&FileDayLog));
//    
//    printf("OPEN YYYY-mm-monthLog.txt %d\n", f_open(&FileMonthLog, logFilename[2], FA_CREATE_ALWAYS | FA_WRITE | FA_READ));
//    printf("WRITE %d\n", f_write(&FileMonthLog, "LogFile created and holds the following: monthLog entries\r\n", strlen("LogFile created and holds the following: monthLog entries\r\n"), &bw));
//    printf("CLOSE %d\n", f_close(&FileMonthLog));
    
    //printf("UMOUNT %d\n", f_mount(0, NULL));
  //#endif
  
//  timer1FlowRateInit();
//  timer1FlowRateStart();
  FRESULT res = f_mount(0, &Fatfs[0]);

  state_LOGGER = INIT;
  // The code within the for loop is your actual
  // task that will continously execute
  for (;;)
  {
//    vTaskSuspend(taskHandles[TASKHANDLE_LED]);
//    #ifdef CFG_LCD
//    vTaskSuspend(taskHandles[TASKHANDLE_LCD]);
//    #endif

    if ( get_measure()==1 ) {
      set_measure(2);
      //updateMeasure_timestamp(mktime(ts));
      item_state = meas_sm();
    }

    //debug_printf("Counted: %d\r\n", timer1FlowRateStop());
    //timer1FlowRateStart();
    
//    vTaskResume(taskHandles[TASKHANDLE_LED]);
//    #ifdef CFG_LCD
//    vTaskResume(taskHandles[TASKHANDLE_LCD]);
//    #endif

    // suspend this task
    //vTaskSuspend(NULL);
    vTaskDelay(100);
  }
}

/**************************************************************************/
/*! 
    Creates a new task for the FreeRTOS Kernel and add it to the
    scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE measSMTaskStart (void)
{
  return xTaskCreate (
    vMeasSM,
    (const signed portCHAR * const) "Measure_SM",
    (unsigned portSHORT) 376, // ^= ((unsigned portSHORT) 128)^=configMINIMAL_STACK_SIZE
    NULL,
    (tskIDLE_PRIORITY + 3),
    &taskHandles [TASKHANDLE_MEASSM]);
}

/**************************************************************************/
/*! 
    Stops the task and deletes it from the task scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE MeasSMTaskStop (void)
{
  if (!taskHandles [TASKHANDLE_MEASSM])
    return 0;
  
  vTaskDelete (taskHandles [TASKHANDLE_MEASSM]);
  taskHandles [TASKHANDLE_MEASSM] = NULL;

  return 1;
}


//void set_measure(struct MEASURE pMeasure) { 
//  measure.rtc_ciir  |= pMeasure.rtc_ciir;
//  measure.rtc_alarm |= pMeasure.rtc_alarm;
//}
//void clr_measure(struct MEASURE pMeasure) { 
//  measure.rtc_ciir  &= ~pMeasure.rtc_ciir;
//  measure.rtc_alarm &= ~pMeasure.rtc_alarm;
//}
//struct MEASURE get_measure(void) 
//{ return struct MEASURE measure; }

void set_measure(char value) { __measure = value; }
void clr_measure(void) { __measure = 0; }
char get_measure(void) { return __measure; }

void set_updateLCD(void) { __updateLCD = 1; }
void clr_updateLCD(void) { __updateLCD = 0; }
char get_updateLCD(void) { return __updateLCD; }

void set_trackLog(void) { __trackLog = 1; }
void clr_trackLog(void) { __trackLog = 0; }
char get_trackLog(void) { return __trackLog; }

double get_pumpLastControlSignalOn(void) { return pumpLastControlSignalOn; }
void set_pumpLastControlSignalOn(void)   { pumpLastControlSignalOn = mktime(ts);}
void clr_pumpLastControlSignalOn(void)   { pumpLastControlSignalOn = 0; }

/**
 * [0]:act, [1]:old, [2]:delta 
 * @return delta time between measure_timestamp_old and measure_timestamp_act
*/
float updateMeasure_timestamp(time_t updatetime) {
  measure_timestamp[2] = difftime (measure_timestamp[0], updatetime);
  measure_timestamp[1] = measure_timestamp[0];
  measure_timestamp[0] = updatetime;
  return measure_timestamp[2];
}

static void initMeasure_timestamp(void) {
  /* initialize timestamp to be able to calculate delta-t's. It's only called when first 5min increment interrupt kicks  */
  measure_timestamp[0] = time (NULL);
  measure_timestamp[1] = measure_timestamp[0]+1;
}

float getMeasure_timestamp_diff(void) { return measure_timestamp[2]; }

/* the variable __valuesReceived acts as indicator for the AD-value conversion task.
 * -1: means stop/halt
 * 0:  means start conversion
 * 1:  means conversion is done. results are available
 *
 * with stopMeasure the task stopps, with startMeasure it's getting launched.
*/
void clr_valuesReceived(void) { __valuesReceived = 0; }
void set_valuesReceived(void) { __valuesReceived = 1; }
char valuesReceived(void) { return __valuesReceived; }

void stopMeasure(void) { __valuesReceived = -1; }
void startMeasure(void) { __valuesReceived = 0; }

/* flowcount is for counting the flow-impulses/ exchanged-volume */
float get_FlowCount(void) { return flowCount; }
float incr_FlowCount(void) { flowCount += (float)flowrateMeterImpulsVolume; return flowCount; }
float clr_FlowCount(void) { float endValue = flowCount; flowCount = 0; return endValue; }

int initFlowrateSensor(void) {
  #if 1
  // P0.3 as EINT1 Pumpenstellsignal
  PCB_PINSEL0 = (PCB_PINSEL0 & ~PCB_PINSEL0_P03_MASK) | PCB_PINSEL0_P03_EINT1;

  /* rest of EINT0 initialisation is done in \core\eints\eint0.c\eint0Init() -> already done for LPC-P2148\Button2 */
  // things will be done in eint0ISR() 
  #endif

  // P0.30 as EINT3 FlowrateSensor
  PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P030_EINT3) | PCB_PINSEL1_P030_EINT3;
  eint3Init();
  // things will be done in eint3ISR()

  clr_FlowCount();
  
  return 0;
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
