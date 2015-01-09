/**
* @file SerialCom.h
* @brief Serial Communication Module for Wördclock
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

#ifndef SerialCom_h
#define SerialCom_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "config.h"
#include "WoerdClockBasics.h"
#include "Sensors.h"

#define HELPMSG 1 ///< Set to 1 if you need a command reference via serial interface. Type help.

#if BLUETOOTH0 || USBPORT0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
#define GENSERIAL 1 ///< General serial interface. Set to 0 if you have no serial communication port.
#endif

/**
* @brief Class of Serial Communication Modul for Wördclock
* @details Defines members of the Serial Communication Modul.
* @author Marcel Müller
* @note Before using SerialCom you have to instance an object global, e.g. Serials:
* @note SerialCom Serials;
* @note In this case Serials is your object. You can use it inside void loop().
* @note Before using a member of the objekt Serials like print(), you have to define the port:
* @note Serials.port=0;
*
* @note Example: How to use SerialCom inside a Sketch
* @note void setup(){
* @note }
* @note void loop()
* @note {
* @note delay(1000);
* @note Serials.port=0; 
* @note Serials.println("Hello USB"); 
* @note Serials.port=1; 
* @note Serials.println("Hello Bluetooth"); 
* @note }
* @date 10.01.2015
* @version 0.1
*/
class SerialCom
{
  public:
    SerialCom();
    void execute(void);
    void debugmode(void);
    byte dummy(byte);
    char read(void);
    void print(byte value);
    void print(int value);
    void print(char value);
    void print(char str[]);
    void println(byte value);
    void println(int value);
    void println(char value);
    void println(char str[]);
    void print(const char *str);
    void println(const char *str);
    void println(void);
    void setWoerdClock(WoerdClockBasics* wc); ///< Object reference to basic properties of Wördclock
    void setSensors(Sensors* sens);
    long BAUDRATE;             ///< Baudrate
    byte port;                 ///< Port number
    byte debugPort;            ///< Port for debugging, set by show
    boolean debug;             ///< for debugging only
    long debugpreviousmillis;  ///< for debugging only
    long debuginterval;        ///< for debugging only
  
  private:
    WoerdClockBasics *woerdclock;  ///< Provides properties of the Wordclock
    Sensors *sensors;              ///< Provides the sensors
    void checkports(void);
    int parse(void);
    void interprete(int j);
    void clean(void);
    void print_cmd(int j);
    void help();
    void welcome();
    void slb();
    void glb(int j);
    void slbp();
    void glbp(int j);
    void slc();
    void glc(int j);
    void slcp();
    void glcp(int j);
    void sled();
    void gled(int j);
    void srtc();
    #if DHT11 void gt(int j);   #endif
    #if DHT11 void gh(int j);   #endif
    void smod();
    void gmod(int j);
    void errormsg();

};

#endif
