/**
 * \addtogroup logging
 * @{
 *
 * \author Lukas Kempf
 * \brief Routines for handling Logging entries and message and queue2file
 *
 *
 */

//*****************************************************************************
//
// logging.c - Routines for handling log files
//
//*****************************************************************************

/* std lib includes */
#include <string.h>
#include <stdio.h>
#include <time.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* FatFs includes */
#include "logging.h"
#include "flowrate_sensor.h"
#include "fatfs/ff.h"

/* Measurement driver includes*/
#include "core/adc/adc.h"
#include "meas_sm.h"

//*****************************************************************************
//
// The following are data structures used by FatFs.
//
//*****************************************************************************
static FATFS g_sFatFs;
#include "fatfs/ff.h"
//#include "lmi_fs.h"
//#include "hw_types.h"

//#include "realtime.h"
//#include "log/logging.h"

//#include "setup.h"
#define ENABLE_LOG 1
#define DEBUG_LOG 1

//char buf[128], 
char time_buf[30];

//void fillSlogEntryItem(char *datetime, unsigned short adc1, unsigned short adc2, unsigned short adc3, unsigned short adc4) {
//void fillSlogEntryItem(time_t datetime, unsigned short adc1, unsigned short adc2, unsigned short adc3, unsigned short adc4) {
void fillSlogEntryItem(unsigned short winddirection, unsigned short winddirection_max, unsigned short windspeed) {
  /* YYYY-MM-DD_HH(24h)-mm-ss */

  //strcpy((char *)slog_entry_item.datetime, datetime); /* YYYY-MM-DD;HH(24h)-mm-ss */
 slog_entry_item.datetime = ts;
  //slog_entry_item.datetime = datetime;
  slog_entry_item.winddirection = winddirection;
  slog_entry_item.windspeed = windspeed;
}

float getWhPriceRappen(void) {
  return WhPriceRappen;
}

void setWsPrice(float WhRappen) { WhPriceRappen = WhRappen; }

/**
  Depending on the parameter given the function returns an appropriate filename. Unfortunately still in a 8+3-Format; i.e. with this CHAN-FatFS Version (Version 0.4)
  @param: char number 0 contLog        Filename e.x. 2011cont.txt
                      1 dayLog         Filename e.x. 2011day.txt
                      2 monthLog       Filename e.x. 2011mont.txt
                      3 allTimeSummary Filename e.x. alltime.txt
  @param: char *filename pointer to buf. sizeof(buf)=59 --> it's the file's buffer
*/
void getLogFilename(char log, char *filename)
{
//LUK 2011-05-26: already defined in meas_sm.h as global  struct tm *ts; 
//LUK 2011-05-26:   ts =  (struct tm *)malloc(sizeof(struct tm));
//LUK 2011-05-26:   getRtcRead (ts);
//LUK 2011-05-26:   memset(filename, '\0', 12); // clear buffer (fills the buffer with '\0' )

  //    (/* �berpr�fen ob bereits vorhanden, allenfalls neues erstellen: YYYY-contLog.txt, YYYY_dayLog.txt, YYYY_monthLog.txt */ )
  // Filename
  strftime(filename, sizeof("YYYY"), "%Y", ts); 
  switch(log) {
    case contLog:         { sprintf(filename+4, "cont.txt");
                            break;
                          }
    case dayLog:          { sprintf(filename+4, "day.txt");
                            break;
                          }
    case monthLog:        { sprintf(filename+4, "mont.txt"); 
                            break;
                          }
     case allTimeSummary: { luk_strcpy(filename, "alltime.txt", 11);
                            break;
                          }
  }
}


