/**************************************************************************/
/*! 
    \file     ProjectConfig.h
    \author   K. Townsend (microBuilder.eu)
    \date     25 November 2009
    \version  1.00

    ProjectConfig.h contains various definitions and enumerations that
    determine how the project works.  By keeping this config information 
    in one central location it will often be easier to adjust the
    behaviour of your program, rather than having to search through
    dozens or hundreds of files to enable or disable different flags
    or find the name of a task handler, etc.
*/
/**************************************************************************/

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

// Included Peripherals
// ====================
// In order to make the code more portable, you can disable
// certain peripherals that may not be available on all
// devices (for example, RTC isn't available on certain chips)

#define CFG_RTC
#define CFG_ADC
#define CFG_FATFS

// Included Drivers
// ================
// You can comment out these definitions to remove any unused
// drivers from your compiled code, saving space and reducing
// any risk of errors

#define CFG_LED 1
#define CFG_LCD 0
//#define CFG_TCS3414
//#define CFG_TPS851

// General Project Settings
// ========================
/**************************************************************************/
/*! 
    General project settings
*/
/**************************************************************************/
#define CFG_PROJECT_NAME              (portCHAR *) "Olimex LPC-P2148 Evaluation Board"  // The name of this project if you wish to display it
#define CFG_PROJECT_VERSION_MAJOR     0                                       // The 'major' version of this project
#define CFG_PROJECT_VERSION_MINOR     1                                       // The 'minor' version of this project
#define CFG_PROJECT_COPYRIGHT         (portCHAR *) "(C) luki 2010-2011" // The copyright notice for this project if you wish to display it


//#define configGENERATE_RUN_TIME_STATS 0 // Timer 1 is used as counter for the windvelocity measurement
/**************************************************************************/
/*! 
    DataLogger settings
    - How many Temperatures(Voltages) on which Portpin and settings
    - Flowrate settings
    - Log interval time
*/
/**************************************************************************/
#define CFG_DATALOGGER
#define CFG_LOGDATA

/* log summary */
//#define logCDaySummary
//#define logAllTimeSummary

#ifndef logCDaySummary
  #undef logAllTimeSummary
#endif

