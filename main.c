/**************************************************************************/
/*! 
    \file     main.c
    \author   K. Townsend
    \date     23 September 2009
    \version  1.00
*/
/**************************************************************************/

#include <stdlib.h>
#include <time.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "monitor/monitor.h"
#include "core/cpu/cpu.h"
#include "sysdefs.h"


#ifdef CFG_LED && (CFG_LED_RUNLEDONSTARTUP == 1)
#include "drivers/leds/leds.h"
#endif

#ifdef CFG_LCD
#include "drivers/lcd/lcd204_4.h"
#endif

#if defined CFG_RTC
#include "core/rtc/rtc.h"
#endif

#ifdef CFG_MONITOR_UART0
  #include "core/uart/uart0.h"
#endif

#ifdef CFG_MONITOR_USBSER
  #include "core/usbser/usbser.h"
#endif

#ifdef CFG_ADC
  #include "core/adc/adc.h"
#endif
#if 1
  #include "fatfs/ff.h"
#endif
#ifdef CFG_PLAY_STARTUP
  #include "core/timer/beep.h"
#endif

#ifdef CFG_DATALOGGER
  #include "logging.h"/* st�ndlich wird die Queue auf die SD Karte geschrieben, daher 12 Eintr�ge der L�nge _SLOG_ENTRY_ITEM */
  #include "meas_sm.h"
  #include "flowrate_sensor.h"
#endif
/**************************************************************************/
/*! 
    Starts the PotiTask task and performs any initialisation activity
*/
/**************************************************************************/
//static portTASK_FUNCTION(vPotiTask, pvParameters __attribute__((unused))) 
//{
//  /* The LEDs are updated every 200 ticks, about 200 ms */
//  const long blinkDelay = 200;
//
//  
//  FATFS Fatfs[_DRIVES]; /* File system object for each logical drive */
//  FIL File1; /* File objects */
//  printf("DISKINIT %d\r", diskInitialize(0));
//  /* Initialize logical drive */
//  //LUKFRESULT res = f_mount(0, &Fatfs[0]);
//  printf("MOUNT %d\n\r", f_mount(0, &Fatfs[0]));
//
//  /* Create file system */
//  
//  printf("MKFS %d\n", f_mkfs((U8) 0, (U8) 0, (U8) 512));
//
//  printf("MKDIR %d\n", f_mkdir("100602_wast_log\0")); // Ordner anlegen
//
//  printf("OPEN %d\n", f_open(&File1, "log.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ));
//
//  //f_printf(&File1, "%6d", -200);
//  UINT byte_len;
//  U16 bw;
//
//  printf("WRITE %d\n", f_write(&File1, "zalue", strlen("zalue"), &bw));
//
//  printf("CLOSE %d\n", f_close(&File1));
//
//  /* Unregister work area prior to discard it */
//  printf("UMOUNT %d\n", f_mount(0, NULL));
//
//  while (1)
//  {
//    /* Block the task for the defined time */
//    vTaskDelay(blinkDelay);
//
//  }
//
//}


