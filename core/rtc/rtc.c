/**************************************************************************/
/*! 
    \file     rtc.c
    \author   Original Code: J.C. Wren
              Modified By: K. Townsend (microBuilder.eu)
    \date     9 November 2009
    \version  1.00
*/
/**************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rtcISR.h"
#include "rtc.h"

/**************************************************************************/
/*! 
    Place RTC on 32kHz xtal and disconnect power.
*/
/**************************************************************************/
static inline void rtcSleep (void)
{
  RTC_CCR = (RTC_CCR_CLKEN | RTC_CCR_CLKSRC);
  SCB_PCONP &= ~SCB_PCONP_PCRTC;
}

/**************************************************************************/
/*! 
    Prepare clock for interactive use.
*/
/**************************************************************************/
static inline void rtcWake (void)
{
  RTC_CCR = (RTC_CCR_CLKEN | RTC_CCR_CLKSRC);
  SCB_PCONP |= SCB_PCONP_PCRTC;
}

/**************************************************************************/
/*! Version: original
    Read clock registers and return tm structure.
*/
/**************************************************************************/
static void rtcRead (struct tm *theTime, unsigned int *milliseconds)
{
  unsigned int ticks32Khz;
  rtcCTIME0_t ctime0;
  rtcCTIME1_t ctime1;
  rtcCTIME2_t ctime2;

  rtcWake ();
  portENTER_CRITICAL ();

  do
  {
    ctime0.i = RTC_CTIME0;
    ctime1.i = RTC_CTIME1;
    ctime2.i = RTC_CTIME2;

    do
      ticks32Khz = (RTC_CTC & 0xfffe);
    while (ticks32Khz != (RTC_CTC & 0xfffe));
  }
  while (ctime0.i != RTC_CTIME0);

  portEXIT_CRITICAL ();
  rtcSleep ();

  if (milliseconds)
    *milliseconds = (((ticks32Khz / 2) * 1000u) / 32768u);

  theTime->tm_sec   = ctime0.seconds;
  theTime->tm_min   = ctime0.minutes;
  theTime->tm_hour  = ctime0.hours;
  theTime->tm_mday  = ctime1.dom;
  theTime->tm_mon   = ctime1.month - 1;
  //theTime->tm_mon   = ctime1.month;
  theTime->tm_year  = ctime1.year - 1900;
  //theTime->tm_year  = ctime1.year;
  theTime->tm_wday  = ctime0.dow;
  theTime->tm_yday  = ctime2.doy - 1;
  theTime->tm_isdst = 0;
}

/**************************************************************************/
/*! Version: f�r Lukas
    Read clock registers and return tm structure.
*/
/**************************************************************************/
static void rtcReadLuk (struct tm *theTime, unsigned int *milliseconds)
{
  unsigned int ticks32Khz;
  rtcCTIME0_t ctime0;
  rtcCTIME1_t ctime1;
  rtcCTIME2_t ctime2;

  rtcWake ();
  portENTER_CRITICAL ();

  do
  {
    ctime0.i = RTC_CTIME0;
    ctime1.i = RTC_CTIME1;
    ctime2.i = RTC_CTIME2;

    do
      ticks32Khz = (RTC_CTC & 0xfffe);
    while (ticks32Khz != (RTC_CTC & 0xfffe));
  }
  while (ctime0.i != RTC_CTIME0);

  portEXIT_CRITICAL ();
  rtcSleep ();

  if (milliseconds)
    *milliseconds = (((ticks32Khz / 2) * 1000u) / 32768u);

  theTime->tm_sec   = ctime0.seconds;
  theTime->tm_min   = ctime0.minutes;
  theTime->tm_hour  = ctime0.hours;
  theTime->tm_mday  = ctime1.dom;
  theTime->tm_mon   = ctime1.month - 1;
  theTime->tm_year  = ctime1.year - 1900;
  theTime->tm_wday  = ctime0.dow;
  theTime->tm_yday  = ctime2.doy;
  theTime->tm_isdst = 0;
}


