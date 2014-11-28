#include <Wire.h>
#include "RTClib.h"
#include "FastLED.h"
#include "DHT.h"

#define WS2812BPIN 5
#define BRIGHTNESS  50

#define WS2812BCOUNT 114
CRGB leds[WS2812BCOUNT];

int temperatur = 22;

void setup()  {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
    }
   FastLED.addLeds<WS2812B, WS2812BPIN, RGB>(leds, WS2812BCOUNT);
   FastLED.setBrightness( BRIGHTNESS );
   selftest(1000);
}
void loop()  {
}

