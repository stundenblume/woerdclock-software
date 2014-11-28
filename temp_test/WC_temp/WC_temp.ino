#include <Wire.h>
#include "RTClib.h"
#include "FastLED.h"
#include "DHT.h"

#define DHTPIN 2           // DHT11

#define WS2812BPIN 5       //LEDS
#define BRIGHTNESS  50     // LED Helligkeit

#define WS2812BCOUNT 114   // LED Anzahl

const int numbers[2] = {X_ORIGIN, Y_ORIGIN, Z_ORIGIN};

CRGB leds[WS2812BCOUNT];

int temperatur = 22;

void setup()  {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
    }
   FastLED.addLeds<WS2812B, WS2812BPIN, RGB>(leds, WS2812BCOUNT);
   FastLED.setBrightness( BRIGHTNESS );
   selftest(500);
}
void loop()  {
}

