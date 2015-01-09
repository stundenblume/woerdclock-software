/**
* @file WoerdClockBasics.h
* @brief Provide the properties for Wördclock
* @details Configuration file
* @author Marcel Müller
* @date 10.01.2015
* @version 0.1
*
* @copyright Copyright 2015 Marcel Müller. Some rights reserved. CC BY-NC-SA 4.0.
* @copyright This work by Marcel Müller is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* @copyright Permissions beyond the scope of this license may be available at https://github.com/marcel-mueller .
* @copyright To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

#ifndef wc_h
#define wc_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "config.h"

/**
* @brief Class for wordclock basic properties
* @details Contains the basic properties of the wordclock: 
* default colors, current time,..
* @author Marcel Müller
* @date 10.01.2015
* @version 0.1
*/
class WoerdClockBasics
{
  public:
    WoerdClockBasics();
    byte displayMode;           ///< Mode of Wördclock
    byte LEDbright;             ///< LED brightness: 0-255
    byte LEDcolorR;             ///< LED color red: 0-255
    byte LEDcolorG;             ///< LED color green:  0-255
    byte LEDcolorB;             ///< LED color blue:  0-255
    long timestamp;             ///< Current Time in unix time stamp format
    CRGB leds[NUM_LEDS];        ///< LED Array for FASTLED
    byte h;                     ///< Hours of current time
    byte m;                     ///< Minutes of current time
    byte s;                     ///< Seconds of current time
    boolean RTCpresent;         ///< this variable will store if a RTC is present
    RTC_DS1307 RTC;             ///< Realtimeclock
    unsigned long lastSecond;   ///< this Var will store when the last tick was made
  private:
};

#endif
