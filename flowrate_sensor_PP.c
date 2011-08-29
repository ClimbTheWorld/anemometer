# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c"
# 18 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c"
# 1 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 1 3 4
# 17 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
# 1 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__crossworks.h" 1 3 4
# 22 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__crossworks.h" 3 4
typedef __builtin_va_list __va_list;
# 18 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 2 3 4
# 33 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
typedef unsigned long size_t;
# 45 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int putchar(int __c);
# 54 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int getchar(void);
# 66 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int puts(const char *__s);
# 83 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
char *gets(char *__s);
# 102 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int sprintf(char *__s, const char *__format, ...);
# 130 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int snprintf(char *__s, size_t __n, const char *__format, ...);
# 166 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int vsnprintf(char *__s, size_t __n, const char *__format, __va_list __arg);
# 182 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int printf(const char *__format, ...);
# 202 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int vprintf(const char *__format, __va_list __arg);
# 231 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int vsprintf(char *__s, const char *__format, __va_list __arg);
# 250 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int scanf(const char *__format, ...);
# 270 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int sscanf(const char *__s, const char *__format, ...);
# 296 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int vscanf(const char *__format, __va_list __arg);
# 322 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
int vsscanf(const char *__s, const char *__format, __va_list __arg);
# 337 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stdio.h" 3 4
typedef void FILE;
typedef long fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE *, fpos_t *);
char *fgets(char *, int, FILE *);
FILE *fopen(const char *, const char *);
int fprintf(FILE *, const char *, ...);
int fputc(int, FILE *);
int fputs(const char *, FILE *);
size_t fread(void *, size_t, size_t, FILE *);
FILE *freopen(const char *, const char *, FILE *);
int fscanf(FILE *, const char *, ...);
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
int getc(FILE *);
void perror(const char *);
int putc(int, FILE *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);
FILE *tmpfile(void);
char * tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE *, const char *, __va_list);
int vfscanf(FILE *, const char *, __va_list);
# 19 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c" 2


# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/FreeRTOS.h" 1
# 61 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/FreeRTOS.h"
# 1 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stddef.h" 1 3 4
# 29 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 62 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/FreeRTOS.h" 2


# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/projdefs.h" 1
# 58 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/projdefs.h"
typedef void (*pdTASK_CODE)( void * );
# 65 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/FreeRTOS.h" 2


# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./FreeRTOSConfig.h" 1
# 48 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./FreeRTOSConfig.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./lpc214x.h" 1
# 18 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./lpc214x.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./sysdefs.h" 1
# 19 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./sysdefs.h"
typedef unsigned char U8;
typedef signed char N8;
typedef unsigned short U16;
typedef signed short N16;
typedef unsigned int U32;
typedef signed int N32;
typedef int BOOL;

typedef volatile U8 REG8;
typedef volatile U16 REG16;
typedef volatile U32 REG32;

typedef int INT;
typedef unsigned int UINT;

typedef signed char CHAR;
typedef unsigned char UCHAR;
typedef unsigned char BYTE;

typedef short SHORT;
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned short WCHAR;

typedef long LONG;
typedef unsigned long ULONG;
typedef unsigned long DWORD;
# 19 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./lpc214x.h" 2
# 1271 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./lpc214x.h"
typedef struct __attribute__ ((packed))
{
  union
  {
    struct
    {
      unsigned int counter : 14;
      unsigned int rsvd15_31 : 18;
    };

    unsigned int i;
  };
}
rtcCTC_t;

typedef struct __attribute__ ((packed))
{
  union
  {
    struct
    {
      unsigned int seconds : 6;
      unsigned int rsvd7_6 : 2;
      unsigned int minutes : 6;
      unsigned int rsvd14_15 : 2;
      unsigned int hours : 5;
      unsigned int rsvd21_23 : 3;
      unsigned int dow : 3;
      unsigned int rsvd27_31 : 5;
    };

    unsigned int i;
  };
}
rtcCTIME0_t;

typedef struct __attribute__ ((packed))
{
  union
  {
    struct
    {
      unsigned int dom : 5;
      unsigned int rsvd5_7 : 3;
      unsigned int month : 4;
      unsigned int rsvd12_15 : 4;
      unsigned int year : 12;
      unsigned int rsvd28_31 : 4;
    };

    unsigned int i;
  };
}
rtcCTIME1_t;

