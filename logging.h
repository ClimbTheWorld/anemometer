/**
 * \addtogroup logging
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

#ifndef LOGGING_H_
#define LOGGING_H_

#include <string.h>
#include <time.h>
#include "sysdefs.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "fatfs/ff.h"

//*****************************************************************************
//
/// Defines path to the log file
//
//*****************************************************************************
#define LOG_FILE_PATH "log/sys.log"

/* for getLogfilename(x,y) */
#define contLog  0
#define dayLog   1
#define monthLog 2
#define allTimeSummary  3

#if CFG_LCD == 1
/* special characters for LCD */
#define charANTENNA     0x95
#define charDEGREES     0x80
    
#define numberOfReportScreens 12
#endif
//*****************************************************************************
//
/// global pointer to the log file
//
//*****************************************************************************
FIL* log_file;

/** Opens the log file (path defined as LOG_FILE_PATH) and
 *  sets file pointer to the end of file
 */
FRESULT initLog();

/**
 * Appends the message to the log file and adds the current time
 *
 */
FRESULT appendToLog(char *msg);

/** Task functions */
void loggingDoSomething(void);
signed portBASE_TYPE loggingStart (void);
signed portBASE_TYPE loggingStop (void);

/**
 * single Log entry item structure
 *
 * { Date/Time; Wind Direction [0-359�N]; Wind velocity [m/s]; }
 *
 */
volatile typedef struct 
{
    /* sizeof (_SLOG_ENTRY_ITEM = (19+1)+2+2+2+2+2+2 = 32 */
    //char  datetime[20];     /* YYYY-MM-DD_HH-mm(24h)-ss'\0' */
    time_t datetime;
    unsigned short winddirection;         /* Value 0-Aref(3300) [0-359�N] */
    unsigned short windspeed;    /* summed-up over a whole day */
} /* __attribute__ ((packed)) */ _SLOG_ENTRY_ITEM;
_SLOG_ENTRY_ITEM slog_entry_item;
#define _SLOG_ENTRY_ITEM_SIZE 32

/**
 * continuous(24h-DayLong) Log entry item structure
 *
 * { Date/Time; ADC1 [�C]; ADC2 [�C]; ADC3 [�C]; ADC4 [�C]; Volumenstrom [l/s]; }
 *
 */
 #ifdef logCDaySummary
volatile typedef struct 
{
    time_t last_update;     /* YYYY-MM-DD_HH(24h)-mm-ss+'\0' */
    unsigned short sum_flowtime;        /* pumptime[s] */
    float sum_flowvolume;       /* Value 0-int l */
    unsigned short sum_energy;         /* Value in Ws */
    unsigned short sum_profit;           /* Value in Rappen */

} /* __attribute__ ((packed)) */ _CDAYLOG_ENTRY_ITEM;
_CDAYLOG_ENTRY_ITEM cdaylog_entry_item;
#define _CDAYLOG_ENTRY_ITEM_SIZE 29
#endif

/**
 * continuous Log entry item structure
 *
 * { Date/Time; ADC1 [�C]; ADC2 [�C]; ADC3 [�C]; ADC4 [�C]; Volumenstrom [l/s]; }
 *
 */
#ifdef logAllTimeSummary
volatile typedef struct 
{
    char  last_update[20];        /* YYYY-MM-DD;HH(24h)-mm-ss+'\0' */
    //unsigned short sum_count_days;          /* how long the structure is logging */
    unsigned long sum_flowtime;           /* pumptime[s] */
    unsigned long sum_flowvolume;         /* Value 0-int l */
    unsigned long sum_energy;             /* Value in Ws */
    unsigned long sum_profit;                /* Value in Rappen */
    unsigned short arithm_day_flowtime;     /* pumptime[s]/day */
    unsigned short arithm_day_flowvolume;  /* Value 0-int l */
    unsigned short arithm_day_energy;      /* Value in Ws */
    unsigned short arithm_day_profit;        /* Value in Rappen */
} /* __attribute__ ((packed)) */ _CLOG_ENTRY_ITEM;
//_CLOG_ENTRY_ITEM cmonthlog_entry_item, cyearlog_entry_item, ctotallog_entry_item;
_CLOG_ENTRY_ITEM clog_entry_item;
#define _CLOG_ENTRY_ITEM_SIZE 52
#endif 

