/**
* @file Sensors.cpp
* @brief Provide the properties of sensors
* @details 
* @author Marcel Müller
* @date 10.01.2015
* @version 0.1
*
* @copyright Copyright 2015 Marcel Müller. Some rights reserved. CC BY-NC-SA 4.0.
* @copyright This work by Marcel Müller is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* @copyright Permissions beyond the scope of this license may be available at https://github.com/marcel-mueller .
* @copyright To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/
#include "config.h"

/********************************************//**
 * @brief Constructor for sensors
 * @details 
 * @author Marcel Müller
 ***********************************************/
Sensors::Sensors()
{
  #if DHT11
    humi=0;
    temp=0;
    readDHT11();
  #endif
}
/********************************************//**
 * Sensor Configuration DHT 11
 ***********************************************/
#if DHT11
  DHT dht(DHTPIN, DHTTYPE); // Init
#endif
/********************************************//**
 * @brief Read the DHT11 sensor
 * @details Read humidity and temperature from DHT11 sensor.
 * humi contains Humidity. temp contains temperature as Celsius.
 * @author Marcel Müller
 ***********************************************/
void Sensors::readDHT11(void)
{
  #if DHT11
    humi = dht.readHumidity();
    temp = dht.readTemperature();
  #endif
}