void trackLog(void)
{
  //struct tm *ts; // da jetzt dieses struct in meas_sm.h als global
  int ret=-1;
  UINT byte_len;
  U16 bw;

  //ts =  (struct tm *)malloc(sizeof(struct tm));
  getRtcRead (ts);
  //if ((ts->tm_hour == 23) && (ts->tm_min == 55)) {
  if(1) {
    #ifdef logCDaySummary
      /* append to daylog file created on startup */
      getLogFilename(dayLog, logFilename);
      if(FR_EXIST == f_open(&FileDayLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ)) {
        ret = f_open(&FileDayLog, logFilename, FA_OPEN_EXISTING | FA_WRITE | FA_READ);
      }
      /* Move to end of the file to append data */
      ret = f_lseek(&FileDayLog, FileDayLog.fsize); //LUK param2 von f_lseek war FileContLog->fsize --> error 2011-01-08
      /** Format of daylog file
       *  YYYY-MM-DD;HH-mm-ss; sum_flowtime; sum_flowvolume; sum_energy; sum_profit;
       */
      //memset(buf, '\0', 30); // clear buffer (fills the buffer with '\0' )
      sprintf(buf, "%s;%d;%.1f;%d;%d;%d;\r\n", cdaylog_entry_item.last_update, cdaylog_entry_item.sum_flowtime, cdaylog_entry_item.sum_flowvolume, cdaylog_entry_item.sum_energy, cdaylog_entry_item.sum_profit);
      ret = f_write(&FileDayLog, buf, strlen(buf), &bw);
      ret = f_close(&FileDayLog);
      printf("dayLog\r\n%s", buf);
      incr_daysLogging();
      clr_FlowCount(); /* einmal im Tag*/
    #endif

/* if last day of month: cmonthlog_entry_item2SD */
//    if (ts->tm_mday == getMonthLength((char)ts->tm_mon), (char)ts->tm_year) {
//      /* append to monthlog file created on startup */
//      getLogFilename(monthLog, logFilename);
//      if(FR_EXIST == f_open(&FileMonthLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ)) {
//        ret = f_open(&FileMonthLog, logFilename, FA_OPEN_EXISTING | FA_WRITE | FA_READ);
//      }
//      /* Move to end of the file to append data */
//      ret = f_lseek(&FileMonthLog, FileMonthLog.fsize); //LUK param2 von f_lseek war FileContLog->fsize --> error 2011-01-08
//      /** Format of daylog file
//       *  YYYY-MM-DD;HH-mm-ss; sum_flowtime; sum_flowvolume; sum_energy; sum_profit;
//       */
//      memset(buf, '\0', 30); // clear buffer (fills the buffer with '\0' )
//      sprintf(buf, "%s;%d;%d;%d;%d;%d;\r\n", cdaylog_entry_item.last_update, cdaylog_entry_item.sum_flowtime, cdaylog_entry_item.sum_flowvolume, cdaylog_entry_item.sum_energy, cdaylog_entry_item.sum_profit);
//      ret = f_write(&FileMonthLog, buf, strlen(buf), &bw);
//      ret = f_close(&FileMonthLog);
//    }

  #ifdef logAllTimeSummary 
  /* if last day of month: clog_entry_item2SD */
  if (ts->tm_mday == getMonthLength((char)ts->tm_mon), (char)ts->tm_year) {
    clog_entry_item.last_update;        /* YYYY-MM-DD;HH(24h)-mm-ss+'\0' */
    clog_entry_item.sum_flowtime;           /* pumptime[s] */
    clog_entry_item.sum_flowvolume;         /* Value 0-int l */
    clog_entry_item.sum_energy;             /* Value in Ws */
    clog_entry_item.sum_profit;                /* Value in Rappen */
    clog_entry_item.arithm_day_flowtime;     /* pumptime[s]/day */
    clog_entry_item.arithm_day_flowvolume;  /* Value 0-int l */
    clog_entry_item.arithm_day_energy;      /* Value in Ws */
    clog_entry_item.arithm_day_profit;        /* Value in Rappen */

    /* append to monthlog file created on startup */
    getLogFilename(allTimeSummary, logFilename);
    if(FR_EXIST == f_open(&FileAllTimeLog, logFilename, FA_CREATE_NEW | FA_WRITE | FA_READ)) {
      ret = f_open(&FileAllTimeLog, logFilename, FA_OPEN_EXISTING | FA_WRITE | FA_READ);
    }
    /* Move to end of the file to append data */
    ret = f_lseek(&FileAllTimeLog, FileAllTimeLog.fsize); //LUK param2 von f_lseek war FileContLog->fsize --> error 2011-01-08
    
    /** Format of allTimeLog file
     *  YYYY-MM-DD;HH-mm-ss; sum_flowtime; sum_flowvolume; sum_energy; sum_profit;
     */
    // write sum's
    memset(buf, '\0', 30); // clear buffer (fills the buffer with '\0' )
    sprintf(buf, "%s;%d;%d;%d;%d;%d;", clog_entry_item.last_update, daysLogging, clog_entry_item.sum_flowtime, clog_entry_item.sum_flowvolume, clog_entry_item.sum_energy, clog_entry_item.sum_profit);
    ret = f_write(&FileAllTimeLog, buf, strlen(buf), &bw);
    
    // write arithmetic medians
    memset(buf, '\0', 30); // clear buffer (fills the buffer with '\0' )
    sprintf(buf, "%d;%d;%d;%d;\r\n", clog_entry_item.arithm_day_flowtime, clog_entry_item.arithm_day_flowvolume, clog_entry_item.arithm_day_energy, clog_entry_item.arithm_day_profit);
    ret = f_write(&FileAllTimeLog, buf, strlen(buf), &bw);

    ret = f_close(&FileAllTimeLog);
  }
  #endif

  #ifdef logCDaySummary
  //resets cdaylog_entry_item
  //getDateTime(datetime);
  cdaylog_entry_item.last_update = slog_entry_item.datetime;
  cdaylog_entry_item.sum_flowtime = 0;
  cdaylog_entry_item.sum_flowvolume = 0;
  cdaylog_entry_item.sum_energy = 0;
  cdaylog_entry_item.sum_profit = 0;
  #endif
  }
}

