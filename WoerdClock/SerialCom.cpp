/**
* @file SerialCom.cpp
* @brief Serial Communication Module for Wördclock
* @details Contains the Serial Communication Module
* @author Marcel Müller
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
* @see SerialCom.h
*
*/
#include "config.h"

#if BLUETOOTH1
  SoftwareSerial BTSerial(BT1RX, BT1TX);    
#endif
  
#if BLUETOOTH2
  SoftwareSerial BTSerial2(BT2RX, BT2TX);
#endif
  
#if WLAN
  
#endif

const char strerror[] = "error";   ///< Error message
const char cmdbreak = '\n';        ///< Symbol of command break/end
const char strwelcome[]  = "\nWelcome to WördClock Controller Interface  \n\r version 0.9b"; ///< Welcome text
const char strhelp1[] = 
  "\n Possible commands are:"
  "\n\r help           help text"
  "\n\r slb=0-255      set led brightness 0-255"
  "\n\r glb            get led brightness"
  "\n\r slbp           store led brightness permanent"
  "\n\r glbp           get permanent led brightness"
  "\n\r slc=R,G,B      set led color (R,G,B) (0-255)"
  "\n\r glc            get led color"; ///< Help text / Command reference part 1
const char strhelp2[] =
  "\n\r slcp           store led color permanent"
  "\n\r glcp           get permanent led color"
  "\n\r sled=No,R,G,B  set led by number with RGB color code"
  "\n\r srtc           set unix time stamp for clock"
  "\n\r grtc           get unix time stamp and time from clock"; ///< Help text / Command reference part 2
const char strhelp3[] =
  "\n\r gtem           get temperature"
  "\n\r ghum           get humidity"
  "\n\r smod           set the mode"
  "\n\r gmod           get the mode\n"; ///< Help text / Command reference part 3


const byte  paraCount = 5;                            ///< Max quantity of parameter (incl. command) per line; slc = NR,r,g,b.
/**< paraCount defines the maximum number of command and parameters. */
const byte  paraLength = 11;                          ///< Max length per parameter/command (-1); 11 chars for timestamp.
/**< paraLength defines the maximum length for commands and parameters (paraLength = max command/parameter length +1). */
const byte  cmdCount = 17;                            ///< Quantity of possible commands; from show=1 to gmod=17.
/**< cmdCount defines the number of entities. */
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
    "smod"}  
  ,{
    "gmod"}
};
/**<  cmdStrCon Defines the commands in lower case!! */
char       cmdStr[paraCount*paraLength+paraCount+1]; ///< Buffer for complete line of comand and parameter
int        cmdStrIn=0;                               ///< Index for the cmdStr 
char       cmd[paraCount][paraLength];               ///< Array with command and parameters


