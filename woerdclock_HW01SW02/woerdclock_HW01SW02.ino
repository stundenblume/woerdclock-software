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
#define RTCLOCK 1     //Module Real Time Clock
#define BUTTON 1     //Button are used
#define LDR 1        //LDR is used
#define BLUETOOTH1 0 //Module Bluetooth 1
#define BLUETOOTH2 0 //Module Bluetooth 2
#define WLAN 0       //Module WLAN
#define DOF 0        //Module 10DOF
#define DCF 0        //Module DCF77
#define SDCARD 0     //Module SD Card
#define MIC 0        //Module Microfon
#define IR 0         //Module IR
#define DHT11 0      //Module DHT11
#define RFM12 0      //Module RMF12B

//Debug Mode or not (uncommand)
#define DEBUG 1
//****************************LED Config************************
//Library includes
#include <FastLED.h>
#include <Wire.h>
//LED defines
#define NUM_LEDS 114

//Modus variables
  #define ONOFF 0
  #define FAST  1
  #define DISCO 2
  #define ANIM  3
  #define CLOCK 4
 
//PIN defines
#define STRIP_DATA_PIN 21
//#define ARDUINO_LED 5           //Default Arduino LED

//LED varables
uint8_t strip[NUM_LEDS];
uint8_t stackptr = 0;
CRGB leds[NUM_LEDS];
 