/**************************************************************************/
/*! 
    The main code that will execute as long as the task is active.
    The first parameter (vMyTask in this case) needs to match the
    name used when the task is created in the method just below.
*/
/**************************************************************************/
static portTASK_FUNCTION(vTrackLog, pvParameters __attribute__((unused)))
{
  // Do any required initialisation or 
  // set up any hardware before the task
  // begins executing for the first time

  // ToDo: ...

  // The code within the for loop is your actual
  // task that will continously execute
  for (;;)
  {
    if(get_trackLog()) {
      trackLog();
      clr_trackLog();
    }

    // vTaskDelay will cause the task to be delayed for 
    // a specified number of ticks
    vTaskDelay(100);  // Wait 100 ticks or 1 second
  }
}

/**************************************************************************/
/*! 
    Creates a new task for the FreeRTOS Kernel and add it to the
    scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE trackLogTaskStart (void)
{
  return xTaskCreate (
    vTrackLog,
    (const signed portCHAR * const) "log tracker",
    (unsigned portSHORT) 256,//    configMINIMAL_STACK_SIZE,
    NULL,
    (tskIDLE_PRIORITY + 2),
    &taskHandles [TASKHANDLE_TRACKLOG]);
}

/**************************************************************************/
/*! 
    Stops the task and deletes it from the task scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE trackLogTaskStop (void)
{
  if (!taskHandles [TASKHANDLE_TRACKLOG])
    return 0;
  
  vTaskDelete (taskHandles [TASKHANDLE_TRACKLOG]);
  taskHandles [TASKHANDLE_TRACKLOG] = NULL;

  return 1;
}

/**
 Opens the log file (path defined as LOG_FILE_PATH) and
 sets file pointer to the end of file

 @return FR_OK 		.... log file was opened successfully
 @return FR_NO_FILE  .... memory alloctaion went wrong
 @return other RC    .... see return codes of f_open()
 */