//void fillSlogEntryItem(char *datetime, unsigned short adc1, unsigned short adc2, unsigned short adc3, unsigned short adc4/*, unsigned short flowrate*/);
//void fillSlogEntryItem(time_t datetime, unsigned short adc1, unsigned short adc2, unsigned short adc3, unsigned short adc4/*, unsigned short flowrate*/); --> the struct tm ts is already global, no need to give it as a parameter
//void fillSlogEntryItem(unsigned short winddirection, unsigned short windvelocity);
void fillSlogEntryItem(unsigned short winddirection, unsigned short winddirection_max, unsigned short windspeed);
void getLogFilename(char log, char *filename);

static float WhPriceRappen; // price of a Wh in CHRp.
void setWhPrice(float WsRappen);
static float getWhPriceRappen(void);

void getDateTime(char *datetime);

void trackLog(void);
signed portBASE_TYPE trackLogTaskStart (void);
signed portBASE_TYPE trackLogTaskStop (void);

/* SD Card Variables */
FATFS Fatfs[_DRIVES]; /* File system object for each logical drive */
FIL FileContLog, FileDayLog, /*FileMonthLog,*/ FileAllTimeLog; /* File objects */

/** Filenames of the Log files:
 * [0] : FileContLog:    "YYYY-contLog.txt" (16+1 chars)  ->> "YYYY" (to save space -> just the year will be saved)
 * [1] : FileDayLog:     "YYYY-dayLog.txt" (15+1 chars)   ->> "YYYY" (to save space -> just the year will be saved)
 * [2] : FileMonthLog:   "YYYY-monthLog.txt" (17+1 chars) ->> "YYYY-MM" (to save space -> just the year and month will be saved) ->> (8)
 * [3] : FileAllTimeLog: "alltime.txt" (11+1 chars)
 */
static char logFilename[18];

static volatile float __windFrequency=0;
void setWindFrequency(short value);
int getWindSpeed(void);
int getWindFrequency(void);
void clrWindFrequency(void);

void incr_SumFlowvolume(void);

static volatile unsigned short daysLogging; /** counts the days the system is logging. Is going to be increment for the following day at 23.55h */
unsigned short incr_daysLogging(void);
void init_daysLogging(void);

void updateCDayLogEntryItem(void);
void updateCLogEntryItem(void);


#if CFG_LCD == 1
/**********************************************************************************************************************
 ******************* LCD Routines *************************************************************************************
**********************************************************************************************************************/
//void b_itoab(char **buf, DWORD i, unsigned int base);
void b_itoab(char **buf, DWORD i);

char nrOfDigits(int i, int base);

void feedLCD(void);

static unsigned char actReportScreen = 0;
/** [12]: number of screens
   *  [4]:  number of rows
   *  [20]: Text-Template without variable values to be written on screen
   */
