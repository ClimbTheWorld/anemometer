


/* #################################################################################################################################
### README for Port of FreeRTOS from microbuilder.eu to Olimex LPC-P2148 Evaluation Board
#################################################################################################################################
Base of the System:             http://www.microbuilder.eu/Projects/LPC2148ReferenceDesign.aspx
Code Version:                   0.1 - BETA 	15 December 2009 	Initial BETA release
Download:                       http://www.microbuilder.eu/Files/Projects/LPC2148RefDesign/LPC2148CodeBase_v0.1.zip
#################################################################################################################################*/




2010-12-15 




/*!
\mainpage LPC-P2148 Evaluation Board from Olimex with FreeRTOS from microBuilder.eu
\date 15-Dez-2010
\author Lukas Kempf, lukaskempf@gmail.com

\section s_listToLabs List of Lab Work
The following is the current list of all laboratory work during the Infotronic lecture:
- \ref page_Mainpage "Mainpage": we are installing all needed tools and do first steps
- \ref page_
- \ref page_Mainpage "SWPortFromMicroBuilder.eu": Steps for Port of FreeRTOS from microbuilder.eu to Olimex LPC-P2148 Evaluation Board
- \ref page_LED "LED": we are writing a driver for 4 LED's
- \ref page_Doxygen "Doxygen": we use doxygen to document our project
- \ref page_Mealy "Mealy": we create a Mealy Sequential State Machine
- \ref page_LEDMacros "LED Macros": we optimize our LED driver using macros
- \ref page_Platform "Platform": we adopt our LED driver to run on two platforms
- \ref page_SimpleEvents "Simple Events": we create a simple event handler
- \ref page_KBI "Keyboard Interrupt": we handle interrupts from the KBI module
- \ref page_Clock "Clock": We configure the clock of the system
- \ref page_Timer "Timer": Someone else wrote a timer, and now we have to take over
- \ref page_Trigger "Simple Trigger": we create the infrastructure for callbacks/triggers
- \ref page_Debounce "Debouncing": we debounce the 4 switches on our platform
- \ref page_LowPowerModes "Low Power Modes": we reduce the power dissipation of our board using low power modes
- \ref page_LowPowerFreq "Low Power Frequency": we adjust the clock frequency for a low power application
- \ref page_LCD "LCD": we attach a 2x16 character LCD to our system
- \ref page_PWM "PWM": we run the DC motor using a PWM signal
- \ref page_Quad "Quadrature": we decode the information from the quadrature sensor
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Mainpage Lab: Intro
\date 16-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- Install CodeWarrior on your machine. 

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform

\section s_hints Hints
- Application entry point (set up by linker) is in platform.c (_EntryPoint())
- Platform/hardware initialization is done in platform.c and platform.h.
- PL_Init() calls all other driver initialization routines.

\section s_journal Journal Questions
- Did you had any difficulties to install the software and download this application?
  If yes, how were you able to solve it?
- What is the role of _Startup() in start08.c?
- Have a look at platform.c and platform.h.
  Why is there a \#ifndef __PLATFORM_H_ / \#define __PLATFORM_H_?
- Inspect platform.h: what is the purpose of the functions like setReg8Bits()?
- What is the role of the 'derivative.h' header file?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_LED Lab: LED
\date 20-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We have to implement an LED driver controlling 4 LEDs on the Infotronic platform.
Following functionality shall be supported:
- LED_On(): enable/turn on one or many LEDs
- LED_Off(): disable/turn off one or many LEDs
- LED_Neg(): negate/toggle one or many LEDs
- LED_Get(): get the status (on or off) of the LEDs
- LED_Put(): set the status (on or off) of the LEDs

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3

\section s_hints Hints
- Application entry point (set up by linker) is in platform.c (_EntryPoint())
- Platform/hardware initialization is done in platform.c and platform.h.
- PL_Init() calls all other driver initialization routines.
- The LED driver is in LED.h and LED.c.
- Implement macros in led.h in order to easily change the used port.
- Implement a LED test driver to verify correct operation of the driver
- Document your solution in the lab journal. What are the challenges and how to solve them?

\section s_journal Journal Questions
- Describe your test strategy
- How can you reduce the current needed for the LEDs? Hardware? Software?
- How is your solution depending on the speed of the microcontroller?
- How would you implement your driver to support arbitrary ports for each LED?
Think about and implement this in the driver.

\section s_additional More...
Doxygen has been used to create this documentation. Doxygen plus all the needed components can be found with the links below
- Doxygen is a tool to create documentation out of source files: http://www.doxygen.org/
- Microsoft HTML Help was used to create compressed HTML help files (\c .chm): http://msdn.microsoft.com/library/default.asp?url=/library/en-us/htmlhelp/html/vsconHH1Start.asp
- The "dot" tool from graphviz was used to create diagrams and graphs: http://www.graphviz.org/
- LaTeX can been used to create PDF files: http://www.tug.org/interest.html#free

Install doxygen, dot and the MS Help compiler and study the provided documentation.
Document your work done with doxygen too.
The project has a subfolder named 'doxy' which contains the batch file 'run_doxy.bat' which does the necessary steps.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_LED Lab: LED
\date 20-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We have to implement an LED driver controlling 4 LEDs on the Infotronic platform.
Following functionality shall be supported:
- LED_On(): enable/turn on one or many LEDs
- LED_Off(): disable/turn off one or many LEDs
- LED_Neg(): negate/toggle one or many LEDs
- LED_Get(): get the status (on or off) of the LEDs
- LED_Put(): set the status (on or off) of the LEDs

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3

\section s_hints Hints
- Application entry point (set up by linker) is in platform.c (_EntryPoint())
- Platform/hardware initialization is done in platform.c and platform.h.
- PL_Init() calls all other driver initialization routines.
- The LED driver is in LED.h and LED.c.
- Implement macros in led.h in order to easily change the used port.
- Implement a LED test driver to verify correct operation of the driver
- Document your solution in the lab journal. What are the challenges and how to solve them?

\section s_journal Journal Questions
- Describe your test strategy
- How can you reduce the current needed for the LEDs? Hardware? Software?
- How is your solution depending on the speed of the microcontroller?
- How would you implement your driver to support arbitrary ports for each LED?
Think about and implement this in the driver.

\section s_additional More...
Doxygen has been used to create this documentation. Doxygen plus all the needed components can be found with the links below
- Doxygen is a tool to create documentation out of source files: http://www.doxygen.org/
- Microsoft HTML Help was used to create compressed HTML help files (\c .chm): http://msdn.microsoft.com/library/default.asp?url=/library/en-us/htmlhelp/html/vsconHH1Start.asp
- The "dot" tool from graphviz was used to create diagrams and graphs: http://www.graphviz.org/
- LaTeX can been used to create PDF files: http://www.tug.org/interest.html#free

Install doxygen, dot and the MS Help compiler and study the provided documentation.
Document your work done with doxygen too.
The project has a subfolder named 'doxy' which contains the batch file 'run_doxy.bat' which does the necessary steps.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Doxygen Lab: Doxygen
\date 17-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- Have all the required tools installed to create documentation with doxygen. 
- Update your project sources in order to have it documented with doxygen
  - as HTML files
  - as CHM (compressed HTML) files
- inspect the project.doxygen configuration file to explore additional possibilites

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform

\section s_hints Hints
- depending on your 'run_doxy.bat' batch file, you may need to add hhc.exe and other tools to your PATH environment variable

\section s_additional More...
Doxygen has been used to create this documentation. Doxygen plus all the needed components can be found with the links below
- Doxygen is a tool to create documentation out of source files: http://www.doxygen.org/
- Microsoft HTML Help was used to create compressed HTML help files (\c .chm): http://msdn.microsoft.com/library/default.asp?url=/library/en-us/htmlhelp/html/vsconHH1Start.asp
- The "dot" tool from graphviz was used to create diagrams and graphs: http://www.graphviz.org/
- LaTeX can been used to create PDF files: http://www.tug.org/interest.html#free

Install doxygen, dot and the MS Help compiler and study the provided documentation.
Document your work done with doxygen too.
The project has a subfolder named 'doxy' which contains the batch file 'run_doxy.bat' which does the necessary steps.

\section s_journal Journal Questions
- doxygen allows you to maintain To-Do lists. Why and how is this useful?
- In a similar way like To-Do lists you can create bug lists. How can this be accomplished using special commands? Which command is used for this?
- This file is processed by doxygen as well. It shows some ways to create lists and paragraphs.
  List the commands are used for this and read the documenation about their usage.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Mealy Lab: Mealy Sequential State Machine
\date 21-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We create a sequential state machine (more precise: a Mealy Sequential State Machine).
We have two inputs (a and b) and we change the state of our 4 LEDs in following way:
\image html MealyLed.jpg

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3

\section s_hints Hints
- refresh your knowledge about Mealy Sequential State Machines (Lipovski)
- create files mealy.c and mealy.h and add them to your project.
- create a function like GetInput() in mealy.c which returns you the input state
- create a function MEALY_Run() for the state machine itself
- draw on paper the state machine and verify it 'by hand' that it will work
- implement the mealy state machine in mealy.c
- if you implement the mealy machine as table, then it is a good idea to have the table
  in ROM (means: use the 'const' qualifier for it). Check the linker .map file if you are
  not wasting RAM.
- call the mealy state machine from your main() routine.
- Try your state machine using the Debugger Visualization Tool as input.
- Document your state machine in the sources using dot and doxygen.
  Below a dot source with corresponding created dot graph:
  \verbatim
  \dot
  digraph example_dot_graph {
      node [shape=triangle];
      rankdir=RL;
      A    [fillcolor=lightblue,style=filled,label="A" ];
      B    [fillcolor=green,style=filled,label="B" ];
      C    [fillcolor=red,style=filled,label="C"];
      A -> A [label="a/something"];
      A -> B -> C -> A -> C;
      B -> B [label="b"];
  }
  \enddot
  \endverbatim
  \dot
  digraph example_dot_graph {
      node [shape=triangle];
      rankdir=RL;
      A    [fillcolor=lightblue,style=filled,label="A" ];
      B    [fillcolor=green,style=filled,label="B" ];
      C    [fillcolor=red,style=filled,label="C"];
      A -> A [label="a/something"];
      A -> B -> C -> A -> C;
      B -> B [label="b"];
  }
  \enddot

\section s_journal Journal Questions
- Some compilers may not allow the usage of multidimensional arrays (CodeWarrior does). How would you then implement the Mealy Sequential State Machine?
- Explore the dot documentation: what feature do you find the most useful for you?
- You used the Visualization Tool in the debugger to show on your screen the status of the LEDs.
  You may have notized some delays between the actual hardware and the view on the PC. How could you minimize this?
- Think about how the debugger is getting the status/variables from your platform/board with the Visualization tool:
  can you use this for many variables, or would this not be a good idea? Why?
- Discuss the advantages/disadvantages of using a Mealy Sequential Machine.

\section s_additional More...
- dot is a very, very powerful tool and you can do pretty much 'anything' with.
  Take some time to read the assoziated dot documents to explore the features.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_LEDMacros Lab: LED Macros
\date 27-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
Using function calls for our LED driver is rather an overkill.
In order to reduce code size and to improve code speed we want to replace the function calls with macros
to have the functionality inlined. For easier debugging we want to have to versions of our driver:
- version which is using methods/function calls
- version which is using macros to have the functionality inlined

In order to switch between the two versions, we can use a macro ::LED_USE_MACROS.

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- MC13213 SRB: refer to the board documentation

\section s_hints Hints
- add a new macro ::LED_USE_MACROS to led.h
- extend the interfaces in led.h (where appropriate) to have the functionality inlined with macros
- make sure you have your new version of the driver documented properly with doxygen
- you can verify the code size for your application in the .map file generated by the linker.
At the bottom of the map file there is a number with the size of blocks downloaded: this gives the number of (code) bytes.
- have fun :-)  

\section s_journal Journal Questions
- it does not make sense to inline all functions/methods of the interface in led.h. What is the criteria for making inlining with macros worthwile?
- why is it beneficial to still keep a version of the LED driver with function/method calls? Describe a use case.
- compare the code size of your application with and without the inlined version (using macros): how much code did you save (absolute number and % number)?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Platform Lab: Platform
\date 24-Feb-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We have to adopt/change our LED driver to run on two different platforms:
- the Medusa Trainer (GB60)
- the MC13213 ZigBee SRB (Sensor Reference Board with GT60)

The two derivatives (GB60 and GT60) are not making a difference for us (for now).
However, the LED's on the two platforms are connected differently. 
The goal is to create a CodeWarrior project which can be switched from one platform to the other using defines.

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- MC13213 SRB: refer to the board documentation

\section s_hints Hints
- compare the board documentation/layout both for the Infotronic platform and the SRB
- use platform.h to set up your platform settings
- use ::PL_TARGET_BOARD to define your current platform (e.g. ::MC1321XSRB or ::MC1320XTRAINER) 
- add a macro ::PL_HAS_LED to indicate if you have LED's or not. Make sure you can compile your project both ways.
- depending on your platform, you need to use different ports to access the LED's
- The LED's are not connected the same way (anode/cathode) on both platforms. Use another macro depending on your platform to reflect this.
- Run your project/tests on both platform to verify the functionality
  - to debug the trainer project:
    - change the connection to 'SofTec HCS08'
    - in the debugger dialog, select 'PK-HCS08GB60'
  - to debug the SRB project:
    - change the connection to 'P&E Multilink/Cyclone Pro'
- make sure you have your new version of the driver documented properly with doxygen
- have fun :-)  

\section s_journal Journal Questions
- how did you solve the dependency on different ports in your driver?
- how did you solve the fact that the two platforms are using different bits in the output port?
- how did you solve the different ways how LED's can be connected to microcontroller pins in your driver?
- One way to switch between different platforms is to change the ::PL_TARGET_BOARD macro in platform.h.
  What other solutions could you implement so you do not have to touch/change the platform.h header file?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_SimpleEvents Lab: Simple Events
\date 9-Mar-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We create a simple event handler. The goal is that we can record events and process them later (e.g. a button pressed).

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- MC13213 SRB: refer to the board documentation

\section s_hints Hints
- create the files events.c and events.h and declare the interfaces (see lecture slides).
  If you want, you can use the templates provided on ILIAS
- implement the method to add an event. Keep in mind that the parameter (depending on your implementation) could carry multiple events.
- do not forget to call your event initialization method from PL_Init()
- Add an first event ::EVNT_Init which is used to show your system startup with LED's
- think about reentrancy: be aware that an interrupt can happen any time. What are the consequences?
- In the next paragraph you find some useful code you may use in your application.
- make sure you have your new version of the application documented properly with doxygen
- have fun :-)  

\section s_critical Critical Sections
\code
extern volatile unsigned char PL_CCR_reg;  /*!< Current CCR register, used by EnterCritical() and ExitCritical()  */
#define SaveStatusReg()     { asm PSHA; asm TPA; asm SEI; asm STA PL_CCR_reg; asm PULA; } /*!< It saves CCR register and disable global interrupts. */
#define RestoreStatusReg()  { asm PSHA; asm LDA PL_CCR_reg; asm TAP; asm PULA; } /*!< It restores CCR register saved in SaveStatusReg(). */
#define EnterCritical()     SaveStatusReg()
#define ExitCritical()      RestoreStatusReg()
\endcode