typedef struct __attribute__ ((packed))
{
  union
  {
    struct
    {
      unsigned int doy : 12;
      unsigned int rsvd12_31 : 20;
    };

    unsigned int i;
  };
}
rtcCTIME2_t;
# 49 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./FreeRTOSConfig.h" 2
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./ProjectConfig.h" 1
# 188 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./ProjectConfig.h"
  enum _LOG_ITEM_STATE {
    OFF=0,
    INIT,
    IDLE,
    START,
    WAITING,
    SAVEVALUE
  } LOG_ITEM_STATE;
# 334 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./ProjectConfig.h"
typedef enum
{
  TASKHANDLE_STARTUP,
  TASKHANDLE_MONITOR,
  TASKHANDLE_LED,






  TASKHANDLE_LCD,

  TASKHANDLE_TRACKLOG,
  TASKHANDLE_MEASTASK,
  TASKHANDLE_MEASSM,




  TASKHANDLE_LAST
}
taskHandle_e;

void * taskHandles [TASKHANDLE_LAST];
# 50 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./FreeRTOSConfig.h" 2
# 86 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./FreeRTOSConfig.h"
extern void vConfigureTimerForRunTimeStats( void );
# 68 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/FreeRTOS.h" 2


# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/portable.h" 1
# 106 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/portable.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/../../Source/portable/GCC/ARM7_LPC2000/portmacro.h" 1
# 101 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/../../Source/portable/GCC/ARM7_LPC2000/portmacro.h"
 typedef unsigned long portTickType;
# 249 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/../../Source/portable/GCC/ARM7_LPC2000/portmacro.h"
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );
# 107 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/portable.h" 2
# 338 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/portable.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/mpu_wrappers.h" 1
# 339 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/portable.h" 2
# 349 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/portable.h"
 unsigned long *pxPortInitialiseStack( unsigned long *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters );





void *pvPortMalloc( size_t xSize ) ;
void vPortFree( void *pv ) ;
void vPortInitialiseBlocks( void ) ;
size_t xPortGetFreeHeapSize( void ) ;





long xPortStartScheduler( void ) ;






void vPortEndScheduler( void ) ;
# 71 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/FreeRTOS.h" 2




typedef long (*pdTASK_HOOK_CODE)( void * );
# 22 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c" 2
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h" 1
# 65 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h" 1
# 98 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h"
struct xLIST_ITEM
{
 portTickType xItemValue;
 volatile struct xLIST_ITEM * pxNext;
 volatile struct xLIST_ITEM * pxPrevious;
 void * pvOwner;
 void * pvContainer;
};
typedef struct xLIST_ITEM xListItem;

struct xMINI_LIST_ITEM
{
 portTickType xItemValue;
 volatile struct xLIST_ITEM *pxNext;
 volatile struct xLIST_ITEM *pxPrevious;
};
typedef struct xMINI_LIST_ITEM xMiniListItem;




typedef struct xLIST
{
 volatile unsigned long uxNumberOfItems;
 volatile xListItem * pxIndex;
 volatile xMiniListItem xListEnd;
} xList;
# 241 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h"
void vListInitialise( xList *pxList );
# 252 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h"
void vListInitialiseItem( xListItem *pxItem );
# 265 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h"
void vListInsert( xList *pxList, xListItem *pxNewListItem );
# 286 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h"
void vListInsertEnd( xList *pxList, xListItem *pxNewListItem );
# 298 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/list.h"
void vListRemove( xListItem *pxItemToRemove );
# 66 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h" 2
# 87 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
typedef void * xTaskHandle;




typedef struct xTIME_OUT
{
 long xOverflowCount;
 portTickType xTimeOnEntering;
} xTimeOutType;




typedef struct xMEMORY_REGION
{
 void *pvBaseAddress;
 unsigned long ulLengthInBytes;
 unsigned long ulParameters;
} xMemoryRegion;




