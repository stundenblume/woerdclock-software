/*******************************************
 * Name.......:  Wördclock
 * Description:  This scetch wich will light up your Wördclock with minimal Hardware.
 * Author.....:  Sebastian Setz
 * Version....:  0.2
 * Date.......:  2014-12-28
 * Project....:  http://woerdclock.com http://wördclock.de
 * Contact....:  http://Sebastian.Setz.name
 * License....:  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
 * Credit.....:  function "koordinate()", Jan S. (https://github.com/khold1996)
 *               FastLED library, https://github.com/FastLED/FastLED
 *               RTC library, adafruit https://github.com/adafruit/RTClib
 * Keywords...:  arduino, time, clock, wordclock
 * History....:  2014-12-26 V0.1 - release
 *               2014-12-28 V0.2 - added different styles for displaying the time
 ********************************************/

// include some libraries
//////////////////////
#include <Wire.h>
#include "RTClib.h"
#include "FastLED.h"


// global defines
///////////////////////////
#define TIMESCALE 1 // 1second / TIMESCALE, 1 for normal use 2 for two times faster...

#define WS2812BPIN 8 // where is the the data line of the LEDs connected
#define WS2812BCOUNT 114 // how many LEDs are present

boolean RTCpresent=false; // this variable will store if a RTC is present

unsigned long lastSecond; // this Var will store when the last tick was made

byte h=11, m=11, s=11; // this vars will store the current time

// init some libraries
/////////////////////
RTC_DS1307 RTC; // Realtimeclock
CRGB leds[WS2812BCOUNT]; // WS2812B LEDs


void setup()  {
  Serial.begin(9600);

  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  FastLED.addLeds<WS2812B, WS2812BPIN, RGB>(leds, WS2812BCOUNT);

  Serial.println("Woerdclock Start.");

  selftest(50); // test all LEDs

  Wire.begin(); // start I²C

  // RTC
  ////////////////////////////
  RTC.begin();
  initRTC();
} 

void loop()  {
  // loop over and over again to show the current time
  if (millis()-lastSecond >= 1000/TIMESCALE){
    lastSecond=millis();
    calcTime();
    showTime(0); // show current time
  }
}

























