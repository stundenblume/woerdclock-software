/**
* @file Sensors.h
* @brief Provide the properties of sensors
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

#ifndef Sensors_h
#define Sensors_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "config.h"

/* DHT11 */
#include "DHT.h"
#define DHTPIN 6
#define DHTTYPE DHT11

/**
* @brief Class of Sensors for Wördclock
* @details Provide the data from all sensors.
* @author Marcel Müller
* @version 0.1
*/
class Sensors
{
  public:
    Sensors();
  #if DHT11
    void readDHT11();
    int temp;
    int humi;
  #endif
    // place holder 
    // for attributes from other sensors
    // for functions to read other sensors
  private: 
};

#endif