\section s_journal Journal Questions
- right now we want to support only a few events (up to 8).
  How would you change your implementation to support more than 8 events? More than 32 events?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_KBI Lab: Keyboard Interrupt
\date 9-Mar-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We are going to recognize buttons pressed using the KBI (Keyboard Interrupt).
Additionally we are preparing our own startup sequence (reset vector) and redirecting the reset vector to PL_Startup().
The application shall work both on the TRAINER and as well on the MC13213 SRB.

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3

\section s_hints Hints
- You need to catch vectors using the vector table.
  There is a vectors.c file in the template on ILIAS you can use.
  Note that the vectors.c is using ::PL_HAS_KBD so you need to add this to your platform.
- This vectors.c is using PL_Startup() for the reset vector/application entry point.
  If you had the reset vector defined as below in your prm file, you may get a linker error that the vector at 0xFFFE is allocated twice.
  In that case you need to remove the VECTOR line (or comment it using a C++ // comment)
\code
VECTOR 0 _Startup /* Reset vector: this is the default entry point for an application. */
\endcode
- With this, the reset is now pointing to PL_Startup(). So we need to implement this now in platform.c:
\code
#include "startup.h"
#pragma NO_FRAME
#pragma NO_EXIT
void PL_Startup(void) {
  /* Initialisation code after reset. We need to do some things before anything else...*/
  /* This entry point is set up in the linker configuration file. */

  /* Common initialization of the write once registers */
  DisableWatchdog();
  __asm   jmp _Startup; /* Jump to C startup code */
}
\endcode
- in order to disably watchpoints, you will need
\code
#if (PL_TARGET_BOARD==MC1321XSRB) || (PL_TARGET_BOARD==MC1320XTRAINER) 
  #define DisableWatchdog() \
          /* SOPT: COPE=0,COPT1,STOPE=0,??=1,??=0,??=0,BKGDPE=1,??=1 */ \
          setReg8(SOPT, 0x53); /* disable watchdog */
#else
  #define DisableWatchdog() \
          /* SOPT1: COPE=0,COPT=1,STOPE=0,??=0,??=0,RSTOPE=0,BKGDPE=1,RSTPE=0 */ \
          setReg8(SOPT1, 0x42);                 
#endif
\endcode
- verify that after you download your code to the target, that the reset sequence is going through PL_Startup().
- You need to set up the KBI block on the chip properly in KBD_Init().
- Use EVNT_SetEvents() to create events about keys pressed.
- In EVNT_HandleEvents() handle your events (like ::EVNT_SW0_PRESSED)
- make sure you have your new version of the application documented properly with doxygen
- have fun :-)  