FRESULT initLog()
{
#if ENABLE_LOG
	FRESULT rc = FR_NO_FILE;
	log_file = (FIL*) pvPortMalloc(sizeof(FIL));

	vTaskSuspendAll();

	//LUK /*is already enabled */ fs_enable(400000);

	if (log_file != NULL)
	{
#if DEBUG_LOG
		printf("Opening file, memory OK \n");
#endif
		rc = f_open(log_file, LOG_FILE_PATH, FA_WRITE);

		//goto end of file
		if (rc == FR_OK)
		  f_lseek(log_file, log_file->fsize);
	}

	xTaskResumeAll();

	return rc;
#else
	return -1;
#endif
}

/**
 Appends the message to the log file and adds the current time
 (format: $time : $msg

 @param *msg  pointer to log message

 @return FR_OK 		.... message wrote successfully
 @return FR_NO_FILE  .... log_file pointer was not initialized
 @return other RC    .... see return codes of f_open()

 */
FRESULT appendToLog(char *msg)
{
#if ENABLE_LOG
	FRESULT rc = FR_NO_FILE;
	unsigned int i = 0;
        U16 bw;

	buf[0] = 0;
	time_buf[0] = 0;

	//LUKget_dateandtime(time_buf, sizeof(time_buf));
	char time_buf[10] = "2010-12-21";
        i = strlen(time_buf);
	time_buf[i-1] = 0;

	// suspend all other tasks
	vTaskSuspendAll();

	snprintf(buf, 127, "%s : %s\n", time_buf, msg);
	rc = f_write(log_file, buf, strlen(buf), &bw);

	if (rc == FR_OK)
	{
#if DEBUG_LOG
		printf("appendToLog: wrote msg %s", buf);
#endif
		f_sync(log_file);
	}

	// resumes all tasks
	xTaskResumeAll();

	return rc;
#else
	return -1;
#endif
}

//*****************************************************************************
//
// Initialize the file system.
//
//*****************************************************************************
void fs_init(void)
{
	FRESULT fresult;
	DIR g_sDirObject;

	//
	// Initialze the flag to indicate that we are disabled.
	//
	//LUKg_bFatFsEnabled = false;
        printf ("RRC=%d\n", diskInitialize (0));


	//
	// Initialize and mount the Fat File System.
	//
	fresult = f_mount(0, &g_sFatFs);
	if (fresult != FR_OK)
	{
		return;
	}

	//
	// Open the root directory for access.
	//
	fresult = f_opendir(&g_sDirObject, "/");

	//
	// Flag and display which file system we are using.
	//

	if (fresult == FR_OK)
	{
		//
		// Indicate and display that we are using the SD file system.
		//
	//LUK	g_bFatFsEnabled = true;
	}
	else
	{
		//
		// Indicate and display that we are using the internal file system.
		//
	//LUK	g_bFatFsEnabled = false;
	}
}

void getDateTime(char *datetime) {
  mktime(ts);
  if(ts->tm_year < 1000) ts->tm_year += 1900; // 2011-111=
  strftime(datetime, sizeof("YYYY-MM-DD;HH-mm-ss"), "%Y-%m-%d;%T", ts); 
}

#ifdef logCDaySummary
void updateCDayLogEntryItem(void) {
    //strcpy((char *)cdaylog_entry_item.last_update, (char *)slog_entry_item.datetime);
    cdaylog_entry_item.last_update = slog_entry_item.datetime;
    if (get_FlowCount() != 0) {
      /* cdaylog_entry_item.sum_flowvolume is directly incremented when a flowrate sensor impuls kicks */
      cdaylog_entry_item.sum_flowtime     += (unsigned short)getMeasure_timestamp_diff(); /* pumptime[s] */
      //cdaylog_entry_item.sum_energy       += (unsigned short) get_FlowCount() * (slog_entry_item.val_adc2 - slog_entry_item.val_adc4) * thermalCapacityFluid;         /* Value in Ws */
      cdaylog_entry_item.sum_profit       += cdaylog_entry_item.sum_energy / 3600 * getWhPriceRappen();           /* Value in Rappen */
    }
}
#endif

