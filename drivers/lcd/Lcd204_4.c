// ********************************************************************
// Demoprogramm
// Inhalt: LCD (DIP204-4 4x20) mit (KS0073 Controller) ansteuern,
// im 4-Bit Parallel Mode
// (Der Jumper J2 des LCD muss auf 4/8 gel�tet sein!)
// LCD-Controller: KS0073 kompatibel
//                 f�r HD44780 sind �nderungen der Initialisierung
//                 und der Zeilenadressenzuordnung notwendig
// Stand: 13.09.2007
// SDCC-Version: M-IDE-51/SDCC 2.7.0
// AT89C51ED2: --code-loc 0x0000 --iram-size 256 --xram-loc 0x0000 --xram-size 0x0700
// AT89S8253:  --code-loc 0x0000 --iram-size 256
// ********************************************************************
// F�r 8051-Microcontroller, z.B. AT89C51ED2 oder AT89S8253
// Frequenz: 11.0592 MHz
// Code-Speicherbedarf: ca. 1kByte, keine XRAM-Verwendung
// Das Programm verwendet nur 8051/52 Standard-SFRs und wurde
// mit dem AT89C51ED2 getestet.
// ********************************************************************
// Die Programmfunktionen d�rfen f�r private Nutzung verwendet und
// ver�ndert werden. F�r gewerbliche Nutzung ist die Zustimmung
// der Authoren erforderlich. Die Nutzung erfolgt auf eigene Gefahr.
// F�r eventuell entstehende Sch�den wird keine Haftung �bernommen.
// ********************************************************************

//#include "at89c51ed2.h"   // Register des AT89C51ED2
//#include "at89s8253.h"   // Register des AT89S8253
#if CFG_LCD == 1
#include "lpc214x.h"
#include <string.h>      // Stingfunktionen
#include "lcd204_4.h"


// ********************************************************************
// Verz�gerungsschleife f�r kurze Zeit
// Zeit: Wartezeit in [zeit]
//       1 = 20us
//       2 = 28us
//       3 = 36us u.s.w. (gilt f�r 11.0952MHz)
//     255 = ca. 2ms
// ********************************************************************
void delay_us(BYTE zeit) {
BYTE zaehler;
  for ( zaehler = zeit; zaehler; zaehler-- ) {
   __asm volatile ( "NOP" );
  }
}

// ********************************************************************
// Verz�gerungsschleife f�r lange Zeit
// Zeit: Wartezeit in [zeit]
//       1 = ca. 10ms
//       2 = ca. 20ms
//       3 = ca. 30ms u.s.w.
//     255 = ca. 2,5s (gilt f�r 11.0952MHz)
// ********************************************************************
void delay(BYTE zeit) {
BYTE zaehler;
  for (zaehler = zeit; zaehler; zaehler--) {
    delay_us(255);  // dauert ca. 2ms
    delay_us(255);  // dauert ca. 2ms
    delay_us(255);  // dauert ca. 2ms
    delay_us(255);  // dauert ca. 2ms
    delay_us(255);  // dauert ca. 2ms
  }
}