/********************************************//**
 * @brief Constructor for Serial Communication Module
 * @details Set default values for Serial Communication Module and initialize the ports
 *
 * Initialize hardware serial port for usb. 
 * Initialize hardware serial port for bluetooth. 
 * Initialize software serial port for bluetooth. 
 * Initialize a second software serial port for bluetooth. 
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
SerialCom::SerialCom() // Constructor
{ 
  BAUDRATE=57600;
  debug = false;
  debugpreviousmillis = 0;
  debuginterval = 1000; 
  port = 255;
  
  for(int i=0; i++; i<paraCount)
  {
    cmd[i][0]='\0';
  }
  
  #if USBPORT0
    Serial.begin(BAUDRATE);       
  #endif
  
  #if BLUETOOTH0
    Serial1.begin(BAUDRATE);      
  #endif
  
  #if BLUETOOTH1
    BTSerial.begin(BAUDRATE);     
  #endif
  
  #if BLUETOOTH2
    BTSerial2.begin(BAUDRATE);    
  #endif 
}

/********************************************//**
 * @brief Object reference to wordclock properties
 * @details To use members of WoerdClockBasics with SerialCom
 * @author Marcel Müller
 * @author Marc Rochler
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::setWoerdClock(WoerdClockBasics* wc)
{
  woerdclock=wc;
}

void SerialCom::setSensors(Sensors* sens)
{
  sensors=sens;
}

/********************************************//**
 * @brief Execute of Serial Communication
 * @details Executes SerialCom with character read, command parse, command interprete, response
 * Run execute in your sketch where you need the serial communication.
 * E.g. in the loop of your sketch.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::execute(void)
{
  do
  {
    checkports();
    int command=-2;
    command = parse();
    
    if(command>=0)
    {
      interprete(command);
      clean();
    }
    if(command==-1)
    {
      errormsg();
      clean();
    }
  }while(port!=255);
  debugmode();
}

/********************************************//**
 * @brief Port checker to check the ports for serial communication
 * @details The last checked port which contains a character inside its buffer will be used for the serial communication.
 * A default port is not set. The default value is 255 to prevent the ports from undesired messages.
 * Ports: USB-Port (Serial), Pin 0,1 (Serial1), Bluetooth via Software Serial, WiFi,...
 * For Software Serial consider interupt pins.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::checkports(void)
{
  port = 255;
  
  #if USBPORT0
  if(Serial.available()>0)
  {
    port = 0;
  }
  #endif
  
  #if BLUETOOTH0
  if(Serial1.available()>0)
  {
    port = 1;
  }
  #endif
  
  #if WLAN
  //  if(wifi.available())
  //  {
  //    port = 4;
  //  }
  #endif
  
  #if BLUETOOTH1 && BLUETOOTH2
  BTSerial.listen();
  #endif
  
  #if BLUETOOTH1
  if(BTSerial.available()>0)
  {
    port = 2;
  }
  #endif

  #if BLUETOOTH1 && BLUETOOTH2
  BTSerial2.listen();
  #endif
  
  #if BLUETOOTH2
  while(BTSerial2.available()>0)
  {
    port = 3;
  }
  #endif
  
//  return port;
}

/********************************************//**
 * @brief Parser of Serial Communication Module
 * @details Parses the incomming/readed characters.
 * The parser logic based on "parser for serial communication on Arduino by (c) 140801 Thomas Peetz" and was modified.
 * @copyright Original Copyright 140801 Thomas Peetz. All rights reserved.
 * @return 
 * If the parsed command was found in cmdStrCon, it returns the number of this entry.
 * If the command was not found but the command was completed, it returns -1.
 * If the command was not found because the command isn't complete, it returns -2.
 * @author Original: Thomas Peetz
 * @author Modifications: Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
int SerialCom::parse(void)
{
  int i,j,k;
  if(port<4)
  {
    char ch=read();
//Serial.print(ch);                         // echo characters to USB0
    if(int(ch)>32)                          // ignore spaces 
      cmdStr[cmdStrIn++]=ch;
    cmdStr[cmdStrIn]='\0';
    if((ch=='\n')||(ch=='\r'))
    {            // end of commandline
      i=0; 
      j=0; 
      k=0;                                 // split the commandline in command and parameters
//Serial.println();      
      while(cmdStr[i]&&(j<paraCount))
      {
        if((cmdStr[i]!='=')&&(cmdStr[i]!=','))
        {
          if(k<paraLength-1){
            cmd[j][k++]=cmdStr[i];
            cmd[j][k]='\0';
          }  
        }
        else{
          j++; 
          k=0;
        }
        i++;
      }
      i=0;
      do
      {                                   // commands are not case sensitive
        cmd[0][i]=tolower(cmd[0][i]);
      }
      while(cmd[0][i++]);
      j=-1;    
      for(i=0; i<cmdCount; i++)
      {
        if(!strcmp(cmd[0],cmdStrCon[i]))
          j=i;
      }
      return j;
    }  
  }
  return -2;
}

/********************************************//**
 * @brief Command cleaner
 * @details Cleans the command buffer for new command interpretation.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::clean(void)
{
  int i;
  for(i=0; i<paraCount; i++)
    cmd[i][0]='\0';
  cmdStr[0]='\0';
  cmdStrIn=0;  
  i=0;  
}

/********************************************//**
 * @brief Interpreter of Serial Communication Module
 * @details Interpretes the parsed characters.
 * Depends on the input, the interpreter runs a function.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::interprete(int j)
{
  switch(j)
      {
      case  0: //show = show status; This is for debugging only
        if (cmd[1][0]=='0')
          debug=false;
        if (cmd[1][0]=='1')
          debug=true;
        debugPort=port;
      break;

      case  1:
        welcome();
        help();
      break;
        
      case  2:
	slb();
      break;

      case  3:
        glb(j);
      break;

      case  4:
	slbp();
      break;

      case  5:
        glbp(j);
      break;

      case  6:
        slc();
      break;

      case  7:
        glc(j);
      break;

      case  8:
        slcp();
      break;

      case 9:  
        glcp(j);
      break;
      
      case 10:
        sled();
      break;     

      case 11:
        gled(j);
      break;

      case 12:
        srtc();
      break;

      case 13:
      #if DHT11
        gt(j);
      #endif
      break;

      case 14:
      #if DHT11
        gh(j);
      #endif
      break;

      case 15:
        smod();
      break;
      
      case 16:
        gmod(j);
      break;         
        
      default: 
        break;
      }
}

/********************************************//**
 * @brief Serial Reader of Serial Communication Module
 * @details Read characters from the serial interfaces
 * @return Returns the readed characters
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
char SerialCom::read()
{
  char ch;
  switch(port)
  {
    #if USBPORT0
    case 0: // read from usb
    if(Serial.available()>0)
    {                   
      ch=Serial.read();
      return ch;
    }
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // read from pin 0,1
    if(Serial1.available()>0)
    {                   
      ch=Serial1.read();
      return ch;
    }
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // read via bluetooth 1
    if(BTSerial.available()>0)
    {                   
      ch=BTSerial.read();
      return ch;
    }
    break;
    #endif

    #if BLUETOOTH2   
    case 3: // read via bluetooth 2
      if(BTSerial2.available()>0)
      {                   
        ch=BTSerial2.read();
        return ch;
      }
    break;
    #endif
    
    #if WLAN
    case 4: // read via wifi
    //    wifi.print
    break;
    #endif
  }
}

/********************************************//**
 * @brief Serial Printer for values
 * @details Prints a byte to a serial interface.
 * Before using set port with the desired value.
 * @param The value to print
 * @see void SerialCom::checkports(void)
 * @see port
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::print(byte value)
{
  value=(int)value;
  switch(port)
  {
    #if USBPORT0
    case 0: // print via usb
      Serial.print(value);
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // print via pin 0,1
      Serial1.print(value);
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // print via bluetooth 1
      BTSerial.print(value);
    break;
    #endif
    
    #if BLUETOOTH2    
    case 3: // print via bluetooth 2
      BTSerial2.print(value);
    break;
    #endif
    
    #if WLAN
    case 4: // print via wifi
    //    wifi.print
    break;
    #endif
  }
}

/********************************************//**
 * @brief Serial Printer for values
 * @details Prints an Integer to a serial interface.
 * @param The value to print
 * @see void SerialCom::checkports(void)
 * @see port
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::print(int value)
{
  switch(port)
  {
    #if USBPORT0
    case 0: // print via usb
      Serial.print(value);
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // print via pin 0,1
      Serial1.print(value);
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // print via bluetooth 1
      BTSerial.print(value);
    break;
    #endif
    
    #if BLUETOOTH2    
    case 3: // print via bluetooth 2
      BTSerial2.print(value);
    break;
    #endif
    
    #if WLAN
    case 4: // print via wifi
    //    wifi.print
    break;
    #endif
  }
}

/********************************************//**
 * @brief Serial Printer for characters
 * @details Prints a character to a serial interface.
 * @param The character to print
 * @see void SerialCom::checkports(void)
 * @see port
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::print(char value)
{
  switch(port)
  {
    #if USBPORT0
    case 0: // print via usb
      Serial.print(value);
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // print via pin 0,1
      Serial1.print(value);
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // print via bluetooth 1
      BTSerial.print(value);
    break;
    #endif
    
    #if BLUETOOTH2
    case 3: // print via bluetooth 2
      BTSerial2.print(value);
    break;
    #endif
    
    #if WLAN
    case 4: // print via wifi
    //    wifi.print
    break;
    #endif
  }
}

/********************************************//**
 * @brief Serial Printer for strings
 * @details Prints characters/strings to a serial interface.
 * @param The character to print
 * @see void SerialCom::checkports(void)
 * @see port
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::print(char str[])
{
  for(int i=0 ; i<strlen(str) ; i++)
  {
    switch(port)
    {
      #if USBPORT0
      case 0: // print via usb
        Serial.print(str[i]);
      break;
      #endif
      
      #if BLUETOOTH0
      case 1: // print via pin 0,1
        Serial1.print(str[i]);
      break;
      #endif
      
      #if BLUETOOTH1
      case 2: // print via bluetooth 1
        BTSerial.print(str[i]);
      break;
      #endif
      
      #if BLUETOOTH2
      case 3: // print via bluetooth 2
        BTSerial2.print(str[i]);
      break;
      #endif
      
      #if WLAN
      case 4: // print via wifi
      //    wifi.print
      break;
      #endif
    }
  }
}

/********************************************//**
 * @brief Serial Printer for const strings
 * @details Prints const strings to a serial interface.
 * @param The string to print
 * @see void SerialCom::checkports(void)
 * @see port
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::print(const char *str)
{
  for(int i=0 ; i<strlen(str) ; i++)
  {
    switch(port)
    {
      #if USBPORT0
      case 0: // print via usb
        Serial.print(str[i]);
      break;
      #endif
      
      #if BLUETOOTH0
      case 1: // print via pin 0,1
        Serial1.print(str[i]);
      break;
      #endif
      
      #if BLUETOOTH1
      case 2: // print via bluetooth 1
        BTSerial.print(str[i]);
      break;
      #endif
      
      #if BLUETOOTH2
      case 3: // print via bluetooth 2
        BTSerial2.print(str[i]);
      break;
      #endif
      
      #if WLAN
      case 4: // print via wifi
      //    wifi.print
      break;
      #endif
    }
  }
}

/* ************************************************************************ */

