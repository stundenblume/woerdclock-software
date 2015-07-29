/* 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Dieses Programm ist Freie Software: Sie k�nnen es unter den Bedingungen
der GNU General Public License, wie von der Free Software Foundation,
Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.

Dieses Programm wird in der Hoffnung, dass es n�tzlich sein wird, aber
OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
Siehe die GNU General Public License f�r weitere Details.

Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>. 

Menue mod:
no jumper is set; after the selftest the button must be push (start with 1-3), ever Button is show with the minute LED;
after all button are calibrate the value of the button are show as a bitvalue;
next step is time adjust with the buttons 1 and 2 (h and m); After a short time the LEDs go off
the jumper is set and the default mode start (normally Clockmod)

Chance mod:
no jumper is set; push the ok button; with the h- and m-button chance the mod the LED show the mod; do nothing and after 5s chance mod exit   

*/

//Which Modules are installed?
#define CONFIGBUTTON 0 //Config Buttons and adjust Time, SET CONFIGBUTTON or BUTTON 
#define RTCLOCK 1     //Module Real Time Clock
#define BUTTON 1      //Button are used  SET CONFIGBUTTON or BUTTON 
#define LDR 1         //LDR is used
#define GENSERIAL 0    //Gen Serial
#define BLUETOOTH0 0   //Module Bluetooth, via pin 0,1 - default=0, because on this port is the led stripe connected
#define USBPORT0 0     // Serial Communication across usb
#define BLUETOOTH1 0   //Module Bluetooth 1
#define BLUETOOTH2 0   //Module Bluetooth 2
#define WLAN 0         //Module WLAN
#define DOF 0          //Module 10DOF
#define DCFMODUL 1     //Module DCF77
#define SDCARD 0       //Module SD Card
#define MIC 0          //Module Microfon
#define IRRESV 0         //Module IR
#define DHT11 1        //Module DHT11
#define RFM12 0        //Module RMF12B
#define TEXT 0        //Show Massage Board 
#define TEXT2 1        //Show Text
#define RUNDECLOCK 0   //added 2 Minutes to time


//Debug Mode or not (uncommand)
#define DEBUG 1
//****************************LED Config************************
//Library includes
#include <Time.h>
#include <FastLED.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>


//#if ARDUINO >= 100
//#include <Arduino.h> 
//#else
//#include <WProgram.h> 
//#endif

//LED defines
#define NUM_LEDS 114
#define ANIMLEDS 100    //LED for Animation 
static byte heatanim[ANIMLEDS];
#define FRAMES_PER_SECOND 60
#define COOLING  55
#define SPARKING 80
long BAUDRATE = 57600; // default Baudrate for serial communication
 
//PIN defines
#define STRIP_DATA_PIN 8

//LED varables
uint8_t strip[NUM_LEDS];    //Array for the aktiv LEDs
uint8_t stackptr = 0;       //Variable for the next LED to set
CRGB leds[NUM_LEDS];        //LED Array for FASTLED
//Clock variables
  long waitUntilClock = 0;    //Variable Delay for ClockLogic
  byte ye=0, mo=0, da=0, h=4, m=4, s=4; //Variables to adjust the Clock 
  int testHours = 0;        //Variables change time? minute or hour?
  int testMinutes = 0;
  
  time_t time;
//***************************RTC Config Library************************
#if RTCLOCK
  #include "RTClib.h"    //Lib for RTC
  RTC_DS1307 RTC;        //TYP of RTC
 //RTC variables
  boolean RTCpresent=false;
  //unsigned long lastSecond;
#endif

//****************************Button Config**********************
#if CONFIGBUTTON
  
  #define ANALOGPIN A6         //Analogpin for Button and LDR
  //Button variables
  //#define CHARSHOWTIME 600     //
  #define AUTOENDTIME 5000       //Time for Funktion 
  #define TIMEEXTENSION 10000    //Time for Funktion ButtonCali 
  #define TOLLERANCE 10          //Tollerance for the ButtonsValue
  
  boolean menue=false,debugmod=true, modus=false;    //Modi for the Config
  int uButtonValue=1,dButtonValue=2,okButtonValue=4; //Variable for the ButtonValue