// ***********************************************************************
// Schreiben eines Zeichens an das LCD-Modul im 8-Bit Parallel Mode
// �bergabe: lcd_byte : Auszugebendes Zeichen/Steuerzeichen
//           lcd_mode : 0 - Daten
//                      1 - Steuerzeichen
// ***********************************************************************
void write_lcd(BYTE lcd_byte, BOOL lcd_mode) {
BOOL lcd_busy = 1;
  // Testen ob LCD-Modul noch im internen Zyklus ist
  LCD_RW_SET();
  LCD_RS_CLR();
  while(lcd_busy) {
    LCD_E1_SET();
    delay_us(1);
    GPIO1_FIODIR2 &= ~(1<<1); // P1.17 as input; 'cause of we read the busy flag over LCD_DATA7
    if (!LCD_DATA7()) lcd_busy = 0; // BUSY-Flag abfragen
    GPIO1_FIODIR2 |= (1<<1); // P1.17 as output
    LCD_E1_CLR();
    LCD_E1_SET();
    // untere 4 Bit liegen jetzt an, werden nicht gebraucht
    // m�ssen aber ausgelesen werden
    LCD_E1_CLR();
    delay_us(1);   // kurze Pause um die Zykluszeit einzuhalten
  }
  // LCD-Anzeige ist zum Empfang neuer Zeichen bereit
  LCD_RW_CLR();
  if (lcd_mode) LCD_RS_CLR(); // Steuerzeichen
    else LCD_RS_SET(); // Daten
  // obere 4-Bit ausgeben
  if(lcd_byte & 0x80) LCD_DATA7_SET(); else LCD_DATA7_CLR();
  if(lcd_byte & 0x40) LCD_DATA6_SET(); else LCD_DATA6_CLR();
  if(lcd_byte & 0x20) LCD_DATA5_SET(); else LCD_DATA5_CLR();
  if(lcd_byte & 0x10) LCD_DATA4_SET(); else LCD_DATA4_CLR();
  LCD_E1_SET();
  LCD_E1_CLR();
  delay_us(1);   // kurze Pause um die Zykluszeit einzuhalten    
  // untere 4-Bit ausgeben
  if(lcd_byte & 0x08) LCD_DATA7_SET(); else LCD_DATA7_CLR();
  if(lcd_byte & 0x04) LCD_DATA6_SET(); else LCD_DATA6_CLR();
  if(lcd_byte & 0x02) LCD_DATA5_SET(); else LCD_DATA5_CLR();
  if(lcd_byte & 0x01) LCD_DATA4_SET(); else LCD_DATA4_CLR();
  LCD_E1_SET();
  LCD_E1_CLR();
  LCD_DATA7_SET();  // Datenlatch f�r R�cklesen vorbereiten (8051-Spezifik)
  LCD_DATA6_SET();
  LCD_DATA5_SET();
  LCD_DATA4_SET();
} 

// ***********************************************************************
// Ausgabe eines ASCII-Zeichen positioniert auf dem LCD-Modul
// �bergabe: lcd_x : Spalte (0...SPALTEN_MAX-1)
//           lcd_y : Zeile  (0...ZEILEN_MAX-1)
//           lcd_ascii : ASCII-Zeichen
// *********************************************************************** 
void write_byte_lcd(BYTE lcd_x, BYTE lcd_y, BYTE lcd_ascii) {
BYTE lcd_offset = 0;
  if (lcd_x > (SPALTEN_MAX - 1)) lcd_x = 0;
  if (lcd_y > (ZEILEN_MAX  - 1)) lcd_y = 0;
  switch (lcd_y) {
    case 0:  lcd_offset = 0x80; break;  // Zeile 1
    case 1:  lcd_offset = 0xA0; break;  // Zeile 2 
    case 2:  lcd_offset = 0xC0; break;  // Zeile 3
    case 3:  lcd_offset = 0xE0; break;  // Zeile 4 
    default: lcd_offset = 0x80;         // Zeile>4
  };
  write_lcd(lcd_x+lcd_offset,1);        // Kursorposition setzen
  write_lcd(lcd_ascii,0);               // Ausgabe des ASCII-Zeichen an der Kursorposition
}

// ***********************************************************************
// Ausgabe einer Zeichenkette positioniert auf dem LCD-Modul
// �bergabe: lcd_x : Spalte (0...SPALTEN_MAX-1)
//           lcd_y : Zeile  (0...ZEILEN_MAX-1)
//           lcd_zeichen : Adresse der auszugebenden format.  Zeichenkette
//           clr_line    : L�schen bis Zeilenende
//                         1 - L�schen
//                         0 - kein L�schen
// ***********************************************************************
void printf_lcd(BYTE lcd_x, BYTE lcd_y, BYTE *lcd_zeichen, BOOL clr_line) {
BYTE lcd_i;
BYTE lcd_offset = 0;
  if (lcd_x > (SPALTEN_MAX - 1)) lcd_x = 0;
  if (lcd_y > (ZEILEN_MAX  - 1)) lcd_y = 0;
  switch (lcd_y) {
    case 0:  lcd_offset = 0x80; break;  // Zeile 1
    case 1:  lcd_offset = 0xA0; break;  // Zeile 2 
    case 2:  lcd_offset = 0xC0; break;  // Zeile 3
    case 3:  lcd_offset = 0xE0; break;  // Zeile 4 
    default: lcd_offset = 0x80;         // Zeile>4
  }
  write_lcd(lcd_x+lcd_offset,1);        // Kursorposition setzen
  // Ausgabe der Zeichenkette ab der Kursorposition
  lcd_offset = strlen(lcd_zeichen);     // L�nge der Zeichenkette
  if (lcd_offset > SPALTEN_MAX) lcd_offset = SPALTEN_MAX;
  for(lcd_i = lcd_offset ; lcd_i ; lcd_i--) {
    write_lcd(*lcd_zeichen,0);
    lcd_zeichen++;
  }
  if (clr_line) {
    // L�schen bis Zeilenende
    for(lcd_i = SPALTEN_MAX - lcd_offset - lcd_x ; lcd_i ; lcd_i--) write_lcd(' ',0);
  }
}