\section s_journal Journal Questions
- if you add the vector.c to your project and if you have a VECTOR 0 in your .prm file, why is the linker complaining?
- why do we want to use a special PL_Startup()?
- Did you see the keys bouncing? How?
- How would your code look like for switches which are connected to pull-down resistors instead of pull-up resistors?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Clock Lab: Clock
\date 16-Mar-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
A realtime system needs precise clocks infrastructure.
In this lab session we are going to set up our system with a 16 MHz clock, and we are able to verify it.

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3

\section s_hints Hints
- read first through the AN2494 and answer the questions in \ref s_journal2994.
  The goal is that to understand the clock configuration of the GB60 and GT60.
- Consult as well the GB60/GT60 Reference manual MC9S08GB60_ref2.3.pdf as needed
- Set up your bus clock as close as possible to 16 MHz using an external reference source
- You will need to set up the clock setting early in the PL_Startup()
- Have your implementation portable so it runs both on the Trainer as well on the SRB
- Below is an example implementation for using a 8 MHz external crystal
\code
  /*  System clock initialization */
#if PL_BUS_CLOCK_MHZ==16
  #if PL_BOARD_8_000_MHZ_CRYSTAL
    /* ICGC1: HGO=0,RANGE=1,REFS=1,CLKS1=1,CLKS0=1,OSCSTEN=1,LOCD=0,??=0 */
    setReg8(ICGC1, 0x7C);                 
    /* ICGC2: LOLRE=0,MFD2=0,MFD1=0,MFD0=0,LOCRE=0,RFD2=0,RFD1=0,RFD0=0 */
    setReg8(ICGC2, 0x00);                 
    ICGTRM = *(unsigned char*)0xFFBE;    /* Initialize ICGTRM register from a non volatile memory */
    while(!ICGS1_LOCK) {                 /* Wait */
    }
  #endif
