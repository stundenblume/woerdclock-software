#include <Wire.h>
#include "RTClib.h"
#include "FastLED.h"
#include "DHT.h"

#define DHTPIN 2           // DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define WS2812BPIN 5       //LEDS
#define BRIGHTNESS  50     // LED Helligkeit
#define COLOR_ORDER GRB

#define WS2812BCOUNT 114   // LED Anzahl


CRGB leds[WS2812BCOUNT];

int temperatur = 22;

void setup()  {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
    }
   Serial.println("Selftest");
   FastLED.addLeds<WS2812B, WS2812BPIN, COLOR_ORDER>(leds, WS2812BCOUNT);
   FastLED.setBrightness( BRIGHTNESS );
   selftest(500);
   Serial.println("!!!Test!!!");
   dht.begin();
}
void loop()  {
  dhtsensor();
}