/**************************************************************************/
/*! 
    Set clock to new values.
*/
/**************************************************************************/
static void rtcWrite (struct tm *newTime)
{
  rtcWake ();
  portENTER_CRITICAL ();

  RTC_CCR &= ~RTC_CCR_CLKEN;
  RTC_CCR |=  RTC_CCR_CTCRST;

  RTC_SEC   = newTime->tm_sec;
  RTC_MIN   = newTime->tm_min;
  RTC_HOUR  = newTime->tm_hour;
  RTC_DOM   = newTime->tm_mday;
  RTC_MONTH = newTime->tm_mon + 1;
  RTC_YEAR  = newTime->tm_year + 1900;
  RTC_DOW   = newTime->tm_wday;
  RTC_DOY   = newTime->tm_yday + 1;

  RTC_CCR &= ~RTC_CCR_CTCRST;
  RTC_CCR |=  RTC_CCR_CLKEN;

  portEXIT_CRITICAL ();
  rtcSleep ();
}

/**************************************************************************/
/*! Version: original

*/
/**************************************************************************/
time_t rtcGetEpochSeconds (unsigned int *milliseconds)
{
  struct tm tm;

  rtcRead (&tm, milliseconds);
  return mktime (&tm);
}

/**************************************************************************/
/*! Version: f�r Lukas

*/
/**************************************************************************/
time_t rtcGetEpochSecondsLuk (unsigned int *milliseconds)
{
  struct tm tm;

  rtcReadLuk (&tm, milliseconds);
  return mktime (&tm);
}

/**************************************************************************/
/*! 

*/
/**************************************************************************/
void rtcSetEpochSeconds (time_t now)
{
  struct tm tm;

  localtime_r (&now, &tm);
  rtcWrite (&tm);
}

/**************************************************************************/
/*! 
    Start clock so that the system may use it.
*/
/**************************************************************************/
static void rtcInitClockCalendar (void)
{
  int nonsense = 0;
  rtcCTIME0_t ctime0;
  rtcCTIME1_t ctime1;
  rtcCTIME2_t ctime2;

  rtcWake ();
  
  ctime0.i = RTC_CTIME0; 
  ctime1.i = RTC_CTIME1; 
  ctime2.i = RTC_CTIME2;

  //  Leisurely tear the packed time apart into individual time.
  if ((ctime0.seconds < 0) || (ctime0.seconds > 59))  nonsense = 1;
  if ((ctime0.minutes < 0) || (ctime0.minutes > 59))  nonsense = 1;
  if ((ctime0.hours < 0)   || (ctime0.hours > 23))    nonsense = 1;
  if ((ctime1.dom < 1)     || (ctime1.dom > 31))      nonsense = 1;
  if ((ctime1.month < 1)   || (ctime1.month > 12))    nonsense = 1;
  if ((ctime1.year < 1980) || (ctime1.year > 2050))   nonsense = 1;
  if ((ctime0.dow < 0)     || (ctime0.dow > 6))       nonsense = 1;
  if ((ctime2.doy < 0)     || (ctime2.doy > 366))     nonsense = 1;

  rtcSleep ();

  //  Set the clock to Jan 1, 2006 00:00:00
  if (nonsense) 
    rtcSetEpochSeconds ((time_t) 1136073600);
}

/**************************************************************************/
/*! 

*/
/**************************************************************************/
void rtcInit (void)
{
  rtcISRInit ();

  // Power up RTC
  SCB_PCONP |= SCB_PCONP_PCRTC;

  RTC_CCR = 0;

  RTC_CCR |= RTC_CCR_CLKSRC;

  RTC_AMR = RTC_AMR_AMRMASK;
  RTC_CIIR = 0;

  RTC_ILR = RTC_ILR_MASK;

  RTC_CCR |= RTC_CCR_CLKEN;

  VIC_IntSelect &= ~VIC_IntSelect_RTC;
#ifdef RTC_NONVECTOREDIRQ
  VIC_DefVectAddr = (portLONG) rtcISR;
#else
  VIC_VectAddr6 = (portLONG) rtcISR;
  VIC_VectCntl6 = VIC_VectCntl_ENABLE | VIC_Channel_RTC;
#endif
  VIC_IntEnable = VIC_IntEnable_RTC;

  rtcInitClockCalendar ();
}