#ifdef  CFG_LOGDATA
  #define LOG2FATFS                   // Log into File on SD
  #define LOG2MONITOR                 // Log continuosly to monitor (uart0/usb/[lan])
  
  /*! available Ports WITH special functions available and how are they used at Olimex's LPC-P2148 Evaluation Board.
      It would be possible using just AD0 with the advantage of power reduction, nevertheless I use both (AD0 and AD1) considering leave AOUT free for future uses

      -P0.0      TXD0      PWM1        GPIO         (NOT yet used, perhabs for extern multiple ADC)
      -P0.1      RXD0      PWM3        EINT0        (NOT yet used, perhabs for extern multiple ADC)
      -P0.2      SCL0      CAP0.0      GPIO*        LCD Backlight { L:off; H:on }
      -P0.3      SDA0      MAT0.0      EINT1*       Pumpenstellsignal detektieren

      -P0.8      TXD1      PWM4        AD1.1        (NOT yet used, perhabs UART1 needed for future Ethernet/WLAN/XBee/Bluetooth use)
      -P0.9      RXD1      PWM6        EINT3        (NOT yet used, perhabs UART1 needed for future Ethernet/XBee/Bluetooth use)
      -P0.21     AD1.6*    CAP13       PWM          Panel (_SLOG_ENTRY_ITEM.val_adc1)
      -P0.22     AD1.7*    CAP0.0      MAT0.0       Rücklauf (_SLOG_ENTRY_ITEM.val_adc2)
      -P0.25     AD0.4     AOUT                     contrast of display
      -P0.28     AD0.1*    CAP0.2      MAT0.2       Boiler oben (_SLOG_ENTRY_ITEM.val_adc3)
      -P0.29     AD0.2*    CAP0.3      MAT0.3       Boiler unten (_SLOG_ENTRY_ITEM.val_adc4) entspricht der Vorlauftemperatur
      -P0.30     AD0.3     EINT3*      CAP0.0       Volumenstrom; Poti on LPC-P2148 EvalBoard (_SLOG_ENTRY_ITEM.val_flowrate)
      -P1.16     PIPESTAT  GPIO*                    LCD Pin 16 Reset     GPIO1_FIOPIN2,Bit0
      -P1.17     PIPESTAT  GPIO*                    LCD Pin 14 Data7     GPIO1_FIOPIN2,Bit1
      -P1.18     PIPESTAT  GPIO*                    LCD Pin 13 Data6     GPIO1_FIOPIN2,Bit2
      -P1.19     PIPESTAT  GPIO*                    LCD Pin 12 Data5     GPIO1_FIOPIN2,Bit3
      -P1.20     PIPESTAT  GPIO*                    LCD Pin 11 Data4     GPIO1_FIOPIN2,Bit4
      -P1.21     PIPESTAT  GPIO*                    LCD Pin 6 E1         GPIO1_FIOPIN2,Bit5
      -P1.22     PIPESTAT  GPIO*                    LCD Pin 5 R/W        GPIO1_FIOPIN2,Bit6
      -P1.23     PIPESTAT  GPIO*                    LCD Pin 16 RS/CS     GPIO1_FIOPIN2,Bit7
  */
  //#define LOG_IF_FLOWRATE_NULL --> always log --> weather station
  
  /*<! Flowrate is going to be logged always over CAP0.0 at P0.30 */
  #define LOG_FLOWRATE               1
  //#define Rechnung Frequenz->Liter
  

  /*<! conversion from adcRead...() to Millivolt  */
  #define AREF   3300 /* ARef is 3300mV */
  #define ADSPAN 1024 /* 10Bit conversion*/
  #define get_AD_mV(intval) (AREF/ADSPAN*intval)

  /*<! Resolution of the flowmeter (2.5 liter per impuls)  */
  #define flowrateMeterImpulsVolume 2.5f

  /*<! Winddirection/AD values to log 
       - Winddirection: -[0-360°]
  */
  
  // P029
  #define adcWindDirectionRead                 adcRead0_1
  #define adcWindDirectionInit                 adcInit0_1

  // P028
  #define adcWindDirectionPwrRead              adcRead0_2
  #define adcWindDirectionPwrInit              adcInit0_2

  /* Winddirection Sensor:
   *   A LM334Z run by a 120Ohm/1% resistor delivers a constant current of Iset=67.7mV/Rset=67.7mV/120Ohm=564uA
   *   
   *   circuit:
   *   

            +5V

             |(2)
            .-.
    LM334Z  | | (1)
            | |-----.
            | |     |
            '-'     |
             |(3)   |
             |     .-.
             |     | |120Ohm
             |     | |
             |     '-'
             |      |
             0------.
             |
             |      
             v Iset=564uA          
             o---------------------o uADC
             |                     
             |                    
             | (schwarz)                      
            .-.                     
            | |Sensor [3,4]kOhm; Ulow=3000*564uA=1.6925V, Uhigh=4000*564uA=2.2566V                  
            | |                  dU=564.166mV @ (10Bit, 3.3V ADC) => 1024/3.3*0.564166=175 => 360°/175 => resolution 2.0564°
            '-'
             |(weiss)
             |
             '---------------------o GND ADC
             |
            ===
            GND 
   *
   */

  
  // if a allTimeSummary shall be generated
  //#define logAllTimeSummary


  enum _LOG_ITEM_STATE {
    OFF=0,
    INIT,
    IDLE,
    START,
    WAITING,
    SAVEVALUE
  } LOG_ITEM_STATE;

  
//  #ifdef LOG_FLOWRATE
//  #endif
    




  
#endif

/**************************************************************************/
/*! 
    I2C settings
*/
/**************************************************************************/
#define CFG_I2C_DEFAULT_TIMEOUT       100                                     // Default timeout, in milliseconds for generic read/write
#define CFG_I2C_DEBUG                 1                                       // Whether I2C debug information (i2CDump) is available or not

/**************************************************************************/
/*! 
    Whether the LED "blinky" task should be started after reset/boot
*/
/**************************************************************************/
#define CFG_LED_RUNLEDONSTARTUP       1                                       // Run the led task on startup (to confirm board is OK)
#define CFG_PLAY_STARTUP              1

/**************************************************************************/
/*! 
    Configuration settings for Chibi 802.15.4 wireless stack
*/
/**************************************************************************/
// #define CFG_CHIBI
// #define CFG_CHB_DEBUG

/**************************************************************************/
/*! 
    Configuration settings for FATFS and SD Cards
*/
/**************************************************************************/
#define CFG_FATFS