#endif

//****************************Button ****************************
#if BUTTON 
  #define ANALOGPIN A6              //Analogpin for Button and LDR
  //Button variables
  #define AUTOENDTIME 5000          //Time for Funktion
  #define TOLLERANCE 10             //Tollerance for the ButtonsValue
  boolean modus=false;              //Modi for the Config
  int uButtonValue=1,dButtonValue=2,okButtonValue=4;//Variable for the ButtonValue
#endif
//****************************LDR Config************************
#if LDR
  #define ANALOGPIN A6              //Analogpin for Button and LDR
  long waitUntilLDR = 0;            // for LDR
#endif
//****************************Serial Config******************
#if GENSERIAL
 #include <SoftwareSerial.h>
 byte serial_com_port = 255; // A number to seperate the ports for serial communication from each other
 boolean showvalues = false; // For debugging only
 boolean LED[NUM_LEDS] = {0};// this is a dummy array for the LEDs of wordclock 0=off, 1=on
 long timestamp = 0;  // this is a dummy variable for the date and time in unix time stamp format (see http://playground.arduino.cc/Code/Time )
 long timestampold = 0;//this is variable for the old dummy
 /* Start command definitions for serial communication - don't touch this 
    based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz */
/*
  paraCount defines the maximum number of command and parameters
  paraLength defines the maximum length for commands and parameters (paraLength = max command/parameter length +1)
  cmdCount defines the number of entities
  cmdStrCon defines the commands in lower case!!
*/
const byte  paraCount = 5;                            // max quantity of parameter (incl. command) per line    slc = NR,r,g,b
const byte  paraLength = 11;                           // max length per parameter/command (-1)                 help,show
const byte  cmdCount = 17;                            // quantity of possible commands                        show to slcp
const char cmdStrCon[cmdCount][paraLength]=
{
  {
    "show"  }
  ,{
    "help"  }
  ,{
    "slb"  }
  ,{
    "glb"  }
  ,{
    "slbp"  }
  ,{
    "glbp"  }
  ,{
    "slc"  }
  ,{
    "glc"  }
  ,{
    "slcp"  }
  ,{
    "glcp"  }
  ,{
    "sled" }
  ,{
    "gled" }
  ,{
    "srtc" }
  ,{
    "gtem" }
  ,{  
    "ghum"}
  ,{
    "smod"}
  ,{
    "gmod"}
};
char       cmdStr[paraCount*paraLength+paraCount+1]; //buffer for complete line of comand and parameter
int        cmdStrIn=0;                               //index for the cmdStr 
char       cmd[paraCount][paraLength];               //arry with command and parameters
/* End command definitons for serial communication - don't touch this */

  #if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
  
    /* Welcome + help text */
    const char strwelcome[]  = "\nWelcome to WördClock Controller Interface  \n\r version 0.8";
    /*
    const char strhelp1[] = 
    "\n Possible commands are:"
    "\n\r help           help text"
    "\n\r slb=0-255       set led brightness 0-255"
    "\n\r glb            get led brightness"
    "\n\r slbp           store led brightness permanent"
    "\n\r glbp           get permanent led brightness"
    "\n\r slc=R,G,B      set led color (R,G,B) (0-255)"
    "\n\r glc            get led color";
    
    const char strhelp2[] =
    "\n\r slcp           store led color permanent"
    "\n\r glcp           get permanent led color"
    "\n\r sled=No,R,G,B set led by number with RGB color code"
    "\n\r srtc           set unix time stamp for clock"
    "\n\r grtc           get unix time stamp and time from clock";
  
    const char strhelp3[] =
    "\n\r gtem           get temperature"
    "\n\r ghum           get humidity"
    "\n\r smode          set the mode";
    "\n\r gmode          get the mode\n";
    */
    const char strerror2[] = "error";
    const char paramseperator = ',';
    const char cmdbreak = '\n';
  #endif