#endif
\endcode
- You can use the Clock Calculation Excel sheet on ILIAS as a helper to set up ICG1/ICG2 registers
- Test your settings both on the Trainer and the SRB.
  It may help you to know the instruction cycle count for a NOP instruction is one cycle.
- Have fun :-)  

\section s_journal2994 Journal Questions (AN2494)
- Read AN2494. You can skip for now the things around stop mode and low power modes (this will be a future topic)
- Make sure you understand the different modes of the ICG (there are 5 modes).
  Why does the controller offer all these modes?
- List the advantages/disadvantages either using an external clock source or using an internal clock source.
  Consider system costs, PCB real estate, pin counts and accuracy.
- What is the advantage of using an external square wave clock source compared to an external crystal/resonator?
- why is trimming the internal reference generator important?
- The block diagram lists the BDC which is the Background Debug Controller.
  This is a block dedicated for debugging. This is what we connect to with the debugger.
  The BDC is used for the BDM (Background Debug Mode), and this is the 6 pin header we use with the P&E Multilink cable.
  The BDC is is implementing a one wire (plus additional GND/Ground) debug connection for a debugger.
  Why does this block need as well a clock source?
- What is the maximum bus clock frequency for the HCS08GB60/GT60?
- Inspect the crystal of the Trainer Box. What is its frequency?
- Inspect the MC13213 SRB: what is its external clock configuration/frequency?


\section s_journal2994 Journal Questions (Implementation)
- Think about different ways to verify that your system is running at a bus clock speed of 16 MHz and describe them.
- Use the Infotronik Lab Equipment to proove and measure that your system is running at 16 MHz Bus Clock and document it.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Timer Lab: Timer
\date 16-Mar-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
You worked together with a co-worker on an important project.
His task was to implement a 10 ms periodic timer in your embedded application
Unfortunately he has left the company, and all what you have is his source code.
You need to take over his work and integrate it into your project.
As such, you need to verify that the timer is working as specified.
  -# Understand how the timer (TPM block) works
  -# Have timer.ch and timer.c documented using doxygen
  -# Integrate timer.h and timer.c into your project

\section s_hardware Hardware
- HCS08GB60 & HCS08GT60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA2
   - SW1: PTA3
   - SW2: PTA4
   - SW3: PTA5

\section s_hints Hints
- You have received timer.h and timer.c source files.
  Unfortunately there is no documentation for it, so you need to create that part (doxygen).
- Research in the GB60 reference manual how the timer (TPM) module works.
- Find out what is going on in timer.c. Document your findings in the sources.
- The goal is that you document the 'what', the 'why' and the 'how'.
  If pass your sources with the documentation to someone else, he would be in a better position than you are right now.
- Have fun :-)  

\section s_journal Journal Questions
- Based on your bus clock speed, calculate the prescaler and modulo value you would use for a 10 ms timer.
- Identify in the code the prescaler and modulo value used. Are they different from your values?
- Why are your values different from the ones in the code? Or you have the same values?
- Use the values in the source code and calculate based on your clock speed the timer period.
  If needed, change the timer to have a 10ms period.
- Integrate timer.h and timer.c into your application. What is needed beside of adding the source files to your project?
- You need to test that your timer implementation has a period of 10 ms.
  Write down a testing strategy how you can test it.
  Use the lab equipement to measure the timer period and to verify it is working properly.
  Document the measurement in your lab journal (e.g. with a screenshot).
- Find out what a 'static local' variable is (search the internet, e.g. use http://en.wikipedia.org/wiki/Local_variable)
- To demonstrate that the timer is working at a 10 ms rate:
  add code to the interrupt routine to flash a LED every second.
  Use a static local variable to implement this.  
- What is the effect of the following code in the timer interrupt routine?
\code
(void)TPM1C1SC;
\endcode
- What is special about clrSetReg8Bits(TPM1SC, 0x10, 0x08)? Why is it done that way?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Trigger Lab: Simple Trigger
\date 16-Mar-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
We implement the infrastructure so the application can install simple triggers.
Simple triggers are callbacks we can install for the future which can be very useful.
To proove and test our design, we implement a flashing LED (flashing every second).
For the implementation consider
- Reentrancy: the code shall be reentrant
- Portability: use generic (and portable) types (so no 'char' or 'int', etc)
- Extensiblity: it shall be possible to add new triggers to the list in trigger.h without changing trigger.c
- Proof of functionality: demonstrate your implementation with using ::TRG_LED_BLINK to blink a LED every second

\section s_hardware Hardware
- HCS08GB60 & HCS08GT60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA2
   - SW1: PTA3
   - SW2: PTA4
   - SW3: PTA5

\section s_hints Hints
- we need to have a set of new files: trigger.c and trigger.c. They are provided in the template.
- In trigger.h we are including platform.h for having machine independant types for 'byte' and 'word'
- make sure that your actual implementation of the trigger 'list' in memory is depending on ::TRG_LAST
- take care that your implementation is reentrant
- you need to add a 10ms timer to your system. Use the timer you implemented in the previous lab session.
- Use an event (e.g. ::EVNT_INIT) to start your LED flashing heartbeat
- verify and test your implementation with a flashing LED
- have fun :-)  

\section s_journal Journal Questions
- What is the difference if you increment the tick counter in TRG_AddTick() 
  either at the beginning of the function or if you increment it at the end of the function?
  The pseudo code in the slide deck does it at the beginning, but is this the correct way?
