/**
* @file config.h
* @brief Overall configuration file for Wördclock
* @details Use this file to enable (1) or disable (0) particular modules of Wördclock, e.g. sensors.
* Sensors need also some informations e.g. about pins they have to use. Define the pins here.
* @author Marcel Müller
* @date 10.01.2015
* @version 0.1
* @copyright Copyright 2015 Marcel Müller. Some rights reserved. CC BY-NC-SA 4.0.
* @copyright This work by Marcel Müller is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* @copyright Permissions beyond the scope of this license may be available at https://github.com/marcel-mueller .
* @copyright To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

#ifndef config_h
#define config_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

/* Select your modules */
#define CONFIGBUTTON 0 ///< Enable/disable Config Buttons and adjust Time, SET CONFIGBUTTON or BUTTON 
#define RTCLOCK 1      ///< Enable/disable Module Real Time Clock
#define BUTTON 0       ///< Enable/disable Button are used  SET CONFIGBUTTON or BUTTON 
#define LDR 0          ///< Enable/disable Module LDR
#define DOF 0          ///< Enable/disable Module 10DOF
#define DCFMODUL 0     ///< Enable/disable Module DCF77
#define SDCARD 0       ///< Enable/disable Module SD Card
#define MIC 0          ///< Enable/disable Module Microfon
#define IRRESV 0       ///< Enable/disable Module IR
#define DHT11 1        ///< Enable/disable Module DHT11
#define RFM12 0        ///< Enable/disable Module RMF12B
#define TEXT 0         ///< Enable/disable Show Massage Board 
#define TEXT2 0        ///< Enable/disable Show Text

/* Woerdclock */
#define WS2812BPIN 8        ///< where is the the data line of the LEDs connected
#define WS2812BCOUNT 114    ///< how many LEDs are present
#define TIMESCALE 1         ///< 1second / TIMESCALE, 1 for normal use 2 for two times faster...
#define NUM_LEDS 114        ///< Number of usable LEDs
#define DEFAULT_MODE 4      ///< Default Mode of Wördclock
#define LED_BRIGHT_EEPROM 4  ///< EEPROM storage for default LED brightness
#define LED_COLORR_EEPROM 5  ///< EEPROM storage for default LED color red
#define LED_COLORG_EEPROM 6  ///< EEPROM storage for default LED color green
#define LED_COLORB_EEPROM 7  ///< EEPROM storage for default LED color blue

/* Select and connect your communication ports */
#define BLUETOOTH0 1  ///< Enable/disable Module Bluetooth, via pin 0,1
#define USBPORT0  1   ///< Enable/disable Serial Communication across usb
#define BLUETOOTH1 0  ///< Enable/disable Module Bluetooth 1
#define BT1TX 9       ///< Connect Arduino Micro pin 9 with HC-06 pin RX
#define BT1RX 8       ///< Connect Arduino Micro pin 8 with HC-06 pin TX
#define BLUETOOTH2 0  ///< Enable/disable Module Bluetooth 2
#define BT2TX 10      ///< Connect Arduino Micro pin 10 with HC-06 pin RX
#define BT2RX 11      ///< Connect Arduino Micro pin 11 with HC-06 pin TX
#define WLAN 0        ///< Enable/disableModule WLAN

#include <Wire.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <FastLED.h>
#include "RTClib.h"
#include "SerialCom.h"
#include "WoerdClockBasics.h"
#include "Sensors.h"
#endif
