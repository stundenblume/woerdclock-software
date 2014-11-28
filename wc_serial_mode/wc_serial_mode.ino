/*
Serial Communication Modul for Wördclock v0.4b by Marcel Müller
based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz

ToDo:
-before we implement this to woerdclock.ino
-we have to clearify the usage of all the serial ports, any idea?
-- actually, we have three ways for serial communication and I realized all:
--- serial across usb, see Serial_interprete() with "Serial"
--- serial across bluetooth with TX,RX on pin 0,1, see Serial1_interprete() with "Serial1"
--- serial across bluetooth with TX,RX on other pins via SoftSerial, see BTSerial_interprete() with "BTSerial" - here pin 4,5
-because of memory size, we should use only one solution

Jobs of this modul:
check if serial communication is available
- via usb, then use usb
- via bluetooth, then use bluetooth
- via WiFi, then use WiFi
if no communication is available, do something else in the loop

In version 0.1, 0.2, 0,3 usb serial only
Since version 0.4b with bluetooth

/*
Tested with Arduino IDE 1.5.7
 
Implemented commands are
  show = show status
  help = help text
  
  slb = set_led_brightness (store in SRAM)
  glb = get_led_brightness (get from SRAM)
  
  slbp = set_led_brightness_permanent (store in EEPROM)
  glbp = get_led_brightness_permanent (get from EEPROM)
  
  slc = set_led_color (store in SRAM)
  glc = get_led_color (get from SRAM)
  
  slcp = set_led_color_permanent (store in EEPROM)
  glcp = get_led_color_permanent (get from EEPROM)
*/

#include <SoftwareSerial.h>
#include <avr/pgmspace.h>     // to use progmem to store arrays in Flash Memory instead of SRAM
#include <EEPROM.h>
//#include <EEPROMVar.h>        // to use EEPROMex - version 0.1 only
//#include <EEPROMex.h>         // to store different data types to EEPROM -version 0.1 only, actually byte only


/*
  Serial is for serial communication across usb
  Serial1 is for serial communication across bluetooth via pin 0,1
  BTSerial with SoftwareSerial is for serial communication across bluetooth via SoftSerial
*/

long BAUDRATE = 57600;                                // default Baudrate for serial communication

/*SoftSerial*/
//#define BTrxPin 9
//#define BTtxPin 8
//SoftwareSerial BTSerial(BTrxPin, BTtxPin);
SoftwareSerial BTSerial(9,8);

/* Start command definitions for serial communication*/
/*
  paraCount defines the maximum number of command and parameters
  paraLength defines the maximum length for commands and parameters (paraLength = max command/parameter length +1)
  cmdCount defines the number of entities
  cmdStrCon defines the commands in lower case!!
*/

const byte  paraCount = 4;                            // max quantity of parameter (incl. command) per line    slc = r,g,b
const byte  paraLength = 5;                           // max length per parameter/command (-1)                 help,show
const byte  cmdCount = 10;                            // quantity of possible commands                        show to slcp
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
};

char       cmdStr[paraCount*paraLength+paraCount+1]; //buffer for complete line of comand and parameter
int        cmdStrIn=0;                               //index for the cmdStr 
char       cmd[paraCount][paraLength];               //arry with command and parameters
/* End command definitons for serial communication */



boolean showvalues;
byte LEDbright = EEPROM.read(0);
byte LEDcolorR = EEPROM.read(1);
byte LEDcolorG = EEPROM.read(2);
byte LEDcolorB = EEPROM.read(3);
unsigned long  serialTime;



void setup()
{
/* You need this in your setup */
  BAUDRATE = 57600;

  int i;

  Serial.begin(BAUDRATE);       // initialize serial port for usb
  //Serial1.begin(BAUDRATE);      // initialize serial port for bluetooth pin 0,1
  BTSerial.begin(BAUDRATE);     // initialize SoftSerial port for bluetooth pin 4,5
  
  for(i=0; i++; i<paraCount)
    cmd[i][0]='\0';
/* You need this in your setup */
}



void loop()
{
  /* The functions are the same, but they use different serial ports */
  //Serial1_interprete(); // interprete command from bluetooth
  //Serial_interprete(); // interprete commands from serial usb
  BTSerial_interprete(); // interprete commands from bluetooth
  
  /* send data for maintenance, if show=1
  if(showvalues)
  {
    if(millis()>serialTime)
    {
      //Print status
      serialTime+=3000;
    }
  }
*/

}