#endif
//****************************Bluetooth1 Config******************
#if BLUETOOTH1
 SoftwareSerial BTSerial(8, 9); // Connect Arduino Micro pin 19 with HC-06 pin RX and Arduino Micro pin 18 with HC-06 pin TX
#endif
//****************************Bluetooth2 Config******************
#if BLUETOOTH2
  SoftwareSerial BTSerial2(10, 11); // Connect Arduino Micro pin 20 with HC-06 pin RX and Arduino Micro pin 21 with HC-06 pin TX
#endif
//****************************WLAN Config************************
#if WLAN

#endif
//****************************10DOF Config***********************
#if DOF

#endif
//****************************DCF Config************************
#if DCFMODUL

 
  
  #define DCF_PIN 7	          // Connection pin to DCF 77 device
  
  #define MIN_TIME 1334102400     // Date: 11-4-2012
  #define MAX_TIME 4102444800     // Date:  1-1-2100
  
  #define DCFRejectionTime 700	  // Pulse-to-Pulse rejection time. 
  #define DCFRejectPulseWidth 50  // Minimal pulse width
  #define DCFSplitTime 180	  // Specifications distinguishes pulse width 100 ms and 200 ms. In practice we see 130 ms and 230
  #define DCFSyncTime 1500	  // Specifications defines 2000 ms pulse for end of sequence
  
  bool initialized;
  static byte pulseStart=HIGH;
  
  
  // DCF77 and internal timestamps
  static time_t previousUpdatedTime;
  static time_t latestupdatedTime;           	
  static time_t processingTimestamp;
  static time_t previousProcessingTimestamp;		
  static unsigned char CEST;
  
  // DCF time format structure
	struct DCF77Buffer {
	  //unsigned long long prefix		:21;
	  unsigned long long prefix		:17;
	  unsigned long long CEST		:1; // CEST 
	  unsigned long long CET		:1; // CET 
	  unsigned long long unused		:2; // unused bits
	  unsigned long long Min		:7;	// minutes
	  unsigned long long P1			:1;	// parity minutes
	  unsigned long long Hour		:6;	// hours
	  unsigned long long P2			:1;	// parity hours
	  unsigned long long Day		:6;	// day
	  unsigned long long Weekday	:3;	// day of week
	  unsigned long long Month		:5;	// month
	  unsigned long long Year		:8;	// year (5 -> 2005)
	  unsigned long long P3			:1;	// parity
	};
  
  // DCF Parity format structure
	struct ParityFlags{
		unsigned char parityFlag	:1;
		unsigned char parityMin		:1;
		unsigned char parityHour	:1;
		unsigned char parityDate	:1;
	} static flags;

// Parameters shared between interupt loop and main loop
        static volatile int test;
	static volatile bool FilledBufferAvailable;
	static volatile unsigned long long filledBuffer;
	static volatile time_t filledTimestamp;

	// DCF Buffers and indicators
	static int  bufferPosition;
	static unsigned long long runningBuffer;
	static unsigned long long processingBuffer;

	// Pulse flanks
	static   int leadingEdge;
	static   int trailingEdge;
	static   int PreviousLeadingEdge;
	static   bool Up;
  
  

#endif
//****************************SD Config*************************
#if SDCARD

#endif
//****************************Mic Config************************
#if MIC
    #define MIC_PIN A5                                            // Analog port for microphone
    #define DC_OFFSET  32                                         // DC offset in mic signal - if unusure, leave 0
    #define NOISE     100                                         // Noise/hum/interference in mic signal and increased value until it went quiet
    #define SAMPLES   60                                          // Length of buffer for dynamic level adjustment
    #define TOP (NUM_LEDS + 2)                                    // Allow dot to go slightly off scale
    #define PEAK_FALL 40                                          // Rate of peak falling dot
    
    byte
    peak      = 0,                                              // Used for falling dot
    dotCount  = 0,                                              // Frame counter for delaying dot-falling speed
    volCount  = 0;                                              // Frame counter for storing past volume data
    int
    vol[SAMPLES],                                               // Collection of prior volume samples
    lvl       = 10,                                             // Current "dampened" audio level
    minLvlAvg = 0,                                              // For dynamic adjustment of graph low & high
    maxLvlAvg = 512;