// ***********************************************************************
// Blinkposition auf dem LCD-Modul setzen / Blinken ein/ausschalten
// �bergabe: lcd_x : Spalte (0...SPALTEN_MAX-1)
//           lcd_y : Zeile  (0...ZEILEN_MAX-1)
//           lcd_blink :   0 - Blinken/Cursor aus
//                         1 - Blinken an
//                         2 - Cursor  an
// ***********************************************************************
void blink_lcd(BYTE lcd_x, BYTE lcd_y, BYTE lcd_blink) {
BYTE lcd_offset;
  write_lcd(0x0C,1);                     // KURSOR ausschalten
  if (lcd_x > (SPALTEN_MAX - 1)) lcd_x = 0;
  if (lcd_y > (ZEILEN_MAX  - 1)) lcd_y = 0;
  switch (lcd_y) {
    case 0:  lcd_offset = 0x80; break;   // Zeile 1
    case 1:  lcd_offset = 0xA0; break;   // Zeile 2 
    case 2:  lcd_offset = 0xC0; break;   // Zeile 3
    case 3:  lcd_offset = 0xE0; break;   // Zeile 4 
    default: lcd_offset = 0x80;          // Zeile>4
  };
  write_lcd(lcd_x+lcd_offset,1);         // Blinkposition setzen
  if (lcd_blink == 1) write_lcd(0x0D,1); // Blinken ein
  if (lcd_blink == 2) write_lcd(0x0E,1); // Cursor ein
}

// ***********************************************************************
// L�schen des LCD
// ***********************************************************************
void clear_lcd(void) {
  write_lcd(0x01,1); // Diplay l�schen
  //LUK 2011-05-11 delay_us(200);     // Wartezeit, weil Clear-Befehl l�nger dauert (ca. 1.53ms)
  vTaskDelay(2 / portTICK_RATE_MS);
} 

// ***********************************************************************
// Grundinitialisierung des LCD-Moduls
// ***********************************************************************
void init_lcd(void) {
  //LUK 2011-05-11 delay(5); // ca. 50ms Wartezeit nach dem Einschalten
  delay(5);
  //vTaskDelay(50 / portTICK_RATE_MS);
  LCD_RES_CLR(); //LUK 2011-04-28
  delay(1); //LUK 2011-04-28
  LCD_RES_SET();
  LCD_RW_CLR();
  LCD_RS_CLR();
  LCD_DATA7_CLR();     // Initialisierung 0010 xxxx (4-Bit Mode) 
  LCD_DATA6_CLR();
  LCD_DATA5_SET();
  LCD_DATA4_CLR();
  LCD_E1_SET();
  LCD_E1_CLR();
  vTaskDelay(1); // ca. 10ms Wartezeit vTaskDelay(10)
  
  // Grundinitialisierung (4-Bit Parallel Mode)
  write_lcd(0x24,1);               // 24 0010 0100 (4Bit Bus RE=1)
  write_lcd(0x09,1);               // 09 0000 1001 (4 Zeilen Mode)
  write_lcd(0x20,1);               // 20 0011 0000 (4Bit Bus RE=0) 
  write_lcd(0x0C,1);               // 0000 1111 (Dipl. ein, Cursor aus, Cursor blinken aus)
  write_lcd(0x06,1);               // 0000 0110 (Autoinkrement)
  clear_lcd();                     // Display l�schen
}