#ifdef logAllTimeSummary
void updateCLogEntryItem(void) {
  unsigned short tmpDeltaEnergy = 0;
  clog_entry_item.last_update;        /* YYYY-MM-DD;HH(24h)-mm-ss+'\0' */
  clog_entry_item.sum_flowtime            += (unsigned short)getMeasure_timestamp_diff();           /* pumptime[s] */
  //clog_entry_item.sum_flowvolume;       /* already done by incr_SumFlowvolume() by each flowmeter-kick */
  tmpDeltaEnergy                             = (unsigned short) get_FlowCount() * (slog_entry_item.val_adc2 - slog_entry_item.val_adc4) * thermalCapacityFluid;         /* Value in Ws */
  clog_entry_item.sum_energy              += tmpDeltaEnergy;
  clog_entry_item.sum_profit              += tmpDeltaEnergy / 3600 * getWhPriceRappen();           /* Value in Rappen */
  
  /* if t==23.55h calculate arithmetic medians */
  //if ((ts->tm_hour == 23) && (ts->tm_min == 55)) {
  if(1) {
    clog_entry_item.arithm_day_flowtime      = (clog_entry_item.arithm_day_flowtime   * (daysLogging-1) + cdaylog_entry_item.sum_flowtime) / daysLogging;     /* pumptime[s]/day */
    clog_entry_item.arithm_day_flowvolume    = (clog_entry_item.arithm_day_flowvolume * (daysLogging-1) + cdaylog_entry_item.sum_flowvolume) / daysLogging;   /* Value 0-int l */
    clog_entry_item.arithm_day_energy        = (clog_entry_item.arithm_day_energy     * (daysLogging-1) + cdaylog_entry_item.sum_energy) / daysLogging;       /* Value in Ws */
    clog_entry_item.arithm_day_profit        = (clog_entry_item.arithm_day_profit     * (daysLogging-1) + cdaylog_entry_item.sum_profit) / daysLogging;       /* Value in Rappen */
  }
  /* if t==23.55h */
}
#endif

//void incr_SumFlowvolume(void) { 
//  slog_entry_item.flowvolume += flowrateMeterImpulsVolume;
//
//  #ifdef logCDaySummary
//  cdaylog_entry_item.sum_flowvolume += flowrateMeterImpulsVolume;
//  #endif
//
//  #ifdef logAllTimeSummary
//  clog_entry_item.sum_flowvolume    += flowrateMeterImpulsVolume; 
//  #endif
//}


void init_daysLogging(void) { daysLogging = 1; }
unsigned short incr_daysLogging(void) { daysLogging++; return daysLogging; };