#endif
//****************************IR Config*************************
//#if IRRESV
//  #include <IRremote.h>
//  // IR defines
//  ////Modus variables
//  #define ONOFF 0
//  #define FAST  1
//  #define DISCO 2
//  #define ANIM  3
//  #define CLOCK 4
//  
//  //#define ONOFF 0xFF02FD
//  #define AUTO 0xFFF00F
//  #define BLUE_DOWN 0xFF48B7
//  #define BLUE_UP 0xFF6897
//  #define BRIGHTER 0xFF3AC5
//  #define DIM 0xFFBA45
//  #define DIY1 0xFF30CF
//  #define DIY2 0xFFB04F
//  #define DIY3 0xFF708F
//  #define DIY4 0xFF10EF
//  #define DIY5 0xFF906F
//  #define DIY6 0xFF50AF
//  #define FLASH 0xFFD02F
//  #define QUICK 0xFFE817
//  #define SLOW 0xFFC837
//  
//  #define IR_RECV_PIN 6
//  
//  //IR variables
//  IRrecv irrecv = IRrecv(IR_RECV_PIN);
//  decode_results irDecodeResults;
//#endif
//****************************DHT11 Config**********************
#if DHT11
  #include "DHT.h"
  #define DHTPIN 6   
  #define DHTTYPE DHT11 
  DHT dht(DHTPIN, DHTTYPE);

  int humi = 0;
  int temp = 0;
  
//  int temperatur = 22;
  //int DHT_TIMER = 0;
 
long waitUntilwriteChar = 0;
long waitUntilDHT = 0;
const long dhtDelay = 30000;     //delay for show temp and humidity  
#endif

#if TEXT

  //arrays for the char  
