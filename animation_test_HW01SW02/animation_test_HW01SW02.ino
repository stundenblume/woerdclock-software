/*
................-......-...............
..............-@W......W@-.............
............-@WWW......WWW@-...........
..........-@WWWWW......WWWWW@-.........
........-@WWW*WWW......WWW*WWW@-.......
......-@W#:...WWW......WWW-..:#W@-.....
....-@*...:...WWW......WWW-..:...*@-...
.....-*@WWW-..WWW......WWW-..WWW@*-....
.+@WWWWWWWW-..WWWWWWWWWWWW-..WWWWWWWW@+
.-@WW=*=WWW-..WWW======WWW-..WWW===WW@-
...-@...WWW-..WWW......WWW-..WWW...@-..
........WWW...WWW......WWW-..WWW.......
........@WW...WWW......WWW-..WW@.......
.........-@...WWW......WWW-..@-........
..............WWW......WWW-............
..............@WW......WW@.............
...............-@......@-..............
V0.1 by KeyJay.........................
*/

//LIBRARYS//
#include <Wire.h>
#include "RTClib.h"
#include "FastLED.h"
#include "DHT.h"

//MODULES//


#define WS2812BPIN 5       //LEDS
#define BRIGHTNESS  50     // LED Helligkeit
#define COLOR_ORDER GRB

#define WS2812BCOUNT 114   // LED Anzahl

uint8_t strip[WS2812BCOUNT];
uint8_t stackptr = 0;
CRGB leds[WS2812BCOUNT];


int temperatur = 22;
int DHT_TIMER = 0;

//SETUP//
void setup()  {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
    }
   Serial.println("Selftest");
   FastLED.addLeds<WS2812B, WS2812BPIN, COLOR_ORDER>(leds, WS2812BCOUNT);
   FastLED.setBrightness( BRIGHTNESS );
   selftest(25);
   Serial.println("!!!Test!!!");
   selftest_RGB(250);
 
}
//LOOP//
void loop()  {
  
}