/**************************************************************************/
/*! 
    Starts the main monitor task and performs any initialisation activity
*/
/**************************************************************************/
static portTASK_FUNCTION(vStartupTask, pvParameters __attribute__((unused))) 
{
  for (;;)
  {    
/* The LEDs are updated every 200 ticks, about 200 ms */
  const long blinkDelay = 500;

/* st�ndlich wird die Queue auf die SD Karte geschrieben, daher 12 Eintr�ge der L�nge _SLOG_ENTRY_ITEM */
    
    #if defined CFG_RTC
    // Initialise RTC
    rtcInit();
    #endif

//    struct tm alarm;
//    alarm.tm_sec = 30;
//    alarm.tm_min = 12;
//    alarm.tm_hour = 16;
//    alarm.tm_year = 2011;
//    alarm.tm_mday = 25;
//    alarm.tm_mon = 1;
//    rtcSetAlarm(&alarm);

    // LED2 einschalten
    GPIO0_FIODIR |= (1<<11);
    GPIO0_FIOCLR |= (1<<11);
    
    #if 1
    rtcSetAlarmCIIR(RTC_CIIR_IMMIN);
    #endif

    #if defined CFG_LED && CFG_LED_RUNLEDONSTARTUP == 1
    // Start LED flasher (for testing purposes)
    ledsTaskStart();
    #endif

    #ifdef CFG_LCD
    /** making the contrast of the display evaluated best round 2.6V */
    PCB_PINSEL1 = (PCB_PINSEL1 & ~PCB_PINSEL1_P025_MASK) | PCB_PINSEL1_P025_AOUT;
    // vDAC = VALUE / 1024 * vREF -> VALUE = 2.6V * 1024 / 3.3V = 806.8
    DAC_CR = (DAC_CR & ~DAC_CR_VALUEMASK) | ((806 << DAC_CR_VALUESHIFT) & DAC_CR_VALUEMASK);
    
    eint0Init();

    lcdTaskStart();
    vTaskPrioritySet(taskHandles[TASKHANDLE_LCD], (tskIDLE_PRIORITY + 3));
    #endif

    #ifdef CFG_DATALOGGER
    trackLogTaskStart(); /* creates tracker(does daily and monthly savings to SD card) state-machine and add it to the kernel */
    #if 1
    #ifdef testWithoutADC || testAllFunctions
    #else
    measTaskStart(); /* creates measurement task (does the AD conversion and impuls-time-measurement) and add it to the kernel */
    vTaskSuspend(taskHandles[TASKHANDLE_MEASTASK]);
    #endif
    measSMTaskStart(); /* creates measurement state-machine and add it to the kernel */
    #endif
    #endif

    // Start monitor task
    monitorTaskStart();
    //xTaskCreate (vMonitorTask,  (const signed portCHAR * const) "Monitor", 3000, NULL, (tskIDLE_PRIORITY + 3), &taskHandles [TASKHANDLE_MONITOR]);
    //xTaskCreate (vPotiTask, (const signed portCHAR * const)"Poti", 3000, NULL, configMAX_PRIORITIES, &taskHandles[TASKHANDLE_POTI]);
    //xTaskCreate (vPotiTask,  (const signed portCHAR * const) "POTI", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1), &taskHandles [TASKHANDLE_POTI]);

    #if CFG_PLAY_STARTUP
    //timer1Init();
    //beepMHALL();
    //beepSMOTW();
    //beepA_TEAM_THEME();
    #endif

    
    // Remove startup task.  The monitor will only start after the current
    // task is deleted since 'Startup' has a higher priority.
    vTaskDelete(NULL);
  }
}


/**************************************************************************/
/*! 
    Starts the SetTime task
*/
/**************************************************************************/
//static portTASK_FUNCTION(vSetTime, pvParameters __attribute__((unused))) 
//{
//  // Print out actual time and date
//  int DD=0, MM=0, YYYY=0, HH=0, mm=0, ss=0;
//  char cDD[2]="uu", cMM[2]="uu", cYYYY[4]="uuuu", cHH[2]="uu", cmm[2]="uu", css[2]="uu";
//  DD = RTC_DOM, MM = RTC_MONTH, YYYY = RTC_YEAR, HH = RTC_HOUR, mm = RTC_MIN, ss = RTC_SEC;
//
//  /* The LEDs are updated every 200 ticks, about 200 ms */
//  const long blinkDelay = 200;
//
//  // Print out actual time and date
//  
//  DD = RTC_DOM;
//  MM = RTC_MONTH;
//  YYYY = RTC_YEAR;
//  HH = RTC_HOUR;
//  mm = RTC_MIN;
//  ss = RTC_SEC;
//  printf("Actual Date and Time (YYYY-MM-DD_HH-mm-ss):\r\n%d-%d-%d_%d-%d-%d\r\nSet new date and time as suggested\r\n", YYYY,MM,DD,HH,mm,ss);
//  
//  static char datetime[20]="uuuuuuuuuuuuuuuuuu";
//  while (1)
//  {
//    while(datetime[17]=='u') uart0GetRxQueue(&datetime);
//    if (datetime[0]!='u') {
//      cDD[2]=datetime[7], datetime[8];
//      cMM[2]=datetime[5], datetime[6];
//      cYYYY[4]=datetime[0], datetime[1], datetime[2], datetime[3];
//      cHH[2]=datetime[10], datetime[11];
//      cmm[2]=datetime[13], datetime[14];
//      css[2]=datetime[16], datetime[17];
//
//      printf("New Date and Time (YYYY-MM-DD_HH-mm-ss):\r\n%s-%s-%s_%s-%s-%s\r\n", cYYYY, cMM, cDD, cHH, cmm, css);
//    }
//    
//
//    /* Block the task for the defined time */
//    vTaskDelay(blinkDelay);
//
//  }
//}