// ********************************************************************
// Grund-Initialisierung
// ********************************************************************
void init_system (void) {
  // LCD Leitungen 
  // LCD-Backlight
  PCB_PINSEL0 = (PCB_PINSEL0 & ~PCB_PINSEL0_P02_MASK) | PCB_PINSEL0_P02_GPIO;
  GPIO0_FIODIR |= (1<<2);
  //GPIO0_FIOCLR |= (1<<0); // LCD Backlight off
  LCD_BLIGHT_OFF();
  LCD_BLIGHT_ON();
  LCD_BLIGHT_OFF();

  // P1.16..P1.23
  PCB_PINSEL2 &= ~(1<<3);
  
//  GPIO1_FIOMASK2 &= ~(1<<0);
  GPIO1_FIODIR2 |= 0xFF; // P1.16..P1.23 as output
  GPIO1_FIOPIN2 |= 0xFF;
  //LUK 2011-05-11 delay(255);
  vTaskDelay(900 / portTICK_RATE_MS); // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11
  GPIO1_FIOPIN2 |= 0x00;
  //GPIO1_FIOSET2 |= (1<<0);
  //delay(255);
  //GPIO1_FIOCLR2 |= (1<<0);

  LCD_BLIGHT_ON(); // Beleuchtung LCD einschalten
  LCD_E1_CLR(); // Enable-Pin LCD
//  LCD_RES_CLR(); //LUK 2011-04-28 
//  delay(1); //LUK 2011-04-28
  LCD_RES_SET(); // Reset-Pin LCD

  init_screenpool();
}

// ********************************************************************
// Hauptprogramm
// ********************************************************************
//void main (void) {
//  init_system();
//  init_lcd();
//  printf_lcd(0,0,"LCD-Grundfunktionen",1); // Einschaltmeldung  
//  printf_lcd(0,1,"LCD: DIP204 (KS0073)",1);  
//  printf_lcd(0,2,"V1.0 13.09.2007",1);  
//  printf_lcd(0,3,"SDCC-Version",1);  
//  delay(200);  // Pause ca. 2s
//  printf_lcd(0,3,"(4Bit parallel-Mode)",1);
//  blink_lcd(0,3,1); 
//  while(1);
//}