- The tick counter is designed in such a way that the counter will run over (0xffff -> 0 -> 1 -> ...). Think about the consequences of this.
- Why is it important to use types like 'byte', 'word', 'dword' instead of plain char, short or int?
- Find out how the type 'char' is defined for our Metrowerks HCS08 compiler. What is the minimum/maximum decimal number it can hold?
- discuss the advantages and disadvantages of your implementation with other groups: what would you change/improve?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Debounce Lab: Debouncing
\date 23-Mar-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- First, make sure you see the keys bouncing (document this in your lab journal)
- Support both platforms
  - Trainer
  - SRB Board
- Debounce the 4 keys on the platform
- Detect short and long key press
- For short keys toggle (negate) the corresponding LED
  - SW0 -> Toggle LED0
  - SW1 -> Toggle LED1
  - SW2 -> Toggle LED2
  - SW3 -> Toggle LED3
  
  Use events to do this (don't do it directly in the interrupt service routine)
- For long keys toggle all other LED
  - long SW0 -> Toggle LED1|LED2|LED3
  - long SW1 -> Toggle LED0|LED2|LED3
  - long SW2 -> Toggle LED0|LED1|LED3
  - long SW3 -> Toggle LED0|LED1|LED2

\section s_hardware Hardware
- HCS08GB60 & HCS08GT60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA2
   - SW1: PTA3
   - SW2: PTA4
   - SW3: PTA5

\section s_hints Hints
- Implement debouncing of the keys in keyboard.c. Use your previous work as base.
- You need to define a ::PL_KBD_PULLUP_RESISTORS macro so you can handle switches with pull-up and pull-down resistors.
- You will need to add/define a new trigger:
  - ::TRG_KEYPRESS
- for the state machine you could use following code snippet:
\code
/*! States of the key detection state machine. */
typedef enum {
  KBD_KEY_IDLE = 0,     /*<! Initial idle state */
  KBD_KEY_PRESSED,      /*<! Key pressing detected, see if it is a long key */
  KBD_KEY_WAIT_RELEASE, /*<! got a long key, wait for release */
} KBD_KeyStateKinds;

static KBD_KeyStateKinds KBD_KeyState = KBD_KEY_IDLE;
  /*!< status of the state machine to detect long and short keys */
\endcode
- In a first step, only detect short key presses. After this is working, implement the long key presses.
- For the long key press detection: enhance EVNT_HandleEvents() to deal with the new events
  - ::EVNT_SW0_LPRESSED
  - ::EVNT_SW1_LPRESSED
  - ::EVNT_SW2_LPRESSED
  - ::EVNT_SW3_LPRESSED
  
  Measure the time for the long key press with counting the number of times you stay within ::KBD_KEY_PRESSED
- To transition from one state to anoter TRG_AddTrigger() is used with a time variable (in 10ms units).
  Write your code in such a way (with macros) so you have the debouncing time and long key press time specified.
  Below is a possible example:
\code
#define KBD_LONG_KEY_TIME_MS 500  /*!< Long key pressing time, in ms units */
\endcode
- Make sure your code is fully reentrant
- Test the functionality
- have fun :-)  

\section s_journal Journal Questions
- Show in your journal (screenshot/etc) that you have seen the key bouncing. Use your lab equipment for this.
- We are using events like ::EVNT_SW0_PRESSED instead of performing directly the actions resulting on a key press.
  Why are we doing this?
- Which challenges did you see to have your implementation working on both platforms (having the code cross-platform)?
- Debouncing could be done in a simpler way without a state machine like we did it here. What is the advantage/disadvantage using the state machine method?
- Summarize what you have learned implementing debouncing using simple triggers and a state machine.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_LowPowerModes Lab: Low Power Modes
\date 6-Apr-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- Support both platforms
- Support following platforms
  - Trainer
  - SRB Board
  - DEMOGB60 Axiom Board
- Reduce the power consumption as much as you can. Goal is below 1.5 mA. Measure it.
- Still, your shall use debouncing for the keys and light up the LED's for the key press.

\section s_hardware Hardware
- HCS08GB60 & HCS08GT60
- Infotronic base platform (TRAINER and DEMOGB60 Axiom board)
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA2
   - SW1: PTA3
   - SW2: PTA4
   - SW3: PTA5

\section s_hints Hints
- Read through AN2493
- We are going to reduce power consumption in steps: Base (what you have right now) -> Wait Mode -> Stop3 Mode
- Baseline
  - Measure the voltage and document it in your workbook
  - Measure the current power consumption as a base line (both running and stopped):
    - Target stopped by debugger
    - Baseline (target running, no power optimization)
  - You will notice that the LED's are using some current too. 
    So you need to take this into account. 
    Measure the amount of current needed for a LED.
  - In order to measure current without the LED's involved, you may use ::PL_UI_HAS_1S_LED_HEARTBEAT
    to switch off the LED heartbeat.
- Wait Mode
  - In order to keep your code portable, you may add following defines to platform.h:
    \code
    #define PL_HAS_LOW_POWER 1   /*!< Set to 1 if platform supports low power modes */
    /* various low power modes */
    #define PL_HAS_LOW_POWER_WAIT  (1 && PL_HAS_LOW_POWER)  /*!< if we support WAIT low power mode */ 
    #define PL_HAS_LOW_POWER_STOP3 (0 && PL_HAS_LOW_POWER)  /*!< if we support STOP3 mode */
    \endcode
  - Below you find some usefule macros for platform.h to be used in your application
    \code
    #define PL_SetWaitMode()  __asm("WAIT") /*!< Set WAIT mode */
    #define PL_SetSTOPMode()  __asm("STOP") /*!< Set STOP mode */
    \endcode
  - Implement the WAIT mode: find a good place where to put the CPU into wait mode.
    Hint: this is where the CPU hase nothing to do, right?
  - Measure the current consumption
