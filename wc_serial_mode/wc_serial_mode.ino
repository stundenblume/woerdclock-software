/* for details see serial_com.ino */

#include <SoftwareSerial.h>
#include <EEPROM.h>

long BAUDRATE = 9600; // default Baudrate for serial communication
byte serial_com_port = 255; // A number to seperate the ports for serial communication from each other
boolean showvalues = false; // For debugging only


/*** Which Modules are installed? ***/
/* NEW */
#define BLUETOOTH0 0 //Module Bluetooth, via pin 0,1 - default=0, because on this port is the led stripe connected
#define USBPORT0 1 // Serial Communication across usb
/* NEW */

/* This block is copied from jan! -> remove this block while merge */
#define RTCLOCK 1     //Module Real Time Clock
#define BUTTON 1     //Button are used
#define LDR 1        //LDR is used
#define DOF 0        //Module 10DOF
#define DCF 0        //Module DCF77
#define SDCARD 0     //Module SD Card
#define MIC 0        //Module Microfon
#define IR 0         //Module IR
#define RFM12 0      //Module RMF12B

#define BLUETOOTH1 1 //Module Bluetooth 1
#define BLUETOOTH2 0 //Module Bluetooth 2
#define WLAN 0       //Module WLAN
#define DHT11 0      //Module DHT11
#define NUM_LEDS 114
/* This block is copied from jan! -> remove this block while merge */
/*** Which Modules are installed? ***/


/* SoftwareSerial for bluetooth - verify the pin numbers */
/* IF you don't use both bluetooth interfaces via softwareserial, you can comment out one of the next two lines to save memory */
#if BLUETOOTH1
SoftwareSerial BTSerial(8, 9); // Connect Arduino Micro pin 9 with HC-06 pin RX and Arduino Micro pin 8 with HC-06 pin TX
#endif
#if BLUETOOTH2
SoftwareSerial BTSerial2(10, 11); // Connect Arduino Micro pin 15 with HC-06 pin RX and Arduino Micro pin 14 with HC-06 pin TX
#endif


/* Dummy variables - @jan: replace these by yours while merge */
boolean LED[NUM_LEDS] = {0};          // this is a dummy array for the LEDs of wordclock 0=off, 1=on
byte LEDbright = EEPROM.read(0); // this is a dummy variable for the LED brightness
byte LEDcolorR = EEPROM.read(1); // this is a dummy variable for the LED color red
byte LEDcolorG = EEPROM.read(2); // this is a dummy variable for the LED color green
byte LEDcolorB = EEPROM.read(3); // this is a dummy variable for the LED color blue
byte mode = 0; // this is a dummy variable for the mode
int dht_temperature = 25; // this is a dummy variable for the temperature from dht sensor
int dht_humidity = 70; // this is a dummy variable for the temperature from dht sensor
long timestamp = 0;  // this is a dummy variable for the date and time in unix time stamp format (see http://playground.arduino.cc/Code/Time )
/* Dummy variables - @jan: replace these by yours while merge */


/* Start command definitions for serial communication - don't touch this 
    based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz */
/*
  paraCount defines the maximum number of command and parameters
  paraLength defines the maximum length for commands and parameters (paraLength = max command/parameter length +1)
  cmdCount defines the number of entities
  cmdStrCon defines the commands in lower case!!
*/
const byte  paraCount = 4;                            // max quantity of parameter (incl. command) per line    slc = r,g,b
const byte  paraLength = 5;                           // max length per parameter/command (-1)                 help,show
const byte  cmdCount = 16;                            // quantity of possible commands                        show to slcp
const char cmdStrCon[cmdCount][paraLength]=
{
  {
    "show"  }
  ,{
    "help"  }
  ,{
    "slb"  }
  ,{
    "glb"  }
  ,{
    "slbp"  }
  ,{
    "glbp"  }
  ,{
    "slc"  }
  ,{
    "glc"  }
  ,{
    "slcp"  }
  ,{
    "glcp"  }
  ,{
    "sled" }
  ,{
    "gled" }
  ,{
    "srtc" }
  ,{
    "gtem" }
  ,{
    "ghum"}
  ,{
    "mode"}
};
char       cmdStr[paraCount*paraLength+paraCount+1]; //buffer for complete line of comand and parameter
int        cmdStrIn=0;                               //index for the cmdStr 
char       cmd[paraCount][paraLength];               //arry with command and parameters
/* End command definitons for serial communication - don't touch this */


void setup()
{
  #if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
  /* You need this in your setup for serial communication */
  for(int i=0; i++; i<paraCount)
  {
    cmd[i][0]='\0';
  }
  
  #if USBPORT0
  Serial.begin(BAUDRATE);       // initialize serial port for usb
  #endif
  
  #if BLUETOOTH0
  Serial1.begin(BAUDRATE);      // initialize serial port for bluetooth
  #endif
  
  #if BLUETOOTH1
  BTSerial.begin(BAUDRATE);     // initialize Software Serial port for bluetooth
  #endif
  
  #if BLUETOOTH2
  BTSerial2.begin(BAUDRATE);    // initialize a second Software Serial port for bluetooth
  #endif 
  /* You need this in your setup  for serial communication */
  #endif
}


void loop()
{
  /* All in one serial communication function to interprete command from any serial port*/
  #if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
  serial_com();
  #endif
}