void init_screenpool(void) {
  /** [12]: number of screens
   *  [4]:  number of rows
   *  [20]: Text-Template without variable values to be written on screen
   */
//  reportScreen[12][4][20] = {
//   {"aktuelle Werte 1/2  ",
//    "aktiv seit      :  h",
//    "Panel             �C",
//    "R�cklauf          �C"},
//  
//   {"aktuelle Werte 2/2  ",
//    "Boiler oben       �C",
//    "Boiler unten      �C",
//    "Durchfluss       s/l"},
//  
//   {"Tageswerte     1/2  ",
//    "Laufzeit          ' ",
//    "umges. Vol.       l ",
//    "Energie           Wh"},
//  
//   {"aktuelle Werte 2/2  ",
//    "Leistung          W ",
//    "Profit            Fr",
//    "                    "},
//  
//   {"Monatswerte    1/3  ",
//    "Messtage          d ",
//    "Laufzeit       h  m ",
//    "Energie           Wh"},
//  
//   {"Monatswerte    2/3  ",
//    "Volumen           l ",
//    "Profit            Fr",
//    "Mw tPumpe/T       m "},
//  
//   {"Monatswerte    3/3  ",
//    "Mw Volumen/T      l ",
//    "Mw Energie/T      Wh",
//    "Mw Profit/T       Fr"},
//  
//   {"kont. Log      1/3  ",
//    "Messtage          d ",
//    "Laufzeit       h  m ",
//    "Energie           Wh"},
//  
//   {"kont. Log      2/3  ",
//    "Volumen           l ",
//    "Profit            Fr",
//    "Mw tPumpe/T       m "},
//  
//   {"kont. Log      3/3  ",
//    "Mw Volumen/T      l ",
//    "Mw Energie/T      Wh",
//    "Mw Profit/T       Fr"},
//
//   {"if no one else can  ", // Werbung / Startup 1/2 (knacksen aus Lautsprecher)
//    "help, and if you can",
//    "find them, may be   ",
//    "you can hire...     "},
//
//   {"        the         ", // Werbung / Startup 2/2 (opening title)
//    "                    ",
//    "       A-TEAM       ",
//    "                    "}
//
//
//
//    /*(Ten years ago / In 1972), a crack commando unit was sent to prison by a military court 
//    for a crime they didn't commit. These men promptly escaped from a maximum security stockade 
//    to the Los Angeles underground. Today, still wanted by the government, they survive as soldiers
//    of fortune. If you have a problem, if no one else can help, and if you can find them, maybe you can hire... 
//    The A-Team.*/
//  };

//  /** [12]: number of screens
//   *  [4]:  number of rows
//   *  [2]:  [0]: at which column the first letter of the number is located
//   *        [1]: number format of float
//   */
//  static const float reportScreenConfig[12][4][2] = {
//    {0 ,0,
//     14, 5.2,
//     16, 3,
//     16, 3},
//    
//    {0, 0,
//     16, 3,
//     16, 3,
//     16, 3,},
//
//    {0, 0,
//     16, 3,
//     16, 3,
//     14, 5.1},
//
//    {0, 0,
//     14, 5.1,
//     16, 3,
//     0, 0},
//
//    {0, 0,
//     16, 3,
//     15, 4,
//     14, 5.1},
//
//    {0, 0,
//     15, 4,
//     16, 3,
//     16, 3},
//
//    {0, 0,
//     16, 3,
//     16, 3,
//     16, 3,},
//
//    {0, 0,
//     16, 3,
//     16, 3,
//     14, 5.1,},
//
//    {0, 0,
//     15, 4,
//     16, 3,
//     16, 3},
//
//    {0, 0,
//     16, 3,
//     16, 3,
//     16, 3,},
//
//    {0, 0,
//     0, 0,
//     0, 0,
//     0, 0,},
//    
//    {0, 0,
//     0, 0,
//     0, 0,
//     0, 0,},
//  };

}

/**************************************************************************/
/*! 
    The main code that will execute as long as the task is active.
    The first parameter (vMyTask in this case) needs to match the
    name used when the task is created in the method just below.
*/
/**************************************************************************/
static portTASK_FUNCTION(vLCDTask, pvParameters __attribute__((unused)))
{
  // Do any required initialisation or 
  // set up any hardware before the task
  // begins executing for the first time

  // ToDo: ...
  init_system();
  vTaskDelay(10);
  init_lcd();
  LCD_BLIGHT_ON();

  vTaskDelay( 900 / portTICK_RATE_MS);  // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11
  vTaskDelay( 900 / portTICK_RATE_MS);  // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11
  vTaskDelay( 900 / portTICK_RATE_MS);  // eigentlich m�ssten es, so war es original, 2.5s gewartet werden, funktioniert jedoch. LUK 2011-03-11

  // The code within the for loop is your actual
  // task that will continously execute
  for (;;)  {
    //if(get_updateLCD())
    LCD_RS_SET();
      feedLCD();
   
    // vTaskDelay will cause the task to be delayed for 
    // a specified number of ticks
    //vTaskDelay(100);  // Wait 100 ticks or 1 second
  }
}

/**************************************************************************/
/*! 
    Creates a new task for the FreeRTOS Kernel and add it to the
    scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE lcdTaskStart (void)
{
  return xTaskCreate (
    vLCDTask,
    (const signed portCHAR * const) "LCD Task",
    (unsigned portSHORT) 376, //configMINIMAL_STACK_SIZE,
    NULL,
    (tskIDLE_PRIORITY + 1),
    &taskHandles [TASKHANDLE_LCD]);
}

/**************************************************************************/
/*! 
    Stops the task and deletes it from the task scheduler.
*/
/**************************************************************************/
signed portBASE_TYPE lcdTaskStop (void)
{
  if (!taskHandles [TASKHANDLE_LCD])
    return 0;
  
  vTaskDelete (taskHandles [TASKHANDLE_LCD]);
  taskHandles [TASKHANDLE_LCD] = NULL;

  return 1;
}
#endif