#if CFG_LCD == 1
void feedLCD(void)
{
  //GPIO1_FIOSET2 |= (1<<0); // CS
  //LUK 2011-05-11 put into loop where feedLCD is called: LCD_RS_SET();

  //LUK 2011-05-11 delay(255);
  //vTaskDelay( 900 / portTICK_RATE_MS);  // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11
  //vTaskDelay( 900 / portTICK_RATE_MS);  // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11
  //vTaskDelay( 900 / portTICK_RATE_MS);  // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11
  
  // send command
  //GPIO1_FIOCLR2 |= (1<<0);
//  printf_lcd(0,0,"HOI Lukas",1);
//  printf_lcd(0,0,"Gib dr Nadine �",1); // Einschaltmeldung  
//  printf_lcd(0,1,"dick� Schmutz",1);  
//  printf_lcd(0,2,"!!!",1);  
//  printf_lcd(0,3,"!!!",1);  
//  //LUK 2011-05-11 delay(200);  // Pause ca. 2s
//  vTaskDelay(2000 / portTICK_RATE_MS);
//  printf_lcd(0,3,"(SPI/Seriell-Mode)",1);
  //blink_lcd(19,3,1); 

  /* show each screen for 2s and loop forever */
  //char txtline[20]; ersetzt durch meas_sm.h/buf[21]
  //while(actReportScreen < 12) {
  while(actReportScreen < 2) {
    char buf[21], numberAsChar[5]="     ", count=0;
    switch(actReportScreen) {
    case  0: { /* "aktuelle Werte  1/2 "
                  "aktiv seit     :   h"
                  "Panel        %3d   C"
                  "R�cklauf     %3d   C" */                    
                        printf_lcd(0,0, reportScreen[0][0],1);
                            
                        /* stringvorgabe mit wert f�llen, anschliessend an lcd schicken */
                        //sprintf(buf, reportScreen[0][1]); // Laufdauer
                        luk_strcpy(buf, reportScreen[0][1], 20); // Laufdauer
                        printf_lcd(0,1, (char *)buf,1);
                        
                        //sprintf(buf, reportScreen[0][2], slog_entry_item.val_adc1);
                        luk_strcpy(buf, reportScreen[0][2], 20);
                        buf[18]=(char)charDEGREES; // wasn't possible to include character '�' via sprintf, the 'C' afterwards has always disappeared
                        //FILL_BUF_WITH_VALUES(slog_entry_item.val_adc1, (reportScreenConfig[0][2][0]));
                        FILL_BUF_WITH_VALUES(slog_entry_item.val_adc1, reportScreenConfig[0][2][0]);  
                        //{ if(slog_entry_item.val_adc1 != 0) { b_itoab(*numberAsChar, slog_entry_item.val_adc1); for(count=0; count < nrOfDigits(slog_entry_item.val_adc1, 10); count++) { buf[(int)(reportScreenConfig[0][2][0] - count)] = numberAsChar[count]; } } luk_strcpy(numberAsChar, "     "); }
                        printf_lcd(0,2, (char *)buf,1);
                        
                        //sprintf(buf, reportScreen[0][3], slog_entry_item.val_adc4);
                        luk_strcpy(buf, reportScreen[0][3], 20);
                        buf[18]=(char)charDEGREES; // wasn't possible to include character '�' via sprintf, the 'C' afterwards has always disappeared
                        FILL_BUF_WITH_VALUES(slog_entry_item.val_adc4, reportScreenConfig[0][3][0]);
                        printf_lcd(0,3, (char *)buf,1);  
                        break;
             }
    case  1: { /* "aktuelle Werte 2/2  "
                  "Boiler oben   %3d  C"
                  "Boiler unten  %3d  C"
                  "Durchfluss    %2ds/l"*/
                        //sprintf(buf, reportScreen[1][0]);
                        luk_strcpy(buf, reportScreen[1][0], 20);
                        buf[19]=(char)charANTENNA;
                        printf_lcd(0,0, (char *)buf,1); 

                        //sprintf(buf, reportScreen[1][1], slog_entry_item.val_adc2);
                        luk_strcpy(buf, reportScreen[1][1], 20);
                        buf[18]=(char)charDEGREES;
                        FILL_BUF_WITH_VALUES(slog_entry_item.val_adc2, reportScreenConfig[1][1][0]);
                        printf_lcd(0,1, (char *)buf,1);
                        
                        //sprintf(buf, reportScreen[1][2], slog_entry_item.val_adc3);
                        luk_strcpy(buf, reportScreen[1][2], 20);
                        buf[18]=(char)charDEGREES;
                        FILL_BUF_WITH_VALUES(slog_entry_item.val_adc3, reportScreenConfig[1][2][0]);
                        printf_lcd(0,2, (char *)buf,1);  

                        //sprintf(buf, reportScreen[1][3], slog_entry_item.val_adc2);
                        luk_strcpy(buf, reportScreen[1][3], 20);
                        float fTMP = get_FlowCount()/getMeasure_timestamp_diff();
                        if(fTMP!=0) { int iTMP = (int)fTMP; // iTMP == value of fTMP without fractional portions
                                      int iFRACPORTION = 10*(fTMP - iTMP); // iFRACPORTION == the first digit after the decimal point (fractional portion)
                                      buf[(int)(reportScreenConfig[1][2][0])]   = iFRACPORTION; // fractional portion
                                      buf[(int)reportScreenConfig[1][2][0]-1] = '.'; // point
                                      FILL_BUF_WITH_VALUES(iTMP, (reportScreenConfig[1][2][0]-2));
                                      printf_lcd(0,3, (char *)buf,1);  
                        }
                        //vTaskDelay(900 / portTICK_RATE_MS);
                        break;
             }
    case  2: { /* Tageswerte 1/2 */
  
             }
    case  3: { /* Tageswerte 2/2 */
  
             }
    case  4: { /* Monatswerte 1/3 */
  
             }
    case  5: { /* Monatswerte 2/3 */
  
             }
    case  6: { /* Monatswerte 3/3 */
  
             }
    case  7: { /* kont. Log 1/3 */
  
             }
    case  8: { /* kont. Log 2/3 */
  
             }
    case  9: { /* kont. Log 3/3 */
  
             }
    case 10: { /* Opening 1/2 */
  
             }
    case 11: { /* Opening 2/2 */
  
             }
    }

    
    actReportScreen += 1;
    vTaskDelay(450);
  }
  actReportScreen = 0;
}
#endif

