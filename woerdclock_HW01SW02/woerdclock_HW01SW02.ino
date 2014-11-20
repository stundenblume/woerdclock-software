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
*/

//Library includes
#include <FastLED.h>
#include <Wire.h>
//#include <Time.h>
//#include <DCF77.h>
#include <IRremote.h>
#include "RTClib.h"
#include <RF12.h>
//#include <util/crc16.h>
//#include <util/parity.h>
#include <avr/eeprom.h>
#include <EEPROM.h>
//#include <avr/pgmspace.h>

// IR defines
#define ONOFF 0xFF02FD
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

RTC_DS1307 RTC;

//LED defines
#define NUM_LEDS 114

//PIN defines
#define STRIP_DATA_PIN 7
#define IR_RECV_PIN 6
#define ARDUINO_LED 5           //Default Arduino LED
#define DCF_PIN 3	         // Connection pin to DCF 77 device
#define DCF_INTERRUPT 1		 // Interrupt number associated with pin
//#define LDR_PIN 0
#define ANALOGPIN 0              //Analogpin for Button and LDR

//RTC variables
boolean RTCpresent=false;
unsigned long lastSecond;
byte h=4, m=4, s=4;

//dcf variables
//time_t time;
//DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);
//bool timeInSync = false;

//Button variables
#define CHARSHOWTIME 600
#define AUTOENDTIME 5000
#define TIMEEXTENSION 10000
#define TOLLERANCE 10

//LED varables
uint8_t strip[NUM_LEDS];
uint8_t stackptr = 0;
CRGB leds[NUM_LEDS];
IRrecv irrecv = IRrecv(IR_RECV_PIN);
decode_results irDecodeResults;

//Clock variables
uint8_t selectedLanguageMode = 0;
const uint8_t RHEIN_RUHR_MODE = 0; //Define?
const uint8_t WESSI_MODE = 1;
//Auto Brightness On or Off
int testHours = 0;
int testMinutes = 0;
int hButtonValue=1,mButtonValue=2,okButtonValue=4;

//Default Config
//Display Mode at start
int displayMode = DEFAULT;
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

//Debug Mode or not (uncommand)
#define DEBUG

#ifdef DEBUG
	#define DEBUG_PRINT(str)  Serial.println (str)
#else
	#define DEBUG_PRINT(str)
#endif

void setup() {
	
	#ifdef DEBUG
		Serial.begin(9600);
	#endif
	
	
        //Setup LED Matrix*******************
        pinMode(ARDUINO_LED, OUTPUT);
	
	for(int i = 0; i<NUM_LEDS; i++) {
		strip[i] = 0;
	}
	FastLED.addLeds<WS2812B, STRIP_DATA_PIN, GRB>(leds, NUM_LEDS);
	resetAndBlack();
	displayStrip();

        //Setup RTC***************************
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
        }	


	//setup DCF*****************************
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

	//setup ir******************************
	irrecv.enableIRIn();
}

void loop() {
	doIRLogic();
	doLDRLogic();
	switch(displayMode) {
		case ONOFF:
			off();
			break;
		case DIY1:
			clockLogic();
			break;
		case DIY2:
			disco();
			break;
		case DIY3:
			animation();
			break;
		case DIY4:
			clockLogic();
			break;
		default:
                        fastTest();
			break;
	}
}

//unsigned long getDCFTime() {
//	time_t DCFtime = DCF.getTime();
//	// Indicator that a time check is done
//	if (DCFtime!=0) {
//		DEBUG_PRINT("sync");
//	}
//	return DCFtime;
//}


///////////////////////
//DISPLAY MODES
///////////////////////


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
///////////////////////

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

///////////////////////
