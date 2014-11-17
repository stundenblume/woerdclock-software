/*

 */
#include <Wire.h>
#include "RTClib.h"
#include "FastLED.h"


RTC_DS1307 RTC;

#define WS2812BPIN 10
#define ANALOGPIN 3

#define WS2812BCOUNT 114

boolean RTCpresent=false;

unsigned long lastSecond;

byte h=4, m=4, s=4;

CRGB leds[WS2812BCOUNT];


void setup()  {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Woerdclock Start");
  
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
      FastLED.addLeds<WS2812B, WS2812BPIN, RGB>(leds, WS2812BCOUNT);

  selftest(100); // test all LEDs

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
} 

void loop()  {
  // loop over and over again to show the current time

  //if (millis()-lastSecond >= 1000){
  if (millis()-lastSecond >= 10){ // just for test reasons every 10ms instead of 1s, so the time will be 10times faster
    lastSecond=millis();
    calcTime();
  }
  showTime(); // show current time
  delay (100); // wait a little, we don't need to update to often
}




