typedef struct xTASK_PARAMTERS
{
 pdTASK_CODE pvTaskCode;
 const signed char * const pcName;
 unsigned short usStackDepth;
 void *pvParameters;
 unsigned long uxPriority;
 unsigned long *puxStackBuffer;
 xMemoryRegion xRegions[ 1 ];
} xTaskParameters;
# 393 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskAllocateMPURegions( xTaskHandle xTask, const xMemoryRegion * const pxRegions ) ;
# 434 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskDelete( xTaskHandle pxTask ) ;
# 489 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskDelay( portTickType xTicksToDelay ) ;
# 548 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskDelayUntil( portTickType * const pxPreviousWakeTime, portTickType xTimeIncrement ) ;
# 595 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
unsigned long uxTaskPriorityGet( xTaskHandle pxTask ) ;
# 637 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskPrioritySet( xTaskHandle pxTask, unsigned long uxNewPriority ) ;
# 688 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskSuspend( xTaskHandle pxTaskToSuspend ) ;
# 737 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskResume( xTaskHandle pxTaskToResume ) ;
# 757 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
long xTaskResumeFromISR( xTaskHandle pxTaskToResume ) ;
# 795 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskStartScheduler( void ) ;
# 848 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskEndScheduler( void ) ;
# 899 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskSuspendAll( void ) ;
# 951 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
signed long xTaskResumeAll( void ) ;
# 962 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
signed long xTaskIsTaskSuspended( xTaskHandle xTask ) ;
# 977 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
portTickType xTaskGetTickCount( void ) ;
# 991 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
unsigned long uxTaskGetNumberOfTasks( void ) ;
# 1017 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskList( signed char *pcWriteBuffer ) ;
# 1049 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskGetRunTimeStats( signed char *pcWriteBuffer ) ;
# 1070 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskStartTrace( signed char * pcBuffer, unsigned long ulBufferSize ) ;
# 1083 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
unsigned long ulTaskEndTrace( void ) ;
# 1103 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
unsigned long uxTaskGetStackHighWaterMark( xTaskHandle xTask ) ;
# 1113 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskSetApplicationTaskTag( xTaskHandle xTask, pdTASK_HOOK_CODE pxHookFunction ) ;







pdTASK_HOOK_CODE xTaskGetApplicationTaskTag( xTaskHandle xTask ) ;
# 1133 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
long xTaskCallApplicationTaskHook( xTaskHandle xTask, void *pvParameter ) ;
# 1150 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskIncrementTick( void ) ;
# 1173 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskPlaceOnEventList( const xList * const pxEventList, portTickType xTicksToWait ) ;
# 1190 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
signed long xTaskRemoveFromEventList( const xList * const pxEventList ) ;
# 1203 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskCleanUpResources( void ) ;
# 1213 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h"
void vTaskSwitchContext( void ) ;




xTaskHandle xTaskGetCurrentTaskHandle( void ) ;




void vTaskSetTimeOutState( xTimeOutType * const pxTimeOut ) ;





long xTaskCheckForTimeOut( xTimeOutType * const pxTimeOut, portTickType * const pxTicksToWait ) ;





void vTaskMissedYield( void ) ;





long xTaskGetSchedulerState( void ) ;





void vTaskPriorityInherit( xTaskHandle * const pxMutexHolder ) ;





void vTaskPriorityDisinherit( xTaskHandle * const pxMutexHolder ) ;





signed long xTaskGenericCreate( pdTASK_CODE pvTaskCode, const signed char * const pcName, unsigned short usStackDepth, void *pvParameters, unsigned long uxPriority, xTaskHandle *pxCreatedTask, unsigned long *puxStackBuffer, const xMemoryRegion * const xRegions ) ;
# 23 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c" 2



# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.h" 1
# 30 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.h"
int initFlowrateSensor(void);
int startReadingFlowrateSensor(void);



static volatile float flowCount = 0;
float get_FlowCount(void);
float incr_FlowCount(void);
float clr_FlowCount(void);
# 27 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c" 2

# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 1
# 22 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h"
# 1 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 1 3 4
# 38 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
void *memcpy(void *s1, const void *s2, size_t n);
# 53 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
void *memmove(void *s1, const void *s2, size_t n);
# 64 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
int memcmp(const void *s1, const void *s2, size_t n);
# 78 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
void *memchr(const void *s, int c, size_t n);
# 88 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
void *memset(void *s, int c, size_t n);
# 99 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strcpy(char *s1, const char *s2);
# 114 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strncpy(char *s1, const char *s2, size_t n);
# 127 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strcat(char *s1, const char *s2);
# 141 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strncat(char *s1, const char *s2, size_t n);
# 151 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
int strcmp(const char *s1, const char *s2);
# 164 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
int strncmp(const char *s1, const char *s2, size_t n);
# 176 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strchr(const char *s, int c);
# 188 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strnchr(const char *str, size_t n, int ch);
# 199 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
size_t strcspn(const char *s1, const char *s2);
# 210 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strpbrk(const char *s1, const char *s2);
# 222 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strrchr(const char *s, int c);
# 233 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
size_t strspn(const char *s1, const char *s2);
# 246 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strstr(const char *s1, const char *s2);
# 261 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strnstr(const char *s1, const char *s2, size_t n);







size_t strlen(const char *s);
# 280 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
size_t strnlen(const char *s, size_t n);
# 312 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strtok(char *s1, const char *s2);
# 331 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strsep(char **stringp, const char *delim);
# 343 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strtok_r(char *s1, const char *s2, char **s3);
# 357 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strdup(const char *s1);
# 369 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/string.h" 3 4
char *strerror(int num);


int strcoll(const char *str1, const char *str2);
size_t strxfrm( char *str1, const char *str2, size_t num);
# 23 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 2
# 1 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/time.h" 1 3 4
# 29 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/time.h" 3 4
typedef long clock_t;






typedef long time_t;
# 55 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/time.h" 3 4
struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};


struct timeval
{
  time_t tv_sec;
  long tv_usec;
};

clock_t clock(void);
time_t time(time_t *tp);





double difftime(time_t __time2, time_t __time1);
# 92 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/time.h" 3 4
time_t mktime(struct tm *__tp);







char *asctime(const struct tm *__tp);







char *asctime_r(const struct tm *__tp, char *__buf);






char *ctime(const time_t *__tp);






char *ctime_r(const time_t *__tp, char *__buf);






struct tm *gmtime(const time_t *__tp);






struct tm *gmtime_r(const time_t *__tp, struct tm *__result);






struct tm *localtime(const time_t *__tp);






struct tm *localtime_r(const time_t *__tp, struct tm *__result);
# 195 "C:/Program Files/Rowley Associates Limited/CrossWorks for ARM 2.0/include/time.h" 3 4
size_t strftime(char *__s, size_t __smax, const char *__fmt, const struct tm *__tp);
# 24 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 2
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/sysdefs.h" 1
# 25 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 2


# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/task.h" 1
# 28 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 2
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h" 1
# 72 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
typedef void * xQueueHandle;
# 136 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
xQueueHandle xQueueCreate( unsigned long uxQueueLength, unsigned long uxItemSize );
# 472 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
signed long xQueueGenericSend( xQueueHandle xQueue, const void * const pvItemToQueue, portTickType xTicksToWait, long xCopyPosition );
# 758 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
signed long xQueueGenericReceive( xQueueHandle xQueue, void * const pvBuffer, portTickType xTicksToWait, long xJustPeek );
# 773 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
unsigned long uxQueueMessagesWaiting( const xQueueHandle xQueue );
# 787 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
void vQueueDelete( xQueueHandle xQueue );
# 1080 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
signed long xQueueGenericSendFromISR( xQueueHandle pxQueue, const void * const pvItemToQueue, signed long *pxHigherPriorityTaskWoken, long xCopyPosition );
# 1169 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
signed long xQueueReceiveFromISR( xQueueHandle pxQueue, void * const pvBuffer, signed long *pxTaskWoken );