const boolean arrayA [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayB [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
const boolean arrayC [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayD [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayE [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayF [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayG [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
const boolean arrayH [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayI [6][10] =  {{0,0,0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayJ [6][10] =  {{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayK [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,1,0,1,0,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
const boolean arrayL [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayM [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayN [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
const boolean arrayO [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayP [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayQ [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayR [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,1,0,0,0,0,0},{0,1,1,1,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};          
 //const boolean arrayS [6][10] =  {{0,1,1,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
 //const boolean arrayT [6][10] =  {{0,1,0,0,0,0,0,0,0,0},{0,1,1,1,1,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayU [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayV [6][10] =  {{0,1,1,0,0,0,0,0,0,0},{0,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,0},{0,0,0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayW [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayX [6][10] =  {{0,1,0,0,0,0,1,0,0,0},{0,0,1,0,1,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,1,0,1,0,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //const boolean arrayY [6][10] =  {{0,1,0,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};            
 //const boolean arrayZ [6][10] =  {{0,1,0,0,0,1,0,0,0,0},{0,1,1,0,0,1,0,0,0,0},{0,0,1,1,0,1,0,0,0,0},{0,1,0,0,1,1,0,0,0,0},{0,1,0,0,0,6,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};           
 //const boolean array_ [6][10] =  {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
const boolean arrayp [6][10] = {{0,0,1,1,0,0,1,0,0,0},{0,0,1,1,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,1,0,1,1,0,0,0},{0,0,1,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}}; 
const boolean array1 [6][10] =  {{0,0,0,1,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};            
const boolean array2 [6][10] =  {{0,0,1,0,0,0,1,1,0,0},{0,1,0,0,0,1,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,1,0,0,0,1,0,0},{0,0,1,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,0,0}};             
const boolean array3 [6][10] =  {{0,0,1,0,0,0,1,0,0,0},{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
const boolean array4 [6][10] =  {{0,1,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,1,1,1,1,1,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
const boolean array5 [6][10] =  {{0,1,1,0,0,0,7,0,0,0},{0,1,0,1,0,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,0,1,0,1,0,0},{0,0,1,0,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,0,0}};           
const boolean array6 [6][10] =  {{0,0,1,1,1,1,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
const boolean array7 [6][10] =  {{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,0,1,1,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,1,0,0,0,0,0},{0,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
const boolean array8 [6][10] =  {{0,0,1,1,1,1,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};        
const boolean array9 [6][10] =  {{0,0,1,1,0,0,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};            
const boolean array0 [6][10] =  {{0,0,1,1,1,1,1,0,0,0},{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,0,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
#endif
//**************************************************************
#if TEXT2
byte startrow = 0;

const char array1 [5] =  {
B00000100,
B00000100,
B00000100,
B00000100,
B00000100
};
const char array2 [5] =  {
B00001111,
B00000001,
B00001111,
B00001000,
B00001111
};             
const char array3 [5] =  {
B00001111,
B00000001,
B00000111,
B00000001,
B00001111
};
const char array4 [5] =  {
B00001000,
B00001010,
B00001111,
B00000010,
B00000010
};             
const char array5 [5] =  {
B00001111,
B00001000,
B00001111,
B00000001,
B00001111
};           
const char array6 [5] =  {
B00001111,
B00001000,
B00001111,
B00001001,
B00001111
};             
const char array7 [5] =  {
B00001111,
B00000001,
B00000001,
B00000001,
B00000001
};             
const char array8 [5] =  {
B00001111,
B00001001,
B00001111,
B00001001,
B00001111
};        
const char array9 [5] =  {
B00001111,
B00001001,
B00001111,
B00000001,
B00001111
};            
const char array0 [5] =  {
B00001111,
B00001001,
B00001001,
B00001001,
B00001111
};

#endif
//****************************RFM12 Config**********************
#if RFM12
  #include <RF12.h>
  //#include <util/crc16.h>
  //#include <util/parity.h>
  #include <avr/eeprom.h>
#endif

//****************************Default Config********************
//Display Mode at start
int displayMode = 4;        //Clock with Color Change is default Modus
//Default Color?
CRGB defaultColor = CRGB::Blue; //White, Red, Green, Blue, Yellow
byte LEDbright = EEPROM.read(4); // this is a dummy variable for the LED brightness
byte LEDcolorR = EEPROM.read(5); // this is a dummy variable for the LED color red
byte LEDcolorG = EEPROM.read(6); // this is a dummy variable for the LED color green
byte LEDcolorB = EEPROM.read(7); // this is a dummy variable for the LED color blue
uint8_t colorIndex = 0;
boolean autoBrightnessEnabled = true;    //true and the LDR is aktiv or false and the LDR is not aktiv (its the same as no LDR
byte brightness = 50;                    //default brightness without LDR

//multitasking helper
const long oneSecondDelay = 1000;
const long halfSecondDelay = 500;


long waitUntilOff = 0;

//Marker to find out the correct Modus or refresh states
boolean dhtaktion = false;       //dht in aktion marker
boolean colorchange = false;     //Color Change over Serial
boolean clockaktion = true;    //Clock in aktion marker

//****************************Debug Config**********************
#if DEBUG
	#define DEBUG_PRINT(str)  Serial.println (str)
#else
	#define DEBUG_PRINT(str)
#endif
//****************************Setup*************************************************************************************************************
//##############################################################################################################################################
//**********************************************************************************************************************************************
void setup() {
	
	#ifdef DEBUG
		Serial.begin(BAUDRATE);
	#endif
	
	
//****************Setup LED Matrix*******************
        //pinMode(ARDUINO_LED, OUTPUT);
	
	for(int i = 0; i<NUM_LEDS; i++) {
		strip[i] = 0;
	}
	FastLED.addLeds<WS2812B, STRIP_DATA_PIN, GRB>(leds, NUM_LEDS);
	resetAndBlack();
	displayStrip();

//***************Setup RTC***************************
    #if RTCLOCK        
        DateTime now = RTC.now();
        Wire.begin();
        RTC.begin();
        if (RTC.isrunning()) {
          //RTCpresent = true;
          DateTime now = RTC.now();
          ye=now.year();
          mo=now.month();
          da=now.day();
          h=now.hour();
          m=now.minute();
          s=now.second();     
        }
        else{
        // following line sets the RTC to the date & time this sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
        DEBUG_PRINT("No RTC");
        }	
    #endif
//***************Setup BUTTON CONFIG***************************
     #if CONFIGBUTTON
        if(analogRead(ANALOGPIN)<10) menue = true;        //Menue start with Jumper
      
        selftest(100); // test all LEDs and write "HALLO"                  
     
        if (menue && analogRead(ANALOGPIN)>10) {          //Debug start with Jumper set after selftest, nothing to debug!
          debugmod=true;
          menue=false;
          resetAndBlack();
	  pushToStrip(1);
          pushToStrip(2);
          displayStrip(CRGB::Blue);
          
        }
        if (!menue && !debugmod){                        //No debug no menue, normal start
            resetAndBlack();
	    pushToStrip(3);
            pushToStrip(1);
            displayStrip(CRGB::Green);

        }
     
        boolean calibOK = alreadyCalibrated();           // Check if there is was already a calibration of the buttons 
        if (!calibOK || menue) buttonCalibration();      // if there wasn't already a calibration OR jumper is open, do the calibration
        if (menue && calibOK) adjustTime(); // if the jumper ist open AND the there is al calibration for the buttonValus, go to adjust the time
     #endif

//***************Setup BUTTON***************************
     #if BUTTON     
        selftest(100);                                   // test all LEDs and write "HALLO" 
        boolean calibOK = alreadyCalibrated();           // Check if there is was already a calibration of the buttons         
        if (!calibOK){                                  
        DEBUG_PRINT(F("Button not calibrated"));
        }
     #endif

//***************setup DCF*****************************
    #if DCFMODUL
        pinMode(DCF_PIN, INPUT);
        initializeDCF();
        StartDCF();
    #endif
//***************setup ir******************************
//    #if IRRESV	
//      irrecv.enableIRIn();
//    #endif
//***************setup Bluetooth WLAN ********************** 
#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
  /* You need this in your setup for serial communication */
  for(int i=0; i++; i<paraCount)
  {
    cmd[i][0]='\0';
  }
  
  #if USBPORT0
  Serial.begin(BAUDRATE);       // initialize serial port for usb
  #endif
  
  #if BLUETOOTH0

  #endif
  
  #if BLUETOOTH1
  BTSerial.begin(BAUDRATE);     // initialize Software Serial port for bluetooth
  #endif
  
  #if BLUETOOTH2
  BTSerial2.begin(BAUDRATE);    // initialize a second Software Serial port for bluetooth
  #endif 
  /* You need this in your setup  for serial communication */
#endif

//***************setup SD*******************************
    #if SDCARD

    #endif
//***************setup DHT11****************************
    #if DHT11
        dht.begin();
    #endif   
//***************setup 10DOF****************************
    #if DOF

    #endif
//***************setup RFM12****************************   
    #if RFM12

    #endif
//***************setup Mic******************************    
    #if MIC

    #endif
}

void loop() {
//    #if IRRESV	
//        doIRLogic();
//    #endif

    #if LDR	
        doLDRLogic();
    #endif
    
    #if BUTTON
        selectModus();
    #endif
    
    /* All in one serial communication function to interprete command from any serial port*/
    #if GENSERIAL
    serial_com();
      #if RTCLOCK
      if (timestamp!=timestampold){        //if the timestap is new adjust the RTC
      timestamp += 3600;
      timestampold = timestamp;
      DEBUG_PRINT(F("Time is "));
      DEBUG_PRINT(timestamp);
      RTC.adjust(DateTime(timestamp)); 
      }
      #endif
    #endif
    
    //ram_info();
    
    #if DCFMODUL

    time_t DCFtime = getTime(); // Check if new DCF77 time is available and adjust the RTC
        if (DCFtime!=0)
          {
              DEBUG_PRINT(F("Time is updated"));
              setTime(DCFtime);
              #if RTCLOCK
                RTC.adjust(DateTime(ye, mo, da, hour(), minute(), 0));
             #endif 
          }	
            
     #endif
    //Select Displaymode
	switch(displayMode) {
		case 0:                  //ONOFF
			off();
			break;
		case 1:                  //Fire Animation in a 10x10 Matrix
			animation();           
			break;
		case 2:                  //Disco or ColorClockmod
                        #if MIC
                        disco();
                        #endif
                        clockLogiColor(); //CLOCK with Color Change and DHT, a alternativ Modus for Boards without MIC (commit if Mic used)
                        #if DHT11
                            dhtRead();
                        #endif
			break;
		case 3:                   //CLOCK with temp and humidity		
                        clockLogic();
                        #if DHT11
                            dhtRead();
                        #endif
			break;
		case 4:                    //CLOCK only
			clockLogic();
			break;
                case 5:                    //Modus for Draw and game over Serialcom      
			#if GENSERIAL
                          serial_com();
                        #endif
			break;
		default:
                        clockLogic();
			break;
	}
}
//***********************DISPLAY MODES OFF**********************
void off() {
	if(millis() >= waitUntilOff) {
		DEBUG_PRINT("switching off");
		waitUntilOff = millis();
		resetAndBlack();
		displayStrip(CRGB::Black);
		waitUntilOff += halfSecondDelay;
	}
}
//*************************Led Function**********************
CRGB prevColor() {                    //used for Color Clock Mod
	if(colorIndex > 0) {
		colorIndex--;
	}
        if(colorIndex == 0) {
		colorIndex = 9;
	}
	return getColorForIndex();
}
CRGB nextColor() {                    //used for Color Clock Mod
	if(colorIndex < 9) {
		colorIndex++;
	}
         if(colorIndex == 9) {
		colorIndex = 0;
	}
	return getColorForIndex();
}

CRGB getColorForIndex() {              //used for Color Clock Mod
	switch(colorIndex) {
		case 0:
			return CRGB::White;
		case 1:
			return CRGB::Blue;
		case 2:
			return CRGB::Aqua;
		case 3:
			return CRGB::Green;
		case 4:
			return CRGB::Lime;
		case 5:
			return CRGB::Red;
		case 6:
			return CRGB::Magenta;
		case 7:
			return CRGB::Olive;
		case 8:
			return CRGB::Yellow;
		case 9:
			return CRGB::Silver;
		default:
			colorIndex = 0;
			return CRGB::Blue;
	}
}

void pushToStrip(int ledId) {                       //used a Array to now witch LED is on 
	strip[stackptr] = ledId;
	stackptr++;
}

void resetAndBlack() {                              //all LED set Black
	resetStrip();
	for(int i = 0; i<NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
}

void resetStrip() {                                  //reset Array for next use 
	stackptr = 0;
	for(int i = 0; i<NUM_LEDS; i++) {
		strip[i] = 0;
	}
}

void displayStripRandomColor() {                    //Random Color for Led
	for(int i = 0; i<stackptr; i++) {
		leds[strip[i]] = CHSV(random(0, 255), 255, 25);
	}
	FastLED.show();
}

void displayStrip() {                                //set Color defaultColor
	displayStrip(defaultColor);
}

void displayStrip(CRGB colorCode) {                  //set Color over variable from FastLED
	for(int i = 0; i<stackptr; i++) {
		leds[strip[i]] = colorCode;
	}
	FastLED.show();
}

void displayStrip(byte red, byte green, byte blue) { //set Color over RGB Code
	for(int i = 0; i<stackptr; i++) {
		leds[strip[i]] = CRGB( red, green, blue);
	}
	FastLED.show();
}
///////////////////////////////////////////////////////