//arrays for the char  
// int arrayA [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayB [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayC [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayD [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayE [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayF [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayG [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
// int arrayH [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayI [6][10] =  {{0,0,0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayJ [6][10] =  {{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayK [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,1,0,1,0,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
// int arrayL [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayM [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayN [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
// int arrayO [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayP [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayQ [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayR [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,1,0,1,0,0,0,0,0,0},{0,1,0,1,1,0,0,0,0,0},{0,1,1,1,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};          
 //int arrayS [6][10] =  {{0,1,1,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,0,1,0,0,0,0},{0,1,0,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
 //int arrayT [6][10] =  {{0,1,0,0,0,0,0,0,0,0},{0,1,1,1,1,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayU [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayV [6][10] =  {{0,1,1,0,0,0,0,0,0,0},{0,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,0},{0,0,0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayW [6][10] =  {{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayX [6][10] =  {{0,1,0,0,0,0,1,0,0,0},{0,0,1,0,1,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,1,0,1,0,0,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 //int arrayY [6][10] =  {{0,1,0,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};            
 //int arrayZ [6][10] =  {{0,1,0,0,0,1,0,0,0,0},{0,1,1,0,0,1,0,0,0,0},{0,0,1,1,0,1,0,0,0,0},{0,1,0,0,1,1,0,0,0,0},{0,1,0,0,0,6,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};           
 //int array_ [6][10] =  {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};           
 int array1 [6][10] =  {{0,0,0,1,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};            
 int array2 [6][10] =  {{0,0,1,0,0,0,1,1,0,0},{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,1,1,0,1,0,0},{0,1,0,1,0,0,0,1,0,0},{0,0,1,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,0,0}};             
 int array3 [6][10] =  {{0,0,1,0,0,0,1,0,0,0},{0,1,0,0,0,0,1,0,0,0},{0,1,0,0,1,1,1,0,0,0},{0,1,0,1,0,0,1,0,0,0},{0,0,1,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
 int array4 [6][10] =  {{0,1,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,1,1,1,1,1,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
 int array5 [6][10] =  {{0,1,1,0,0,0,7,0,0,0},{0,1,0,1,0,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,0,1,0,1,0,0},{0,0,1,0,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,0,0}};           
 int array6 [6][10] =  {{0,0,1,1,1,1,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
 int array7 [6][10] =  {{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,0,1,1,0,0,0},{0,1,0,0,0,1,0,0,0,0},{0,1,0,0,1,0,0,0,0,0},{0,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};             
 int array8 [6][10] =  {{0,0,1,1,1,1,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};        
 int array9 [6][10] =  {{0,0,1,1,0,0,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,1,0,0,1,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};            
 int array0 [6][10] =  {{0,0,1,1,1,1,1,0,0,0},{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,0,0,0,1,0,0},{0,1,0,0,0,0,0,1,0,0},{0,0,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
   
//****************************RTC Config Library************************
#if RTCLOCK  
  #include "RTClib.h"
  RTC_DS1307 RTC;
 //RTC variables
  boolean RTCpresent=false;
  unsigned long lastSecond;
  byte h=4, m=4, s=4;
  //Clock variables
  uint8_t selectedLanguageMode = 0;
  const uint8_t RHEIN_RUHR_MODE = 0; //Define?
  const uint8_t WESSI_MODE = 1;
  //Auto Brightness On or Off
  int testHours = 0;
  int testMinutes = 0;
#endif
//****************************Button Config**********************
#if BUTTON
  #include <EEPROM.h>
  #define ANALOGPIN A1              //Analogpin for Button and LDR
  //Button variables
  #define CHARSHOWTIME 600
  #define AUTOENDTIME 5000
  #define TIMEEXTENSION 10000
  #define TOLLERANCE 10
  boolean menue=false,debugmod=true, modus=false;
  int hButtonValue=1,mButtonValue=2,okButtonValue=4;
#endif
//****************************LDR Config************************
#if LDR
  //#define ANALOGPIN 0              //Analogpin for Button and LDR
#endif
//****************************Bluetooth1 Config******************
#if BLUETOOTH1

#endif
//****************************Bluetooth2 Config******************
#if BLUETOOTH2

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
#endif
//****************************SD Config*************************
#if SDCARD

#endif
//****************************Mic Config************************
#if MIC

#endif
//****************************IR Config*************************
#if IR
  #include <IRremote.h>
  // IR defines
  //#define ONOFF 0xFF02FD
  #define AUTO 0xFFF00F
  #define BLUE_DOWN 0xFF48B7
  #define BLUE_UP 0xFF6897
  #define BRIGHTER 0xFF3AC5
  #define DIM 0xFFBA45
  #define DIY1 0xFF30CF
  #define DIY2 0xFFB04F
  #define DIY3 0xFF708F
  #define DIY4 0xFF10EF
  #define DIY5 0xFF906F
  #define DIY6 0xFF50AF
  #define FLASH 0xFFD02F
  #define QUICK 0xFFE817
  #define SLOW 0xFFC837
  
  #define IR_RECV_PIN 6
  
  //IR variables
  IRrecv irrecv = IRrecv(IR_RECV_PIN);
  decode_results irDecodeResults;
#endif
//****************************DHT11 Config**********************
#if DHT11
  #include "DHT.h"
  #define DHTPIN 8   
  #define DHTTYPE DHT11 
  DHT dht(DHTPIN, DHTTYPE);

  float humi = 0;
  float temp = 0;
  
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
int displayMode = 4;        //Clock is default Modus
//Default Color?
CRGB defaultColor = CRGB::Red; //White, Red, Green, Blue, Yellow
uint8_t colorIndex = 0;
boolean autoBrightnessEnabled = true;
int brightness = 50;

//multitasking helper
const long oneSecondDelay = 1000;
const long halfSecondDelay = 500;
long waitUntilRtc = 0;
long waitUntilParty = 0;
long waitUntilOff = 0;
long waitUntilFastTest = 0;
long waitUntilHeart = 0;
long waitUntilDCF = 0;
long waitUntilLDR = 0;
long waitUntilwriteChar = 0;

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
		Serial.begin(9600);
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
//***************Setup RTC***************************
     #if BUTTON
        if(analogRead(ANALOGPIN)<10) menue = true;        //Menue start with Jumper
        
        selftest(100); // test all LEDs

        if (menue && analogRead(ANALOGPIN)>10) {          //Debug start with Jumper set after selftest, nothing to debug!
          debugmod=true;
          menue=false;
          resetAndBlack();
	  pushToStrip(1);
          pushToStrip(2);
          displayStrip(CRGB::Blue);
          DEBUG_PRINT("Debug");
//          writeChar('D');
//          writeChar('E');
//          writeChar('B');
//          writeChar('U');
//          writeChar('G');
          
        }
        if (!menue && !debugmod){                        //No debug no menue, normal start
            resetAndBlack();
	    pushToStrip(3);
            pushToStrip(1);
            displayStrip(CRGB::Green);
            DEBUG_PRINT("Hi");
//          writeChar('H');
//          writeChar('I');
        }
     
        boolean calibOK = alreadyCalibrated();           // Check if there is was already a calibration of the buttons 
        DEBUG_PRINT("cali=");
        DEBUG_PRINT(calibOK);
        if (!calibOK || menue) buttonCalibration();      // if there wasn't already a calibration OR jumper is open, do the calibration
//        DEBUG_PRINT("hButton=");
//        DEBUG_PRINT(hButtonValue);
//        DEBUG_PRINT("mButton=");
//        DEBUG_PRINT(mButtonValue);
//        DEBUG_PRINT("okButton=");
//        DEBUG_PRINT(okButtonValue);
        if (menue && calibOK) adjustTime(); // if the jumper ist open AND the there is al calibration for the buttonValus, go to adjust the time
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
    #if IR	
      irrecv.enableIRIn();
    #endif
//***************setup Bluetooth1**********************    
    #if BLUETOOTH1

    #endif 
//***************setup Bluetooth2**********************
    #if BLUETOOTH2

    #endif
//***************setup WLAN*****************************
    #if WLAN

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
    #if IR	
        doIRLogic();
    #endif

    #if LDR	
        doLDRLogic();
    #endif
    
    #if BUTTON
        selectModus();
    #endif
    
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
		default:
                        clockLogic();
			break;
	}
}

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

//***********************DISPLAY MODES**********************

void off() {
	if(millis() >= waitUntilOff) {
		DEBUG_PRINT("switching off");
		waitUntilOff = millis();
		resetAndBlack();
		displayStrip(CRGB::Black);
		waitUntilOff += halfSecondDelay;
	}
}

void fastTest() {
	if(millis() >= waitUntilFastTest) {
		autoBrightnessEnabled = false;
		DEBUG_PRINT("fastTest");
		waitUntilFastTest = millis();
		if(testMinutes >= 60) {
			testMinutes = 0;
			testHours++;
		}
		if(testHours >= 24) {
			testHours = 0;
		}
		
		//Array leeren
		resetAndBlack();
		timeToStrip(testHours, testMinutes);
		displayStripRandomColor();
		testMinutes++;
		waitUntilFastTest += oneSecondDelay;
	}
}
//*************************Led Function**********************
CRGB prevColor() {
	if(colorIndex > 0) {
		colorIndex--;
	}
	return getColorForIndex();
}
CRGB nextColor() {
	if(colorIndex < 9) {
		colorIndex++;
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
			return CRGB::Red;
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
///////////////////////////////////////////////////////