signed long xQueueIsQueueEmptyFromISR( const xQueueHandle pxQueue );
signed long xQueueIsQueueFullFromISR( const xQueueHandle pxQueue );
unsigned long uxQueueMessagesWaitingFromISR( const xQueueHandle pxQueue );
# 1194 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
signed long xQueueAltGenericSend( xQueueHandle pxQueue, const void * const pvItemToQueue, portTickType xTicksToWait, long xCopyPosition );
signed long xQueueAltGenericReceive( xQueueHandle pxQueue, void * const pvBuffer, portTickType xTicksToWait, long xJustPeeking );
# 1210 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
signed long xQueueCRSendFromISR( xQueueHandle pxQueue, const void *pvItemToQueue, signed long xCoRoutinePreviouslyWoken );
signed long xQueueCRReceiveFromISR( xQueueHandle pxQueue, void *pvBuffer, signed long *pxTaskWoken );
signed long xQueueCRSend( xQueueHandle pxQueue, const void *pvItemToQueue, portTickType xTicksToWait );
signed long xQueueCRReceive( xQueueHandle pxQueue, void *pvBuffer, portTickType xTicksToWait );





xQueueHandle xQueueCreateMutex( void );
xQueueHandle xQueueCreateCountingSemaphore( unsigned long uxCountValue, unsigned long uxInitialCount );





long xQueueTakeMutexRecursive( xQueueHandle xMutex, portTickType xBlockTime );
long xQueueGiveMutexRecursive( xQueueHandle xMutex );
# 1250 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/FreeRTOS/Source/include/queue.h"
 void vQueueAddToRegistry( xQueueHandle xQueue, signed char *pcName );
# 29 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 2

# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/ff.h" 1
# 71 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/ff.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/./sysdefs.h" 1
# 72 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/ff.h" 2
# 86 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/ff.h"
typedef struct _FATFS
{
    U16 id;
    U16 n_rootdir;
    U32 winsect;
    U32 sects_fat;
    U32 max_clust;
    U32 fatbase;
    U32 dirbase;
    U32 database;

    U32 last_clust;
    U32 free_clust;

    U32 fsi_sector;
    U8 fsi_flag;
    U8 pad2;


    U8 fs_type;
    U8 sects_clust;



    U8 n_fats;
    U8 drive;
    U8 winflag;
    U8 pad1;
    U8 win[512];
}
                               FATFS;




typedef struct _DIR
{
    U16 id;
    U16 index;
    FATFS* fs;
    U32 sclust;
    U32 clust;
    U32 sect;
}
                               DIR;




typedef struct _FIL
{
    U16 id;
    U8 flag;
    U8 sect_clust;
    FATFS* fs;
    U32 fptr;
    U32 fsize;
    U32 org_clust;
    U32 curr_clust;
    U32 curr_sect;

    U32 dir_sect;
    U8* dir_ptr;

    U8 buffer [512];
}
                               FIL;




typedef struct _FILINFO
{
    U32 fsize;
    U16 fdate;
    U16 ftime;
    U8 fattrib;
    char fname [8+1+3+1];
}
                               FILINFO;
# 190 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/ff.h"
# 1 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/disk.h" 1
# 19 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/disk.h"
typedef enum
{
 DRESULT_OK = 0,
 DRESULT_ERROR,
 DRESULT_WRPRT,
 DRESULT_NOTRDY,
 DRESULT_PARERR
}
DRESULT;

typedef enum
{
  DSC_COMMANDPASS = 0,
  DSC_NOTREADY,
  DSC_NOTPRESENT,
  DSC_PARAMETERSERROR,
  DSC_MISCOMPAREERROR,
  DSC_DISKCHANGED,
  DSC_UNKNOWNERROR,
}
diskStatusCode_e;




typedef U8 DSTATUS;
# 72 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/disk.h"
typedef struct
{
  diskStatusCode_e statusCode;
  BOOL writeProtect;
  BOOL mediaChanged;
}
mediaStatus_t;




DSTATUS diskInitialize (U8);
DSTATUS diskShutdown (void);
DSTATUS diskStatus (U8);
DRESULT diskRead (U8, U8 *, U32, U8);

DRESULT diskWrite (U8, const U8 *, U32, U8);

DRESULT diskIoctl (U8, U8, void *);
BOOL diskPresent (void);
const char *diskErrorText (DRESULT d);
void diskErrorTextPrint (DRESULT d);
# 191 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/fatfs/ff.h" 2