- Stop3 mode
  - in order to use the STOP3 mode, you need to set up the ::SOPT register in PL_Startup():
  \code
  #if PL_HAS_LOW_POWER_STOP3
    /* SOPT: COPE=0,COPT=1,STOPE=1,??=0,??=0,??=0,BKGDPE=1,??=1 */
    setReg8(SOPT, 0x63); /* long COP timeout, disable watchdog and enable stop mode */
  #else
    DisableWatchdog();
  #endif
  \endcode
  - We to use an RTI (Real Time Interrupt) to wake up every second from STOP mode.
    Below is a code you could use to handle the RTI interrupt:
  \code
  /* ----------------- RTI --------------------------------------*/
  #if PL_HAS_LOW_POWER_RTI
  /*!
    \brief Real Time Interrupt (RTI)
   */
  void interrupt TMR_RTI_Interrupt(void) {
    /* RTI is called every 1s, and will not happen in run mode (e.g. only in STOP mode) as we use internal oszillator.
       NOTE: in active BDM debug mode (e.g. debugging) there will be no RTI interrupt!
    */
    SRTISC_RTIACK = 1; /* Reset real-time interrupt request flag */
  #if PL_UI_HAS_1S_LED_HEARTBEAT
    LED_Neg(LED_0);
  #endif
  }
  #endif /* PL_HAS_LOW_POWER_RTI */
  \endcode
  - Do not forget to add the RTI interrupt to the vector table
  - You will need to start the RTI timer. Check the GB/GT60 CPU manual for details around the RTI.
    The following piece of code starts the RTI timer with a 1024 ms period.
\code
  setReg8(SRTISC, 0x17); /* Run RTI for 1024 ms (select clock source, set frequency and enable interrupt ) */    
\endcode  
  - Do not forget the impact of an active debug connection to STOP modes
  - Measure the power consumption in STOP3 mode
  - Verify that your debouncing is still working properly
- Test the functionality
- Have fun :-)  

\section s_journal Journal Questions
- Document your measurement as indicated in the Hints section
- Make a measurement both the current with batteries and an external power supply.
  Why is the current measured on the jumper for barrel (external power supply) and for batteries different?
- Use an Excel graph to visualize your measurements
- One way to suppress the LED's for measurement is to have a switch in your code to disable the 
  heartbeat LED with a macro like PL_UI_HAS_1S_LED_HEARTBEAT. What alternative approach could you use with your board?
\code
#define PL_UI_HAS_1S_LED_HEARTBEAT  0   /*!< Set to 1 if we have an LED 1s hearbeat */
\endcode  
- Why is it important to measure the voltage (and not only the current) for power measurement?
- What would you need to do in order to implement STOP2 mode? What would be the difficulties?
- Based on the battery capacity on the board and your measurement:
  make a rough calculation how long the board is able to run in your lowest power consumption mode.
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_LowPowerFreq Lab: Low Power Frequency
\date 12-Apr-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- Support following platforms
  - Trainer
  - SRB Board
  - DEMOGB60 Axiom Board
- The existing functionality shall be preserved (switches, debouncing and LED's)
- Reduce the power consumption as much as you can. Goal is below 1.5 mA. Measure it.
- Still, your shall use debouncing for the keys and light up the LED's for the key press.

\section s_hardware Hardware
- HCS08GB60 & HCS08GT60
- Infotronic base platform
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
- MC13213 SRB: refer to the board documentation
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA2
   - SW1: PTA3
   - SW2: PTA4
   - SW3: PTA5
- DEMOGB60 Axiom board
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7

\section s_hints Hints
- You received two new modules as base for your implementation (LowPower.h and LowPower.c).
  Integrate them into your CodeWarrior project and make yourself familiar with the implementation.
- ::LP_ICGTable is implementing a table with different speed mode settings.
  Make sure you have set up a matching configuration for your board.
- Create a define to indicate your new upcoming capabilities in platform.h.
  The first one tells that the system has the ability to change the frequency,
  and the second one tells that we can change the frequency using the keyboard:
\code
  #define PL_HAS_LOW_POWER_FREQ   1   /*!< Set to 1 if we enable low power support with frequency change */
  #define PL_UI_KBD_LOW_POWER         (1 & PL_HAS_KBD & PL_HAS_LOW_POWER_FREQ)  /*!< Set to 1 if keyboard is used to set bus frequency for low power */
\endcode
- As changing the bus clock is changing the timers, you need to inform the timer about the change.
  So you will need to add (and use) a new interface in timer.h:
\code
/*!
 \brief Informs the timer about a speed change. This function is called by the platform module.
 @param[in] speed New speed
 */
void TMR_ChangeSpeed(LP_Speed speed);
\endcode  
- Below is a piece of code you may use in your timer.c as the implementation of it.
  Based on your timer implementation, you may need to adopt it.
\code
/* ----------------- Change of Frequency --------------------------------------*/
#if PL_HAS_LOW_POWER_FREQ

void TMR_ChangeSpeed(LP_Speed speed) {
  clrReg8Bits(TPM1SC, 0x18);  /* Stop TPM1 counter (CLKSB:CLKSA = 00) */ 
  setReg8(TPM1CNTH, 0x00);    /* Clear counter register */ 

  /* set new prescaler and compare values */
  TMR_10ms_SetCV(LP_Get10msTimerCompareValue(speed)); /* Set Compare/modulo register value */
  /* now set clock select and prescaler, this will run the counter again */
  setReg8(TPM1SC, LP_Get10msTimerPrescalerValue(speed)); /* prescaler */

  clrSetReg8Bits(TPM1SC, 0x10, 0x08); /* run counter: CLKSA=0, CLKSA=1 */
}

#endif /* PL_HAS_LOW_FREQ */
\endcode
- You need to add additional code in EVNT_HandleEvents() in order to increase/decrease the frequency (button handling)
- Now it is time to verify if your timer (e.g. through the 1 s heartbeat) is still working with your changes
- If you change now the speed, your heartbeat shall still be in a 1 second interval
- Test the functionality
- Have fun :-)  

\section s_journal Journal Questions
- Changing the bus clock speed means as well to change the timer prescaler for the 
  10 ms timer using TMR_ChangeSpeed(). What is needed to change the RTI timer we used
  in previous lab work to operate properly as well with a changed clock frequency?
- Document in your work book your measurement for different speed values
  - ~250 KHz up to ~20 MHz
  - measure both a setup with external clock and with internal clock
  - normalize the two measurement rows in order to compare them
- Do the current measured match with your expectations? Why? (or why not ;-) ?
- The MC9S08GB60_Ref2.3.pdf Data Sheet manual for the GB60 lists in Appendix A
  Electrical Characteristics, page 266) in Figure A-6 the typical Run Idd for FBE and FEE
  Modes: why is making using FEE vs FBE a difference?