/**************************************************************************/
/*! 
    The application entry point.  Initialise the CPU, open the monitor
    'port', create the startup task and begin the task scheduler.
 */
/**************************************************************************/
int main(void)
{
  // Setup the system clocks and put all peripherals in an appropriate default state
  cpuSetupHardware();

  #ifdef CFG_MONITOR_UART0
  // Configure UART0 for Monitor input/output
  uart0Init(9600, 80);
  #endif

  #ifdef CFG_MONITOR_USBSER
  // Configure USB Serial Port for Monitor input/output (9600/8N1)
  usbserInit();
  #endif

  // Create the startup task
  xTaskCreate (vStartupTask, (const signed portCHAR * const)"Startup", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES, &taskHandles[TASKHANDLE_STARTUP]);

  // Start the task scheduler
  vTaskStartScheduler();

  
  // You should only ever reach this point if there isn't enough memory to start the scheduler
  return 0;
}

/**************************************************************************/
/*! 
    Configures Timer1 for FreeRTOS run time stat monitoring.  To enable
    run time stats set configGENERATE_RUN_TIME_STATS to '1' in
    FreeRTOSConfig.h.

    \note For more information on run time stats monitoring see: 
    http://www.freertos.org/rtos-run-time-stats.html
*/
/**************************************************************************/
#if configGENERATE_RUN_TIME_STATS == 1
void vConfigureTimerForRunTimeStats( void )
{
    const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

    // Power up timer1
    SCB_PCONP |= SCB_PCONP_PCTIM1;
	
    // Reset the timer
    T1_TCR = TCR_COUNT_RESET;
	
    // Just count up
    T1_CTCR = CTCR_CTM_TIMER;

    // Prescale to a frequency that is good enough to get a decent resolution,
    // but not so fast that it overflows all the time.
    T1_PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

    // Start the counter
    T1_TCR = TCR_COUNT_ENABLE;
}
#endif


/**************************************************************************/
/*! 
    Hook when a stack overflow occurs if configCHECK_FOR_STACK_OVERFLOW
    is set to 1 or 2 in FreeRTOSConfig.h

    \note For more information on stack overflow in FreeRTOS see: 
    http://www.freertos.org/Stacks-and-stack-overflow-checking.html
*/
/**************************************************************************/
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* Check pcTaskName for the name of the offending task, or pxCurrentTCB
	if pcTaskName has itself been corrupted. */
	( void ) pxTask;
	( void ) pcTaskName;
	for( ;; );
}

/**************************************************************************/
/*! 
    Redirects printf output to either UART0 or USBSER (as defined in
    ProjectConfig.h)
*/
/**************************************************************************/
void __putchar(char c) 
{
  // Use UART0 for printf output
  #ifdef CFG_MONITOR_UART0
  uart0PutChar(c, 5);
  #endif

  // Use USB Serial for printf output
  #ifdef CFG_MONITOR_USBSER
  usbserPutChar(c, 5);
  #endif
}



