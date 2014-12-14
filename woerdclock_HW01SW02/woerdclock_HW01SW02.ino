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
#define LDR 0         //LDR is used
#define GENSERIAL 0    //Gen Serial
#define BLUETOOTH0 0   //Module Bluetooth, via pin 0,1 - default=0, because on this port is the led stripe connected
#define USBPORT0 0     // Serial Communication across usb
#define BLUETOOTH1 0   //Module Bluetooth 1
#define BLUETOOTH2 0   //Module Bluetooth 2
#define WLAN 0         //Module WLAN
#define DOF 0          //Module 10DOF
#define DCF 0          //Module DCF77
#define SDCARD 0       //Module SD Card
#define MIC 0          //Module Microfon
#define IRRESV 0         //Module IR
#define DHT11 0        //Module DHT11
#define RFM12 0        //Module RMF12B
#define TEXT 0        //Show Text



//Debug Mode or not (uncommand)
#define DEBUG 1
//****************************LED Config************************
//Library includes
#include <FastLED.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
//LED defines
#define NUM_LEDS 114
long BAUDRATE = 9600; // default Baudrate for serial communication
 
//PIN defines
#define STRIP_DATA_PIN 21
//#define ARDUINO_LED 5           //Default Arduino LED

//LED varables
uint8_t strip[NUM_LEDS];
uint8_t stackptr = 0;
CRGB leds[NUM_LEDS];
   
//****************************RTC Config Library************************
#if RTCLOCK
  #include "RTClib.h"
  RTC_DS1307 RTC;
 //RTC variables
  boolean RTCpresent=false;
  unsigned long lastSecond;
  byte ye=0, mo=0, da=0, h=4, m=4, s=4;
  //Clock variables
  uint8_t selectedLanguageMode = 0;
  const uint8_t RHEIN_RUHR_MODE = 0; //Define?
  const uint8_t WESSI_MODE = 1;
  //Auto Brightness On or Off
  int testHours = 0;
  int testMinutes = 0;
  long waitUntilRtc = 0;
#endif

//****************************Button Config**********************
#if CONFIGBUTTON
  
  #define ANALOGPIN A1 
  //Button variables
  #define CHARSHOWTIME 600
  #define AUTOENDTIME 5000
  #define TIMEEXTENSION 10000
  #define TOLLERANCE 10
  
  boolean menue=false,debugmod=true, modus=false;
  int hButtonValue=1,mButtonValue=2,okButtonValue=4;
#endif

//****************************Button ****************************
#if BUTTON
  
  #define ANALOGPIN A1              //Analogpin for Button and LDR
  //Button variables
  #define AUTOENDTIME 5000
  #define TOLLERANCE 10
  boolean modus=false;
  int hButtonValue=1,mButtonValue=2,okButtonValue=4;
#endif
//****************************LDR Config************************
#if LDR
  long waitUntilLDR = 0;
#endif
//****************************Serial Config******************
#if GENSERIAL
 #include <SoftwareSerial.h>
 byte serial_com_port = 255; // A number to seperate the ports for serial communication from each other
 boolean showvalues = false; // For debugging only
 boolean LED[NUM_LEDS] = {0};// this is a dummy array for the LEDs of wordclock 0=off, 1=on
 long timestamp = 0;  // this is a dummy variable for the date and time in unix time stamp format (see http://playground.arduino.cc/Code/Time )
 
 /* Start command definitions for serial communication - don't touch this 
    based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz */
/*
  paraCount defines the maximum number of command and parameters
  paraLength defines the maximum length for commands and parameters (paraLength = max command/parameter length +1)
  cmdCount defines the number of entities
  cmdStrCon defines the commands in lower case!!
*/
const byte  paraCount = 4;                            // max quantity of parameter (incl. command) per line    slc = r,g,b
const byte  paraLength = 5;                           // max length per parameter/command (-1)                 help,show
const byte  cmdCount = 16;                            // quantity of possible commands                        show to slcp
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
    "mode"}
};
char       cmdStr[paraCount*paraLength+paraCount+1]; //buffer for complete line of comand and parameter
int        cmdStrIn=0;                               //index for the cmdStr 
char       cmd[paraCount][paraLength];               //arry with command and parameters
/* End command definitons for serial communication - don't touch this */
#endif
//****************************Bluetooth1 Config******************
#if BLUETOOTH1
 SoftwareSerial BTSerial(8, 9); // Connect Arduino Micro pin 9 with HC-06 pin RX and Arduino Micro pin 8 with HC-06 pin TX
#endif
//****************************Bluetooth2 Config******************
#if BLUETOOTH2
  SoftwareSerial BTSerial2(10, 11); // Connect Arduino Micro pin 15 with HC-06 pin RX and Arduino Micro pin 14 with HC-06 pin TX
#endif
//****************************WLAN Config************************
#if WLAN

