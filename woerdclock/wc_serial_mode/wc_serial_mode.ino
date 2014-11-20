/*
Serial Communication Modul for Wördclock v0.3 by Marcel Müller
based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz

ToDo:
-before we implement this to woerdclock.ino
-- we have to clearify the usage of all the serial ports, any idea?
-- and how we can use more than one serial port

Jobs:
check if serial communication is available
- via usb, then use usb
- via bluetooth, then use bluetooth
- via WiFi, then use WiFi
if no communication is available, do something else in the loop

In version 0.1, 0.2, 0,3 usb serial only
/* 
  version 0.1
  Der Sketch verwendet 8.486 Bytes (29%) des Programmspeicherplatzes. Das Maximum sind 28.672 Bytes.
  Globale Variablen verwenden 405 Bytes (15%) des dynamischen Speichers, 2.155 Bytes für lokale Variablen verbleiben. Das Maximum sind 2.560 Bytes.
*/

/* 
  version 0.2
  Der Sketch verwendet 8.150 Bytes (28%) des Programmspeicherplatzes. Das Maximum sind 28.672 Bytes.
  Globale Variablen verwenden 278 Bytes (10%) des dynamischen Speichers, 2.282 Bytes für lokale Variablen verbleiben. Das Maximum sind 2.560 Bytes.
*/

/* 
  version 0.3
  serial_interprete() as standalone function for serial communication
*/

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


#include <avr/pgmspace.h>     // to use progmem to store arrays in Flash Memory instead of SRAM
//#include <EEPROMVar.h>        // to use EEPROMex - version 0.1 only
//#include <EEPROMex.h>         // to store different data types to EEPROM -version 0.1 only
#include <EEPROM.h>


/* Start command definitions for serial communication*/
/*
  paraCount defines the maximum number of command and parameters
  paraLength defines the maximum length for commands and parameters (paraLength = max command/parameter length +1)
  cmdCount defines the number of entities
  cmdStrCon defines the commands in lower case!!
*/

long BAUDRATE = 9600;                                // default Baudrate for serial communication
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
  BAUDRATE = 9600;

  int i;

  Serial.begin(BAUDRATE);                        // initialize serial port to send and receive at xxxxx baud
  for(i=0; i++; i<paraCount)
    cmd[i][0]='\0';
/* You need this in your setup */
}



void loop()
{

  serial_interprete();

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



void serial_interprete(void)
{
  /* Serial communication start */
  int i,j,k;

  if(Serial.available()){                   // check to see if at least one character is available
    char ch=Serial.read();
    Serial.print(ch);                       // echo
    if(int(ch)>32)                          // ignore spaces 
      cmdStr[cmdStrIn++]=ch;
    cmdStr[cmdStrIn]='\0';
    if((ch=='\n')||(ch=='\r')){            // end of commandline
      i=0; 
      j=0; 
      k=0;                                 // split the commandline in command and parameters
      Serial.println();      
      while(cmdStr[i]&&(j<paraCount)){
        if((cmdStr[i]!='=')&&(cmdStr[i]!=',')){
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
      do{                                   // commands are not case sensitive
        cmd[0][i]=tolower(cmd[0][i]);
      }
      while(cmd[0][i++]);
      j=-1;    
      for(i=0; i<cmdCount; i++){
        if(!strcmp(cmd[0],cmdStrCon[i]))
          j=i;
      }
      switch(j){

      case  0: 
//show = show status
        if (cmd[1][0]=='0')
          showvalues=false;
        if (cmd[1][0]=='1')
          showvalues=true;
        break;

      case  1: 
//help = help text
        printhelptext();
        break;
        
      case  2: 
//slb = set_led_brightness (store in SRAM)
	if(cmd[1][0]){
	LEDbright = atoi(cmd[1]);
        }
        break;

      case  3: 
//glb = get_led_brightness (get from SRAM)
	Serial.println(LEDbright);
        break;

      case  4: 
//slbp = set_led_brightness_permanent (store in EEPROM)
	EEPROM.write(0, LEDbright);
        /*        
        Serial.print("Now, LED brightness is: ");
        Serial.println(EEPROM.read(0));
        */
        break;

      case  5: 
//glbp = get_led_brightness_permanent (get from EEPROM)
	Serial.println(EEPROM.read(0));
        break;

      case  6: 
//slc = set_led_color (store in SRAM)
        if(cmd[1][0]){
          LEDcolorR = (double) atof(cmd[1]);
          LEDcolorG = (double) atof(cmd[2]);
          LEDcolorB = (double) atof(cmd[3]);
        }
        break;

      case  7: 
//glc = get_led_color
        Serial.print(LEDcolorR);
        Serial.print(",");
        Serial.print(LEDcolorG);
        Serial.print(",");
        Serial.println(LEDcolorB);
        break;

      case  8: 
//slcp = set_led_color_permanent (store in EEPROM)
        EEPROM.write(1, LEDcolorR);
        EEPROM.write(2, LEDcolorG);
        EEPROM.write(3, LEDcolorB);
        /*
        Serial.print("Now, LED color is: ");
        Serial.print(EEPROM.read(1));
        Serial.print(",");
        Serial.print(EEPROM.read(2));
        Serial.print(",");
        Serial.println(EEPROM.read(3));
        */
        break;

	case 9:
//glcp = get_led_color_permanent (get from EEPROM)
        Serial.print(EEPROM.read(1));
        Serial.print(",");
        Serial.print(EEPROM.read(2));
        Serial.print(",");
        Serial.println(EEPROM.read(3));
	break;
        
      default: 
        if(strlen(cmd[0])){
          Serial.println("error");
        }
      }   
      for(i=0; i<paraCount; i++)                     //reset variables
        cmd[i][0]='\0';
      cmdStr[0]='\0';
      cmdStrIn=0;  
      i=0;  
    }  
  }
  /* Serial communication end */
}



void printhelptext (void)
{
  /* Welcome and help text */
  Serial.print(F("\nWelcome to WordClock Controller Interface\
  \n\r version 0.3\
  \n\r"));
               
  Serial.print(F("\npossible commands are:\
  \n\r show= 0/1      show status off/on\
  \n\r help           help text\
  \n\r slb=0-255 	set led brightness 0-255\
  \n\r glb            get led brightness\
  \n\r slbp           store led brightness permanent\
  \n\r glbp           get permanent led brightness\
  \n\r slc=R,G,B      set led color (R,G,B) (0-255,0-255,0-255)\
  \n\r glc            get led color\
  \n\r slcp           store led color permanent\
  \n\r glcp           get permanent led color\
  \n\r"));
}