/**************************************************************************/
/*! 
    Configuration settings for uIP
*/
/**************************************************************************/
//LUK #define CFG_UIP           // Enable uIP w/ ENC28J60 on SPI0
//LUK #define CFG_TELNETD       // Enable telnet server under uIP
//LUK #define CFG_HTTPD         // Enable http server under uIP
//LUK #define CFG_SNTP	  // Enable sntp client under uIP
//LUK #define CFG_DHCP          // Enable DHCP under uIP
//LUK #define CFG_AUTO_UIP      // Automatically start uIP at reboot (ignored if not CFG_UIP)
//LUK #define CFG_AUTO_DHCP     // Automatically to DHCP for an address at start (ignored if not CFG_UIP, CFG_DHCP and CFG_AUTO_UIP)
//LUK #define CFG_AUTO_SNTP     // Automatically to set the time via SNTP (ignored if not CFG_UIP and CFG_AUTO_UIP)

//  No UIP means no servers and no auto stuff
#ifndef CFG_UIP
#undef CFG_TELNETD
#undef CFG_HTTPD
#undef CFG_SNTP
#undef CFG_DHCP
#undef CFG_AUTO_UIP
#undef CFG_AUTO_DHCP
#undef CFG_AUTO_SNTP
#endif

//  Can't auto DHCP unless there's DHCP support, and auto requested
#if !defined CFG_DHCP || !defined CFG_AUTO_UIP
#undef CFG_AUTO_DHCP
#endif

//  We need an lvalue to pass to uipStart() to DHCP or not
#ifdef CFG_AUTO_DHCP
#define CFG_AUTO_DHCP_VALUE 1
#else
#define CFG_AUTO_DHCP_VALUE 0
#endif

/**************************************************************************/
/*! 
    Monitor settings

    CFG_MONITOR_UART0 should be defined if you wish to use UART0 for the 
    monitor, or CFG_MONITOR_USBSER if you wish to use USB Serial (CDC).
    Please note that only one of CFG_MONITOR_UART0 or CFG_MONITOR_USBSER can be
    defined at a time!  By default both operate at 9600 Baud 8N1.
*/
/**************************************************************************/
//#define CFG_MONITOR_UART0                              // Use UART0 for the monitor console
#define CFG_MONITOR_USBSER                                // Use USB Serial for the monitor console
#define CFG_MONITOR_PROMPT            "Command > "        // The 'command prompt' that will be displayed in the monitor
#define CFG_MONITOR_ALLOWRESET        1                   // Whether the user is allowed to issue the reset command
#define CFG_MONITOR_ALLOWI2C          1                   // Whether the user is allowed to send generic I2C commands
#define CFG_MONITOR_ALLOWSPI          1                   // Whether the user is allowed to send generic SPI commands



// Config Error Checking
// =====================

// Make sure that an input/output device is defined for monitor
#if !defined CFG_MONITOR_UART0 && !defined CFG_MONITOR_USBSER
    #error "You must define a monitor output: CFG_MONITOR_UART0 or CFG_MONITOR_USBSER"
#endif

// Make sure that only ONE device is defined for monitor
#if defined CFG_MONITOR_UART0 && defined CFG_MONITOR_USBSER
    #error "You can only define one of: CFG_MONITOR_UART0 or CFG_MONITOR_USBSER"
#endif



/**************************************************************************/
/*! 
    An enumeration of every xTaskHandle used for FreeRTOS 'tasks'.
    
    By defining the task handle here you can easily access any task
    without having to remember or look up the xTaskHandle name in
    dozens of different files.

    When creating a new task, you simply need to add a new task handle to
    this enumeration (anywhere before TASKHANDLE_LAST), and then reference
    the entry when you actually create your task, as in the example below:

    \code
    // Create a 'startup' task (assumes 'TASKHANDLE_STARTUP' is defined)
    xTaskCreate (vStartupTask, 
                 (const signed portCHAR * const)"Startup",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 configMAX_PRIORITIES,
                 &taskHandles[TASKHANDLE_STARTUP]);
    \endcode
*/
/**************************************************************************/
typedef enum
{
  TASKHANDLE_STARTUP,
  TASKHANDLE_MONITOR,
  TASKHANDLE_LED,
//LUK  TASKHANDLE_TCS3414,
//LUK  TASKHANDLE_TPS851,
//  TASKHANDLE_POTI,
//  TASKHANDLE_SETTIME,
//  TASKHANDLE_UIP,
//#if CFG_LCD == 1
  TASKHANDLE_LCD,
//#endif
  TASKHANDLE_TRACKLOG,
  TASKHANDLE_MEASTASK,
  TASKHANDLE_MEASSM,
//  TASKHANDLE_LOGGING,
#if configGENERATE_RUN_TIME_STATS == 1
  TASKHANDLE_RUNTIMESTATS,
#endif
  TASKHANDLE_LAST
}
taskHandle_e;

void * taskHandles [TASKHANDLE_LAST];

#endif