/** int to string
    to bypass the sprintf-function because of too much stack usage we have this function which uses less stack.
    Source: http://documentation.renesas.com/eng/products/region/rtas/mpumcu/apn/bprintf.pdf
 */

//void b_itoab(char **buf, DWORD i, unsigned int base)
void b_itoab(char **buf, DWORD i)
{
  //#define LEN 9
  #define LEN 5
  unsigned int base = 10;
  BYTE index=0;
  DWORD rem;
  char conv[LEN];
  if (i == 0)
  {
    (*buf)[0] = '0';
    ++(*buf);
    return;
  }
  conv[index++] = 0;
  while (i)
  {
    rem = i % base;
    //if (base == 10)
      conv[index++] = rem + '0';
//    else if (base == 16)
//    {
//      if (rem < 10)
//        conv[index++] = rem + '0';
//      else
//        conv[index++] = rem + 'A'- 0xA;
//    }
    i /= base;
  }
  while (conv[--index])
  {
    (*buf)[0] = conv[index];
    ++(*buf);
  }
}

/** number of digits */
char nrOfDigits(int i, int base) {
  return (char)(log(i)/log(base) + 1); //LUK to be verified
}

void luk_strcpy(char *to, char *from, char howMany) {
  while(howMany) {
    to[howMany-1] = from[howMany-1];
    howMany--;
  }
}


void setWindFrequency(short value)
{
  __windFrequency = value;
}

int getWindSpeed(void)
{
  /* each count of __windPeriod is based on a 4kHz sampling rate and takes effective time of 250us.
  __windPeriod*250us=periodtime[us]
  periodtime[us]/10^6=periodtime[s]
  1/periodtime=frequency
  ->summarized: frequency=4000/__windPeriod

  */
  float windFrequency;
  if(getWindPeriod()==0)
  {
    windFrequency = 0;
  }
  else
  {
    windFrequency = (4000.0/getWindPeriod());
    //v(f) = 1/1.8112*f+0.7572 [m/s]
    windFrequency = 1/1.8112*windFrequency+0.7572;
  }
  return (short)windFrequency;
}

int getWindFrequency(void)
{
  float tmpa=-1;
  if(meas_op_item[1].value > 0)
  {
    /*
    c:  Countervalue (T1_CR3)
    dT: timebase for one increment of T1_CR3 [100us]=48'000'000Hz/480=100'000
    f:  Frequency
    T:  Periodtime of the measured frequency
    T[us] = c * 100us             T=500*100us=50000us    \
                                                           => Factor=100us/1'000'000us=0.1
    T[s]  = T / 1000000           T=50000/1000000=0.05s  /
    f     = 1 / T[s]              f=1/0.05s=20Hz

    */
    tmpa= meas_op_item[1].value / 4000.0; // Basiswechsel [1ms]=>[1s] 1000.0-1kHz; 40000-4kHz; 
    meas_op_item[1].value = 1.0 / tmpa; // f=1/T
  }
  return meas_op_item[1].value;
}

void clrWindFrequency(void)
{
  __windFrequency = 0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
