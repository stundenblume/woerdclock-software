/**
* @file WoerdClock.ino
* @brief Wördclock Sketch
* @details Run this sketch with the Arduino to use Wördclock
* @author Marcel Müller
* @author ...
* @author ...
* @author ...
* @date 10.01.2015
* @version 0.1
*
* @copyright Copyright 2015 Marcel Müller. Some rights reserved. CC BY-NC-SA 4.0.
* @copyright This work by Marcel Müller is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* @copyright Permissions beyond the scope of this license may be available at https://github.com/marcel-mueller .
* @copyright To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
* @copyright Excepted int SerialCom::parse(void) (c) 140801 Thomas Peetz.
* @copyright The parser based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz and was modified Marcel Müller.
* @copyright All rights reserved.
*
* @warning USE WÖRDCLOCK AT YOUR OWN RISK.
*
* @see config.h
* @see SerialCom.cpp
* @see SerialCom.h
* @see WoerdClockBasics.cpp
* @see WoerdClockBasics.h
*
* @note Tetris and snake works with Android App.
*
* @bug Disable DHT11 in config.h has no effect.
*
* @todo Add Wordclock logic
* @todo Add Wordclock views
* @todo Add RTC
* @todo Add Sensors
* @todo SerialCom.cpp: smod() is without any function, objects for view are needed
*/

#include <Wire.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <FastLED.h>
#include "RTClib.h"
#include "DHT.h"
#include "config.h"
#include "SerialCom.h"
#include "Sensors.h"

WoerdClockBasics woerdclock;  ///< Provides properties of the Wordclock
Sensors sensors;              ///< Provides the sensors
SerialCom Serials;            ///< Provides the communication

/********************************************//**
 * @brief Wördclock Sketch Setup 
 * for initializations
 ***********************************************/
void setup() 
{
  Serials.setWoerdClock(&woerdclock);  // Hand over the properties of the Wordclock to SerialCom
  Serials.setSensors(&sensors);        // Hand over the sensors to SerialCom
}

/********************************************//**
 * @brief Wördclock Sketch Loop 
 * for cyclic jobs
 ***********************************************/
void loop()
{
  #if DHT11
    sensors.readDHT11();
  #endif
  #if GENSERIAL
    Serials.execute();
  #endif
  
  /* Example: How to use SerialCom inside a Sketch */
  /*
   delay(1000);
   Serials.port=0; 
   Serials.println("Hello USB"); 
   Serials.port=1; 
   Serials.println("Hello Bluetooth"); 
  */
  
}