/********************************************//**
 * @brief Serial Printer for values with line end
 * @details Prints a byte to a serial interface
 * and ends the line. See e.g. Serial.println().
 * @param The value to print
 * @see void SerialCom::println(void)
 * @see void SerialCom::print(byte value)
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::println(byte value)
{
  print(value);
  println();
}

/********************************************//**
 * @brief Serial Printer for values with line end
 * @details Prints an Integer to a serial interface
 * and ends the line. See e.g. Serial.println().
 * @param The value to print
 * @see void SerialCom::println(void)
 * @see void SerialCom::print(int value)
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::println(int value)
{
  print(value);
  println();
}

/********************************************//**
 * @brief Serial Printer for characters with line end
 * @details Prints a character to a serial interface
 * and ends the line. See e.g. Serial.println().
 * @param The character to print
 * @see void SerialCom::println(void)
 * @see void SerialCom::print(char value)
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::println(char value)
{
  print(value);
  println();
}

/********************************************//**
 * @brief Serial Printer for strings with line end
 * @details Prints characters/strings to a serial interface
 * and ends the line. See e.g. Serial.println().
 * @param The character to print
 * @see void SerialCom::println(void)
 * @see void SerialCom::print(char str[])
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::println(char str[])
{
  print(str);
  println();
}

/********************************************//**
 * @brief Serial Printer for const strings
 * @details Prints const strings to a serial interface.
 * @param The string to print
 * @see void SerialCom::checkports(void)
 * @see port
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::println(const char *str)
{
  print(str);
  println();
}

/********************************************//**
 * @brief Serial Printer for line end
 * @details Prints a line end to a serial interface
 * @see port
 * @param The character to print
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::println(void)
{
  switch(port)
  {
    #if USBPORT0
    case 0: // print via usb
      Serial.println();
    break;
    #endif
      
    #if BLUETOOTH0
    case 1: // print via pin 0,1
      Serial1.println();
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // print via bluetooth 1
      BTSerial.println();
    break;
    #endif
      
    #if BLUETOOTH2
    case 3: // print via bluetooth 2
      BTSerial2.println();
    break;
    #endif
      
    #if WLAN
    case 4: // print via wifi
    //    wifi.print
    break;
    #endif
  }  
}


/********************************************//**
 * @brief Serial Printer for commands
 * @details It prints the command to the serial port.
 * E.g.: 
 * you check led color status with "glc" (=get led color)
 * than you get the answer:
 * "lc=R,G,B".
 * @details The string "lc=" is generated by this function to save memory.
 * The first letter of the command will be ignored: glc -> lc=
 * @param The character to print
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::print_cmd(int j)
{
  for(int i=1; i<sizeof(cmdStrCon[j])-1 ; i++)
  {
    if(cmdStrCon[j][i]!='\0')
    {
      print(cmdStrCon[j][i]);
    }
  }
  print('=');
}

/********************************************//**
 * @brief Debugging mode to show all values 
 * @details If show=1, every second all values are printed
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::debugmode()
{
  if(debug)
  {
  port=debugPort;
  unsigned long debugcurrentmillis = millis();
  if(debugcurrentmillis - debugpreviousmillis > debuginterval) 
  {
    debugpreviousmillis = debugcurrentmillis;
    if(debug==true)
    {   
      println("Debug");
      
      print("Mode: ");
      println(woerdclock->displayMode);
      
      print("LED (R,G,B): ");
      print(woerdclock->LEDcolorR);
      print(',');
      print(woerdclock->LEDcolorG);
      print(',');
      println(woerdclock->LEDcolorB);
      
      print("Time: ");
      print(woerdclock->h);
      print(':');
      print(woerdclock->m);
      print(':');
      println(woerdclock->s);
            
#if DHT11
      if (isnan(sensors->humi) || isnan(sensors->temp)) 
      {
        println("Failed to read from DHT sensor!");
      }
      else
      {
        print("DHT11 Temp: ");
        println(sensors->temp);
        print("DHT11 Humi: ");
        println(sensors->humi);
      }
#endif

      println("Exit with show=0");
      println();

    } 
  }
  port=255;
  }
}

/********************************************//**
 * @brief Welcome Message
 * @details Prints a welcome message
 * to the requesting serial interface.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::welcome()
{
  #if HELPMSG
  print(strwelcome);
  #endif 
}

/********************************************//**
 * @brief Welcome Message
 * @details Prints a help text containing all commands are available
 * to the requesting serial interface.
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::help()
{
  #if HELPMSG
  print(strhelp1);
  print(strhelp2);
  print(strhelp3);
  #endif
}

/********************************************//**
 * @brief set led brightness
 * @details Store led brightness in SRAM
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::slb()
{
  if(cmd[1][0])
  {
    woerdclock->LEDbright = atoi(cmd[1]);
  }
}

/********************************************//**
 * @brief get led brightness
 * @details Get led brightness stored in SRAM
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::glb(int j)
{
  print_cmd(j);
  print(woerdclock->LEDbright);
  print(cmdbreak);
}

/********************************************//**
 * @brief set led brightness permanent
 * @details Store led brightness (from SRAM) to EEPROM
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::slbp()
{
  EEPROM.write(LED_BRIGHT_EEPROM, woerdclock->LEDbright);
}

/********************************************//**
 * @brief get led brightness permanent
 * @details Get led brightness from EEPROM
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::glbp(int j)
{
  print_cmd(j);
  print(EEPROM.read(LED_BRIGHT_EEPROM));
  print(cmdbreak);
}

/********************************************//**
 * @brief set led color
 * @details Store led colors (RGB) in SRAM
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::slc()
{
  if(cmd[1][0])
  {
    woerdclock->LEDcolorR = (double) atof(cmd[1]);
    woerdclock->LEDcolorG = (double) atof(cmd[2]);
    woerdclock->LEDcolorB = (double) atof(cmd[3]);
  }
  FastLED.show();
}

/********************************************//**
 * @brief get led color
 * @details Get led colors (RGB) stored in SRAM
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::glc(int j)
{
  print_cmd(j);
  print(woerdclock->LEDcolorR);
  print(',');
  print(woerdclock->LEDcolorG);
  print(',');
  print(woerdclock->LEDcolorB);
  print(cmdbreak);
}

/********************************************//**
 * @brief set led color permanent
 * @details Store led colors (RGB) (from SRAM) to EEPROM
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::slcp()
{
  EEPROM.write(LED_COLORR_EEPROM, woerdclock->LEDcolorR);
  EEPROM.write(LED_COLORG_EEPROM, woerdclock->LEDcolorG);
  EEPROM.write(LED_COLORB_EEPROM, woerdclock->LEDcolorB);
}

/********************************************//**
 * @brief get led color permanent
 * @details Get led colors (RGB) from EEPROM
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::glcp(int j)
{
  print_cmd(j);
  print(EEPROM.read(LED_COLORR_EEPROM));
  print(',');
  print(EEPROM.read(LED_COLORG_EEPROM));
  print(',');
  print(EEPROM.read(LED_COLORB_EEPROM));
  print(cmdbreak);
}

/********************************************//**
 * @brief set led color
 * @details Set a particular led with a color
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::sled()
{
  woerdclock->leds[atoi(cmd[1])] = CRGB(atoi(cmd[2]), atoi(cmd[3]), atoi(cmd[4]));
  FastLED.show();
}

/********************************************//**
 * @brief get leds colors
 * @details Get all the colors of all leds
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::gled(int j)
{
  for(int i=0 ; i<NUM_LEDS ; i++)
  {
    print_cmd(j);
    print(i);
    print(',');
    print(woerdclock->leds[i].r);
    print(',');
    print(woerdclock->leds[i].g);
    print(',');
    print(woerdclock->leds[i].b);
    print(cmdbreak);
  }
}

/********************************************//**
 * @brief set real time clock
 * @details Set the real time clock with the timestamp
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::srtc()
{
  woerdclock->timestamp=atol(cmd[1]);
}

/********************************************//**
 * @brief get temperature
 * @details Get the temperature from DHT11
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::gt(int j)
{
  #if DHT11
  print_cmd(j);
  print(sensors->temp);
  print(cmdbreak);
  #endif
}

/********************************************//**
 * @brief get humidity
 * @details Get the humidity from DHT11
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::gh(int j)
{
  #if DHT11
  print_cmd(j);
  print(sensors->humi);
  print(cmdbreak);
  #endif
}

/********************************************//**
 * @brief set mode
 * @details Set/Select an other mode
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::smod()
{
  woerdclock->displayMode=atoi(cmd[1]);
/*
  switch(displayMode){
   case 1: 
     delete(currentView); 
     currentView = new BinaryView();
     break;
   case 2: 
     delete(currentView); 
     currentView = new AnalogView();
     break;
   case 4: 
     delete(currentView); 
     currentView = new WoerdClockView();
     break;
   case 3: 
     delete(currentView); 
     currentView = new SegmentView();
     break;
   default: break;
  }
*/
}

/********************************************//**
 * @brief get mode
 * @details Get the number of the actual mode
 * and print to the requesting serial interface.
 * @param Number of command
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::gmod(int j)
{
  print_cmd(j);
  print(woerdclock->displayMode);
  print(cmdbreak);
}

/********************************************//**
 * @brief Error Message
 * @details Print error to the serial interface
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
void SerialCom::errormsg()
{
  println(strerror);
}

/********************************************//**
 * @brief Dummy Member
 * @details Example for a new member.
 * Inkrements the over handed byte value.
 * @param A byte value
 * @return The byte value + 1
 * @author Marcel Müller
 * @date 10.01.2015
 * @version 0.1
 ***********************************************/
byte SerialCom::dummy(byte var)
{
  var+=1;
  return var;
}