- In the same figure A-6, the curves are making a change around 2.6V. What could be the reason for this?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_LCD Lab: LCD
\date 12-Apr-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- The goal is to attach an LCD display to our platform and use it for displaying text.
- Write a nice welcome message to the LCD
- Show on the display which key has been pressed (SW0, SW1, SW2, SW3 for short key press)
- Show as well long key presses (SWL0, SWL1, SWL2, SWL3)
- Show the current frequency of the CPU

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- 3.3V LCD display (lcd.c, lcd.h)
  - Data bus: PORTC pins 0 to 7
  - RS      : PORTB.PB0
  - R_W     : PORTB.PB1
  - EN      : PORTB.PB2

\section s_hints Hints
- The display is using a Hitachi HD44780 compatible controller (on the display).
  On ILIAS there is the data sheet for this controller.
- See the LCD driver documentation and header files how to use the driver
- Use ::PL_HAS_LCD to guard your code for having LCD support
- Follwing is a routine which allows you (based on your clock settings) to wait for a
  specific time (busy waiting). You may use this function in your work.
\code
/* Using pragmas to disable entry/exit code to have complete control */
#pragma NO_ENTRY
#pragma NO_EXIT
static void TMR_WaitCycles100(void) {
  /* This function shall spend exactly 100 CPU cycles (including call overhead). */
  asm {
      /* BSR to here  ; [5] */
      PSHH            ; [2], reserve space on stack
      LDA #13         ; [2], n
      TSX             ; [2]
      STA 0,X         ; [2]
    Label:
      DBNZ X,Label    ; 13*[6] =[78]
      PULH            ; [3]
      RTS             ; [6]
  }
}

void TMR_BusyWaitMs(unsigned int ms) {
  /* busy waiting for a period of time */
  unsigned char i;
  
  while (ms != 0){
    ms--;
    for (i=0; i<=PL_CurrentNof100KHz(); i++) { /* wait 1000 cycles @ 1MHz => 1 ms */
      TMR_WaitCycles100();
    }
  }
}
\endcode
- Generate a nice welcome message on the LCD after program start.
  You can use the ::EVNT_INIT event.
- Display if you have a long or short key press detected, and for which key.
  It is recommended that you guard your new functionality with ::PL_UI_LCD_KBD
  to indicate that you have a user interface showing the key status on the LCD
- In order to use the LCD as UI for showing the CPU clock, it will be a good idea 
  to guard the functionality using a ::PL_UI_LCD_SHOW_MHZ define
  (to indicate that we are using the LCD as UI to display the MHz)
- Display the current clock speed on the LCD (re-use your work from previous lab).
  A recommended way to do this is to create an additional event ::EVNT_LCD_SHOW_MHZ
  and to react on this event in the event handler.
- Have fun :-)

\section s_journal Journal Questions
- If you have to use this LCD in a low power environment: what would you do in order to minimize power consumption?
- Measure the current used for the LCD: verify your ideas you had in previous question.
- The HD44780 data sheet lists at the end (page 58ff) the timing of the protocol.
  How is the timing implemented in the driver you received?
  Is there an opportunity to improve this? How?
- How sensitive is the LCD driver to microcontroller speed changes?
  Could the driver as it is be used for a high speed CPU (say > 20 MHz?)
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_PWM Lab: PWM
\date 16-Apr-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
- The goal is drive the DC motor using a PWM signal.
- To change the direction, a dedicated pin signal (DIR) shall be used.
- As user interface we use the Visualization Tool in the debugger.
- If you want, you could use the keys/LCD as user interface instead of the debugger visualization tool.

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- 3.3V LCD display (lcd.c, lcd.h)
  - Data bus: PORTC pins 0 to 7
  - RS      : PORTB.PB0
  - R_W     : PORTB.PB1
  - EN      : PORTB.PB2
- Infotronic DC motor (motor.c, motor.h)
  - C1: PTA1
  - C2: PTA0
  - DIR: PTD6
  - PWM: PTD7

\section s_hints Hints
- Make sure the jumper for the RS232 driver IC on the board is installed
- Connect the motor with the board
- There are a few additional platform defines to configure your setup:
\code
  #define PL_HAS_MOTOR    1                   /*!< Set to 1 if platform has DC motor */
  #define PL_UI_VT_MOTOR  (1 & PL_HAS_MOTOR)  /*!< Set to 1 if debugger visualization tools (VT) is used to manage the motor */
  #define PL_UI_LCD_MOTOR (1 & PL_HAS_LCD & PL_HAS_MOTOR)           /*!< Set to 1 if LCD shall show the status of the motor */
\endcode
- The driver for the PWM is provided in PWM.c and PWM.h. Integrate them into your project.
- The PWM driver requires an additional interrupt set up in vector.c:
\code
#if PL_HAS_MOTOR
         PWM_Interrupt,       /* Int.no. 14 Vtpm2ovf (at FFE2)   */
#else
         Dummy_Interrupt14,   /* Int.no. 14 Vtpm2ovf (at FFE2)   */
#endif
\endcode
- An initial motor driver is provided with motor.c and motor.h
- In order to have the system report values on the Visualization tool, we add an additional trigger:
\code
#if PL_UI_VT_MOTOR
  #define TRG_TRIGGER_VISUALIZATION 2  /*!< Get data from debugger visulization tool */
#endif
#if PL_UI_LCD_MOTOR
  #define TRG_MOTOR_LCD_DISPLAY 3  /*!< Display Motor status on LCD */
#endif
\endcode
- Additionally we need to add a new event:
\code
#if PL_UI_LCD_MOTOR
  #define EVNT_LCD_SHOW_MOTOR   (1<<10) /*!< Show motor status on LCD */
#endif /* PL_UI_LCD_MOTOR */
\endcode
- You may copy-paste the following Visualization Tool instruments into the Visualization tool:
  Select the text below and past it (in edit mode) into your Debug Visualization Tool window. 