#endif
//****************************10DOF Config***********************
#if DOF

#endif
//****************************DCF Config************************
#if DCF
  //#include <Time.h>
  //#include <DCF77.h>
  
  #define DCF_PIN 7	         // Connection pin to DCF 77 device
  #define DCF_INTERRUPT 4	 // Interrupt number associated with pin
  
  //dcf variables
  //time_t time;
  //DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);
  //bool timeInSync = false;
  long waitUntilDCF = 0;
#endif
//****************************SD Config*************************
#if SDCARD

#endif
//****************************Mic Config************************
#if MIC

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
  #define DHTPIN 8   
  #define DHTTYPE DHT11 
  DHT dht(DHTPIN, DHTTYPE);

  int humi = 0;
  int temp = 0;
  
//  int temperatur = 22;
  int DHT_TIMER = 0;
 
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
//****************************RFM12 Config**********************
#if RFM12
  #include <RF12.h>
  //#include <util/crc16.h>
  //#include <util/parity.h>
  #include <avr/eeprom.h>
  //#include <avr/pgmspace.h>
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
boolean autoBrightnessEnabled = true;
byte brightness = 50;

//multitasking helper
const long oneSecondDelay = 1000;
const long halfSecondDelay = 500;

long waitUntilParty = 0;
long waitUntilOff = 0;
long waitUntilFastTest = 0;
long waitUntilHeart = 0;

boolean dhtaktion = false;       //dht in aktion marker

//****************************Debug Config**********************
#ifdef DEBUG
	#define DEBUG_PRINT(str)  Serial.println (str)
#else
	#define DEBUG_PRINT(str)
#endif
//****************************Setup*****************************
//##############################################################
//***************************************************************
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
          RTCpresent = true;
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
        resetAndBlack();
	pushToStrip(0);
        pushToStrip(3);
        displayStrip(CRGB::Red);
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
    #if DCF
//	DCF.Start();
//	setSyncInterval(30);
//	setSyncProvider(getDCFTime);
//	DEBUG_PRINT("Waiting for DCF77 time ... ");
//	DEBUG_PRINT("It will take at least 2 minutes until a first update can be processed.");
//	while(timeStatus()== timeNotSet) {
//		// wait until the time is set by the sync provider
//		DEBUG_PRINT(".");
//		delay(2000);
//	}
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
  Serial1.begin(BAUDRATE);      // initialize serial port for bluetooth
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
    
    #if DHT11
        dhtRead();
    #endif
    
    /* All in one serial communication function to interprete command from any serial port*/
    //#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
    #if GENSERIAL
    serial_com();
    #endif
    
    //ram_info();
    
    #if DCF
        //unsigned long getDCFTime() {
        //	time_t DCFtime = DCF.getTime();
        //	// Indicator that a time check is done
        //	if (DCFtime!=0) {
        //		DEBUG_PRINT("sync");
        //	}
        //	return DCFtime;
        //}
     #endif
    //Select Displaymode
	switch(displayMode) {
		case 0:              //ONOFF
			off();
			break;
		case 1:              //FAST
			fastTest();           
			break;
		case 2:              //DISCO
			disco();
			break;
		case 3:               //ANIM
			animation();
			break;
		case 4:                //CLOCK
			clockLogic();
			break;
                case 5:                
			clockLogiColor(); //CLOCK with Color Change
			break;
		default:
                        clockLogiColor();
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
CRGB prevColor() {
	if(colorIndex > 0) {
		colorIndex--;
	}
        if(colorIndex == 0) {
		colorIndex = 9;
	}
	return getColorForIndex();
}
CRGB nextColor() {
	if(colorIndex < 9) {
		colorIndex++;
	}
         if(colorIndex == 9) {
		colorIndex = 0;
	}
	return getColorForIndex();
}

CRGB getColorForIndex() {
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

void pushToStrip(int ledId) {
	strip[stackptr] = ledId;
	stackptr++;
}

void resetAndBlack() {
	resetStrip();
	for(int i = 0; i<NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
}

void resetStrip() {
	stackptr = 0;
	for(int i = 0; i<NUM_LEDS; i++) {
		strip[i] = 0;
	}
}

void displayStripRandomColor() {
	for(int i = 0; i<stackptr; i++) {
		leds[strip[i]] = CHSV(random(0, 255), 255, 25);
	}
	FastLED.show();
}

void displayStrip() {
	displayStrip(defaultColor);
}

void displayStrip(CRGB colorCode) {
	for(int i = 0; i<stackptr; i++) {
		leds[strip[i]] = colorCode;
	}
	FastLED.show();
}

void displayStrip(byte red, byte green, byte blue) {
	for(int i = 0; i<stackptr; i++) {
		leds[strip[i]] = CRGB( red, green, blue);
	}
	FastLED.show();
}
///////////////////////////////////////////////////////