typedef enum
{
    FR_OK = 0,
    FR_NOT_READY,
    FR_NO_FILE,
    FR_NO_PATH,
    FR_INVALID_NAME,
    FR_INVALID_DRIVE,
    FR_DENIED,
    FR_EXIST,
    FR_RW_ERROR,
    FR_WRITE_PROTECTED,
    FR_NOT_ENABLED,
    FR_NO_FILESYSTEM,
    FR_INVALID_OBJECT,
    FR_MKFS_ABORTED
}
FRESULT;




const char *f_ferrorlookup (FRESULT d);
void f_printerror (FRESULT d);
FRESULT f_mount (U8, FATFS*);
FRESULT f_open (FIL*, const char*, U8);
FRESULT f_read (FIL*, void*, U16, U16*);
FRESULT f_write (FIL*, const void*, U16, U16*);
FRESULT f_lseek (FIL*, U32);
FRESULT f_close (FIL*);
FRESULT f_opendir (DIR*, const char*);
FRESULT f_readdir (DIR*, FILINFO*);
FRESULT f_stat (const char*, FILINFO*);
FRESULT f_getfree (const char*, U32*, FATFS**);
FRESULT f_sync (FIL*);
FRESULT f_unlink (const char*);
FRESULT f_mkdir (const char*);
FRESULT f_chmod (const char*, U8, U8);
FRESULT f_rename (const char*, const char*);
FRESULT f_mkfs (U8, U8, U8);




U32 get_fattime (void);
# 31 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h" 2
# 49 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h"
FIL* log_file;




FRESULT initLog();





FRESULT appendToLog(char *msg);


void loggingDoSomething(void);
signed long loggingStart (void);
signed long loggingStop (void);







volatile typedef struct
{

    char datetime[20];

    unsigned short val_adc1;
    unsigned short val_adc2;
    unsigned short val_adc3;
    unsigned short val_adc4;
    float flowvolume;
    float power;
} _SLOG_ENTRY_ITEM;
_SLOG_ENTRY_ITEM slog_entry_item;
# 94 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h"
volatile typedef struct
{
    char last_update[20];
    unsigned short sum_flowtime;
    float sum_flowvolume;
    unsigned short sum_energy;
    unsigned short sum_fin_profit;

} _CDAYLOG_ENTRY_ITEM;
_CDAYLOG_ENTRY_ITEM cdaylog_entry_item;
# 112 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/logging.h"
volatile typedef struct
{
    char last_update[20];
    unsigned short sum_count_days;
    unsigned long sum_flowtime;
    unsigned long sum_flowvolume;
    unsigned long sum_energy;
    unsigned long sum_fin_profit;
    unsigned short arithm_day_flowtime;
    unsigned short arithm_day_flowvolume;
    unsigned short arithm_day_energy;
    unsigned short arithm_day_cost;
} _CLOG_ENTRY_ITEM ;





void fillSlogEntryItem(char *datetime, unsigned short adc1, unsigned short adc2, unsigned short adc3, unsigned short adc4 );
void getLogFilename(char log, char *filename);

float getRpProWs(void);

void getDateTime(char *datetime);

void trackLog(void);
signed long trackLogTaskStart (void);
signed long trackLogTaskStop (void);


FATFS Fatfs[1];
FIL FileContLog, FileDayLog, FileMonthLog;






static char logFilename[18];
# 29 "C:/Users/lukas/Desktop/LPC2148CodeBase_v0.1__ff-v0-04/LPC2148CodeBase_v0.1__ff-v0-04/Source/flowrate_sensor.c" 2




int initFlowrateSensor(void) {

  (*((REG32 *) (0xe002c000))) = ((*((REG32 *) (0xe002c000))) & ~((unsigned int) 0x000000c0)) | ((unsigned int) 0x000000c0);





  (*((REG32 *) (0xe002c004))) = ((*((REG32 *) (0xe002c004))) & ~((unsigned int) 0x20000000)) | ((unsigned int) 0x20000000);


  clearFlowCount();

  return 0;
}

int startReadingFlowrateSensor(void) {
  clearFlowCount();

  return 0;
}

void stopReadingFlowrateSensor(void) {


}

float get_FlowCount(void) { return flowCount; }
float incr_FlowCount(void) { flowCount += (float)2.5f; return flowCount; }
float clr_FlowCount(void) { float endValue = flowCount; flowCount = 0; return endValue; }