\code
LoadInstrument Text[BoundX="33",BoundY="14",BoundH="90",BoundW="274",colBkgnd="T13160660",FName=""]
LoadInstrument Bar[BoundX="142",BoundY="30",BoundW="136",Port_PortKind="2",Port="Motor_UsrPWM",RangeHigh="65535"]
LoadInstrument Text[BoundX="75",BoundY="30",BoundW="64",swBBox="0",FName="User PWM: "]
LoadInstrument Switch[BoundX="143",BoundY="53",Port_PortKind="2",Port="Motor_UsrDirection"]
LoadInstrument Text[BoundX="73",BoundY="48",BoundW="64",swBBox="0",FName="User DIR: "]
LoadInstrument Text[BoundX="22",BoundY="23",BoundW="37",swBBox="0",FName="User"]
LoadInstrument Switch[BoundX="20",BoundY="39",Port_PortKind="2",Port="Motor_UsrOn"]
\endcode
- Using the Visualization Tool GU interface, verify that you can control speed and direction of the motor.
- Check if your code is working with increased/decreased speed
- Have fun :-)

\section s_journal Journal Questions
- What is the maximum speed of the motor?
- Why may the motor start running while downloading/programming the flash?
- You can use the visualization tool in the debugger to get some visibility into the target.
  What are the pros and cons? What would be the advantage using the keyboard/LCD instead?
*/
/*----------------------------------------------------------------------------------------------------*/
/*!
\page page_Quad Lab: Quadrature
\date 27-Apr-2009
\author Erich Styger, erich.styger@hslu.ch

\section s_requirement Requirements
Following functionality shall be supported:
- Decoding speed signal provided by quadratic decoder
- Show on the LCD
  - The current position
  - The current speed (RPM)

\section s_hardware Hardware
- HCS08GB60
- Infotronic base platform
  - Keyboard (keyboard.c, keyboard.h)
   - SW0: PTA4
   - SW1: PTA5
   - SW2: PTA6
   - SW3: PTA7
  - LED (LED.c, LED.h)
    - LED0: PTF0
    - LED1: PTF1
    - LED2: PTF2
    - LED3: PTF3
- 3.3V LCD display (lcd.c, lcd.h)
  - Data bus: PORTC pins 0 to 7
  - RS      : PORTB.PB0
  - R_W     : PORTB.PB1
  - EN      : PORTB.PB2
- Infotronic DC motor (motor.c, motor.h)
  - C1: PTA1
  - C2: PTA0
  - DIR: PTD6
  - PWM: PTD7

\section s_hints Hints
- For simplicity: run you target with internal clock and maximum speed (you will need the processing power)
- The template includes an updated version of LowPower.c and LowPower.h which handles the additional Quadrature decoding timer
- The template includes an updated version of vector.c which incorporates TMR_Quadrature_Interrupt()
- The template comes with a utility module (utility.c and utility.h) with some routines which may be useful for you.
- Here is a template for the Visualization Tool:
\code
LoadInstrument Switch[BoundX="10",BoundY="154",Port_PortKind="2",Port="input_ab",kind="2"]
LoadInstrument Text[BoundX="10",BoundY="197",BoundW="37",swHAlig="1",FName="ab"]
LoadInstrument LED[BoundX="18",BoundY="227",BoundH="41",BoundW="44",Port_PortKind="2",Port="_PTFD.Byte",colON="T65280"]
LoadInstrument LED[BoundX="64",BoundY="227",BoundH="40",BoundW="38",Port_PortKind="2",Port="_PTFD.Byte",swBIT="1",colON="T65280"]
LoadInstrument LED[BoundX="103",BoundY="226",BoundH="41",BoundW="42",Port_PortKind="2",Port="_PTFD.Byte",swBIT="2",colON="T65280"]
LoadInstrument LED[BoundX="146",BoundY="225",BoundH="41",BoundW="44",Port_PortKind="2",Port="_PTFD.Byte",swBIT="3",colON="T65280"]
LoadInstrument Text[BoundX="33",BoundY="14",BoundH="90",BoundW="274",colBkgnd="T13160660",FName=""]
LoadInstrument Bar[BoundX="142",BoundY="30",BoundW="136",Port_PortKind="2",Port="Motor_UsrPWM",RangeHigh="65535"]
LoadInstrument Text[BoundX="75",BoundY="30",BoundW="64",swBBox="0",FName="User PWM: "]
LoadInstrument Switch[BoundX="143",BoundY="53",Port_PortKind="2",Port="Motor_UsrDirection"]
LoadInstrument Text[BoundX="73",BoundY="48",BoundW="64",swBBox="0",FName="User DIR: "]
LoadInstrument Text[BoundX="22",BoundY="23",BoundW="37",swBBox="0",FName="User"]
LoadInstrument Switch[BoundX="20",BoundY="39",Port_PortKind="2",Port="Motor_UsrOn"]
LoadInstrument ValueText[BoundX="132",BoundY="124",BoundW="115",Port_PortKind="2",Port="Motor_currPos",Port_PortSize="1",FName="Pos: ",swFormat="0"]
LoadInstrument Chart[BoundX="285",BoundY="143",BoundH="328",BoundW="365",Port_PortKind="2",Port="Motor_currRPM",RangeHigh="2500",RangeLow="-1000"]
\endcode
- MOTOR_UpdateLCD() is used to update the LCD periodically about the status.
  Make sure you handle ::EVNT_LCD_SHOW_MOTOR in EVNT_HandleEvents() and display there the current RPM/speed.
  Motor.h provides an interface to get the position and the RPM value.
- Complete the quadrature decoding tables (::Motor_Quad_Table)
- Verify ::MOTOR_NOF_ROUND_PULSE and ::MOTOR_SPEED_CALC_PERIOD if they match your hardware and setup 
- Make sure get the C1 and C2 signals correctly.
- Have fun :-)

\section s_journal Journal Questions
- The utility.c implements a function UTIL_strcpy(). Why not using the normal strcopy() provided by the ANSI library? 
- Check the encoder data sheet and the motor data sheet:
  calculate the signal rate with maximum speed and the used encoder and document it
- See http://en.wikipedia.org/wiki/Nyquist%E2%80%93Shannon_sampling_theorem:
  you will need to sample the signal twice as fast as the max signal frequency: what is your required sampling frequency?
- Is there a good reason why the C1 and C2 signals are on bit 0 and bit 1 of the port?
  What would be the impact if they would be on other bits?
- The reported speed (RPM) may jump back and forward some values. Why? What could be done to improve this?
- It may be that somethimes you will get errors while sampling the signals. Why? What can you do about it?
- Compare the decoder with error correction and the one without.
  At which speed the one without error correction will start producing errors?
  At which speed the one with error correction starts producing errors?
  Why is that?

*/