/**************************************************************************/
/*! 

*/
/**************************************************************************/
int rtcSetAlarm (struct tm *tm)
{
  // ToDo: Check if alarm time is less than current time!
  // if (tm && (mktime (tm) < time (NULL)))
  //   return -1;

  rtcWake ();

  RTC_AMR = RTC_AMR_AMRMASK;

  if (tm)
  {
    RTC_ALYEAR = tm->tm_year /*+ 1900*/; // LUK: + 1900 vermutlich ein Fehler; keine Ahnung wof�r, da Datumsjahr sowieso 4-stellig
    RTC_ALMON = tm->tm_mon /*+ 1*/;
    RTC_ALDOM = tm->tm_mday;
    RTC_ALHOUR = tm->tm_hour;
    RTC_ALMIN = tm->tm_min;
    RTC_ALSEC = tm->tm_sec;
    RTC_ALDOW = 0;
    RTC_ALDOY = 0;

    RTC_AMR = RTC_AMR_AMRDOW | RTC_AMR_AMRDOY;
  }

  rtcSleep ();

  return 0;
}

/**************************************************************************/
/*! Set increment interrupts
 * @param  which incremental alarms should be turned on
 * @return 0
*/
/**************************************************************************/
int rtcSetAlarmCIIR (unsigned char pCIIR)
{
  // ToDo: Check if alarm time is less than current time!
  // if (tm && (mktime (tm) < time (NULL)))
  //   return -1;

  rtcWake ();

  RTC_CIIR |= pCIIR;

  RTC_ILR |= 1; // clear increment interrupt flag

  rtcSleep ();

  return 0;
}

/**************************************************************************/
/*! 

*/
/**************************************************************************/
struct tm *rtcGetAlarmTm (struct tm *tm)
{
  if (tm)
  {
    memset (tm, 0, sizeof (* tm));

    rtcWake ();

    if (RTC_AMR != RTC_AMR_AMRMASK)
    {
      tm->tm_year = RTC_ALYEAR - 1900;
      tm->tm_mon = RTC_ALMON - 1;
      tm->tm_mday = RTC_ALDOM;
      tm->tm_hour = RTC_ALHOUR;
      tm->tm_min = RTC_ALMIN;
      tm->tm_sec = RTC_ALSEC;
    }
    else
    {
      time_t now = 0;
      memcpy (tm, localtime (&now), sizeof (* tm));
    }

    rtcSleep ();
  }

  return tm;
}

/**************************************************************************/
/*! 

*/
/**************************************************************************/
time_t rtcGetAlarmEpochSeconds (void)
{
  struct tm tm;

  return mktime (rtcGetAlarmTm (&tm));
}

/**************************************************************************/
/*! 

*/
/**************************************************************************/
int rtcPeriodicAlarm (int mode)
{
  int state;
    
  rtcWake ();

  state = RTC_CIIR & RTC_CIIR_IMMIN;

  if (!mode)
    RTC_CIIR &= ~RTC_CIIR_IMMIN;
  else if (mode > 0)
    RTC_CIIR |= RTC_CIIR_IMMIN;

  rtcSleep ();

  return state ? 1 : 0;
}

/**************************************************************************/
/*! 
    Yuck!  Redirect time from time.h to rtcGetEpochSeconds, otherwise
    Crossworks barfs at "now = time (NULL);"
*/
/**************************************************************************/
time_t time(time_t *tp)
{
  return rtcGetEpochSeconds (NULL);
}