static const char reportScreen[12][4][20] = {
//   {"aktuelle Werte 1/2  ", // screen 0
//    "aktiv seit     :   h",
//    "Panel        %3d   C",
//    "R�cklauf     %3d   C"},
//  
//   {"aktuelle Werte 2/2  ", // 1
//    "Boiler oben   %3d  C",
//    "Boiler unten  %3d  C",
//    "Durchfluss    %2dl/s"},
   {"aktuelle Werte 1/2  ", // screen 0
    "aktiv seit     :   h",
    "Panel           0  C",
    "R�cklauf        0  C"},
  
   {"aktuelle Werte 2/2  ", // 1
    "Boiler oben     0  C",
    "Boiler unten    0  C",
    "Durchfluss      0l/s"},

   {"Tageswerte     1/2  ", // 2
    "Laufzeit      %3d ' ",
    "umges. Vol.   %3d l ",
    "Energie       %3d Wh"},
  
   {"Tageswerte     2/2  ", // 3
    "Leistung      %3d W ",
    "Profit        %3d Fr",
    "                    "},
  
   {"Monatswerte    1/3  ", // 4
    "Messtage          d ",
    "Laufzeit       h  m ",
    "Energie           Wh"},
  
   {"Monatswerte    2/3  ", // 5
    "Volumen           l ",
    "Profit            Fr",
    "Mw tPumpe/T       m "},
  
   {"Monatswerte    3/3  ", // 6
    "Mw Volumen/T      l ",
    "Mw Energie/T      Wh",
    "Mw Profit/T       Fr"},
  
   {"kont. Log      1/3  ", // 7
    "Messtage          d ",
    "Laufzeit       h  m ",
    "Energie           Wh"},
  
   {"kont. Log      2/3  ", // 8
    "Volumen           l ",
    "Profit            Fr",
    "Mw tPumpe/T       m "},
  
   {"kont. Log      3/3  ", // 9
    "Mw Volumen/T      l ",
    "Mw Energie/T      Wh",
    "Mw Profit/T       Fr"},

   {"if no one else can  ", // Werbung / Startup 1/2 (knacksen aus Lautsprecher)
    "help, and if you can",
    "find them, may be   ",
    "you can hire...     "},

   {"        the         ", // Werbung / Startup 2/2 (opening title)
    "                    ",
    "       A-TEAM       ",
    "                    "}



    /*(Ten years ago / In 1972), a crack commando unit was sent to prison by a military court 
    for a crime they didn't commit. These men promptly escaped from a maximum security stockade 
    to the Los Angeles underground. Today, still wanted by the government, they survive as soldiers
    of fortune. If you have a problem, if no one else can help, and if you can find them, maybe you can hire... 
    The A-Team.*/
  };

//static const char AUSWERTUNGSBILDSCHIRME[40][20];


/** [12]: number of screens
   *  [4]:  number of rows
   *  [2]:  [0]: at which column the first/least valuable letter of the number is located
   *        [1]: number format of float
   */
static const float reportScreenConfig[12][4][2] = {
  { 0 ,0,    // screen 0
   14, 5.2,
   16, 3,
   16, 3},
  
  { 0, 0,    // 1
   16, 3,
   16, 3,
   16, 3,},

  { 0, 0,    // 2
   16, 3,
   16, 3,
   14, 5.1},

  { 0, 0,    // 3
   14, 5.1,
   16, 3,
    0, 0},

  { 0, 0,    // 4
   16, 3,
   15, 4,
   14, 5.1},

  { 0, 0,    // 5
   15, 4,
   16, 3,
   16, 3},

  { 0, 0,    // 6
   16, 3,
   16, 3,
   16, 3,},

  { 0, 0,    // 7
   16, 3,
   16, 3,
   14, 5.1,},

  { 0, 0,    // 8
   15, 4,
   16, 3,
   16, 3},

  { 0, 0,    // 9
   16, 3,
   16, 3,
   16, 3,},

  { 0, 0,    // Werbung / Startup 1/2 (knacksen aus Lautsprecher)
    0, 0,
    0, 0,
    0, 0,},
  
  { 0, 0,    // Werbung / Startup 2/2 (opening title)
    0, 0,
    0, 0,
    0, 0,},
};

//if(slog_entry_item.val_adc1 == 0)
//  buf[(int)(reportScreenConfig[0][2][0])] = '0';
//else {
//  b_itoab(*numberAsChar, slog_entry_item.val_adc1);
//  for(count=0; count < nrOfDigits(slog_entry_item.val_adc1, 10); count++) {
//    buf[(int)(reportScreenConfig[0][2][0] - count)] = numberAsChar[count];
//  }
//}
#define FILL_BUF_WITH_VALUES(value, position)          { if(value != 0) { b_itoab(*numberAsChar, value); for(count=0; count < nrOfDigits(value, 10); count++) { buf[(int)(position - count)] = numberAsChar[count]; } } strcpy(numberAsChar, "     "); }

void luk_strcpy(char *to, char *from, char howMany);
#endif // #if CFG_LCD == 1
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************