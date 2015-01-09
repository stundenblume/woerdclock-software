/**
* @file WoerdClockBasics.cpp
* @brief Load the properties of Wördclock
* @author Marcel Müller
* @date 10.01.2015
* @version 0.1
*
* @copyright Copyright 2015 Marcel Müller. Some rights reserved. CC BY-NC-SA 4.0.
* @copyright This work by Marcel Müller is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* @copyright Permissions beyond the scope of this license may be available at https://github.com/marcel-mueller .
* @copyright To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*
* @see WoerdClockBasics.h
*/
#include "config.h"

/********************************************//**
 * @brief Constructor for Wördclock basics
 * @details Initialization of Wördclock for clock mode.
 * Load: LED brightness, 
 * LED color red, Load LED color green and LED color blue 
 * from EEPROM to SRAM.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
WoerdClockBasics::WoerdClockBasics()  // Constructor
{
  displayMode=DEFAULT_MODE;
  LEDbright = EEPROM.read(LED_BRIGHT_EEPROM); // Load default value of LED brightness from EEPROM
  LEDcolorR = EEPROM.read(LED_COLORR_EEPROM); // Load default value of LED color red from EEPROM
  LEDcolorG = EEPROM.read(LED_COLORG_EEPROM); // Load default value of LED color green from EEPROM
  LEDcolorB = EEPROM.read(LED_COLORB_EEPROM); // Load default value of LED color blue from EEPROM
  
  FastLED.addLeds<WS2812B, WS2812BPIN, RGB>(leds, WS2812BCOUNT); // Initialize LEDs
}