/**************************************************************************/
/*! Returns true if increment interrupt is 5min interrupt ^= time2measure
    
*/
/**************************************************************************/
int rtcIs5minInt(void) {
  //return (int) (( RTC_MIN % 5) ? FALSE: TRUE);
  return (int) (( RTC_MIN % 1) ? FALSE: TRUE);
}

/**************************************************************************/
/*! Fills datetime with actual time and date
    
*/
/**************************************************************************/
//char* getDateTime(void)
//{
//  char datetime[19];
//  rtcCTIME0_t ctime0;
//  rtcCTIME1_t ctime1;
//  rtcCTIME2_t ctime2; 
//  ctime0.i = RTC_CTIME0;
//  ctime1.i = RTC_CTIME1;
//  ctime2.i = RTC_CTIME2;
  
/* YYYY-MM-DD;HH(24h)-mm-ss */
// 
//
//    time_t     now;
//    struct tm  *ts;
//    char       buf[19];
// 
//    /* Get the current time */
//    now = time(NULL);
// 
//    /* Format and print the time, "yyyy-mm-dd;hh:mm:ss" */
//    ts = localtime(&now);
//    strftime(buf, sizeof(buf), "%Y-%m-%d;%H:%M:%S", ts);
//    
//
//
//  theTime->tm_sec   = ctime0.seconds;
//  theTime->tm_min   = ctime0.minutes;
//  theTime->tm_hour  = ctime0.hours;
//  theTime->tm_mday  = ctime1.dom;
//  theTime->tm_mon   = ctime1.month - 1;
//  theTime->tm_year  = ctime1.year - 1900;
//  theTime->tm_wday  = ctime0.dow;
//  theTime->tm_yday  = ctime2.doy - 1;
//  theTime->tm_isdst = 0;
//  return buf;
//}

void getRtcRead (struct tm *theTime)
{
  //struct tm ts;
  rtcReadLuk (theTime, NULL);
}

char getMonthLength(char month, char year)
{
  char month_length = 0;
  switch(month) {
    case 1: month_length = 31; break;
    case 2: month_length = 28; break; /* leap year ber�cksichtigen mit +1 ber�cksichtigen */
    case 3: month_length = 31; break;
    case 4: month_length = 30; break;
    case 5: month_length = 31; break;
    case 6: month_length = 30; break;
    case 7: month_length = 31; break;
    case 8: month_length = 31; break;
    case 9: month_length = 30; break;
    case 10: month_length = 31; break;
    case 11: month_length = 30; break;
    case 12: month_length = 31; break;
  }
  /* Leap year calculation
       The RTC does a simple bit comparison to see if the two lowest order bits of the year
       counter are zero. If true, then the RTC considers that year a leap year. The RTC considers
       all years evenly divisible by 4 as leap years. This algorithm is accurate from the year 1901
       through the year 2099, but fails for the year 2100, which is not a leap year. The only effect
       of leap year on the RTC is to alter the length of the month of February for the month, day
       of month, and year counters. (Philips, UM10139, Volume 1: LPC214x User Manual, Rev. 01 � 15 August 2005 281) */
   /* Die Regel lautet: Alles, was durch 4 teilbar ist, ist ein Schaltjahr.
        Es sei denn, das Jahr ist durch 100 teilbar, dann ist es keins.
        Aber wenn es durch 400 teilbar ist, ist es doch wieder eins. */
  BOOL isLeapyear = 0;
  //struct tm *theTime;
  //rtcReadLuk (theTime, NULL);

 if((year % 4) == 0)
    isLeapyear = 1;
  if((year % 100) == 0)
    isLeapyear = 0;
  if((year % 400) == 0)
    isLeapyear = 1; 
//  if((theTime->tm_year % 4) == 0)
//    isLeapyear = 1;
//  if((theTime->tm_year % 100) == 0)
//    isLeapyear = 0;
//  if((theTime->tm_year % 400) == 0)
//    isLeapyear = 1;
  
  if ((month == 2) && isLeapyear) month_length +=  1;
  return month_length;
}