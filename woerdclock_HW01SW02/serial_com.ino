/* Serial Communication Modul for Wördclock v0.72 by Marcel Müller
   Developed with Arduino IDE 1.5.7 on Arduino Pro Micro and Arduino Yun

  This program comes with absolutely no warranty. Use at your own risk
  
  Jobs of this modul:
    check if serial communication is available
    [x] via usb
    [x] via bluetooth
      [x] hardware serial pin 0,1
      [x] software serial
    [-] via WiFi (not implemented)
    if no communication is available, do something else in the loop
    
    if communication is available, this module seperate commands from parameters
    interprete this and do something
    
  ToDo
    select your connected hardware
    verify the software serial pins
    
  Bug
    actually, it is not possible to use two software serial ports at the same time
*/

/* Serial communication */
#if GENSERIAL
void serial_com(void)
{
  /* Check which port is actually available 
      This is realy primitive, because there is a ranking.
      If usb send permanent data, bluetooth will be ignored.
      If you dislike this, we need a state machine.
  */
  //DEBUG_PRINT(F("Serial logic"));
  serial_com_port = 255; //default, means no port
  
  #if USBPORT0
  while(Serial.available()>0)
  {
    serial_com_port = 0;
    serial_interprete();
  }
  serial_com_port = 255;
  #endif
  
  #if BLUETOOTH0
  while(Serial1.available()>0)
  {
    serial_com_port = 1;
    serial_interprete();
  }
  serial_com_port = 255;
  #endif
  
  #if WLAN
  //  if(wifi.available())
  //  {
  //    serial_com_port = 4;
  //  }
  #endif
  
  #if BLUETOOTH1 && BLUETOOTH2
  BTSerial.listen();
  #endif
  
  #if BLUETOOTH1
  while(BTSerial.available()>0)
  {
    serial_com_port = 2;
    serial_interprete();
  }
  serial_com_port = 255;
  #endif

  #if BLUETOOTH1 && BLUETOOTH2
  BTSerial2.listen();
  #endif
  
  #if BLUETOOTH2
  while(BTSerial2.available()>0)
  {
    serial_com_port = 3;
    serial_interprete();
  }
  serial_com_port = 255;
  #endif
} 
#endif

/* Interpreter */
/* based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz */
#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
void serial_interprete()
{
  int i,j,k;
  if(serial_com_port<4){                   // check to see if at least one character is available
    char ch=read_serial();
    //Serial.print(ch);                       // echo
    if(int(ch)>32)                          // ignore spaces 
      cmdStr[cmdStrIn++]=ch;
    cmdStr[cmdStrIn]='\0';
    if((ch=='\n')||(ch=='\r')){            // end of commandline
      i=0; 
      j=0; 
      k=0;                                 // split the commandline in command and parameters
      //Serial.println();      
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

      case  0: //show = show status
     /*
      This is for debugging only
     */ 
        if (cmd[1][0]=='0')
          showvalues=false;
        if (cmd[1][0]=='1')
          showvalues=true;
      break;

      case  1: //help = welcome + help text
        for(int i=0; i<sizeof(strwelcome)-1 ; i++)
        {
          write_serial_str(strwelcome[i]);
        }
        
        for(int i=0 ; i<sizeof(strhelp1)-1 ; i++)
        {
          write_serial_str(strhelp1[i]);
        }
        
        for(int i=0 ; i<sizeof(strhelp2)-1 ; i++)
        {
          write_serial_str(strhelp2[i]);
        }
       
        for(int i=0 ; i<sizeof(strhelp3)-1 ; i++)
        {
          write_serial_str(strhelp3[i]);
        }
 
        break;
        
      case  2: //slb = set_led_brightness (store in SRAM)
	if(cmd[1][0])
        {
	  LEDbright = atoi(cmd[1]);
        }
      break;

      case  3: //glb = get_led_brightness (get from SRAM)
        write_serial_cmd(j);
	write_serial(LEDbright);
        write_serial_str(cmdbreak);
        break;

      case  4: //slbp = set_led_brightness_permanent (store in EEPROM)
	EEPROM.write(4, LEDbright);
      break;

      case  5: //glbp = get_led_brightness_permanent (get from EEPROM)
        write_serial_cmd(j);
        write_serial(EEPROM.read(4));
        write_serial_str(cmdbreak);
      break;

      case  6: //slc = set_led_color (store in SRAM)
        if(cmd[1][0])
        {
          LEDcolorR = (double) atof(cmd[1]);
          LEDcolorG = (double) atof(cmd[2]);
          LEDcolorB = (double) atof(cmd[3]);
        }
      break;

      case  7: //glc = get_led_color
        write_serial_cmd(j);
        write_serial(LEDcolorR);
        write_serial_str(paramseperator);
        write_serial(LEDcolorG);
        write_serial_str(paramseperator);
        write_serial(LEDcolorB);
        write_serial_str(cmdbreak);
      break;

      case  8: //slcp = set_led_color_permanent (store in EEPROM)
        EEPROM.write(5, LEDcolorR);
        EEPROM.write(6, LEDcolorG);
        EEPROM.write(7, LEDcolorB);
      break;

      case 9: //glcp = get_led_color_permanent (get from EEPROM)
        write_serial_cmd(j);
        write_serial(EEPROM.read(5));
        write_serial_str(paramseperator);
        write_serial(EEPROM.read(6));
        write_serial_str(paramseperator);
        write_serial(EEPROM.read(7));
        write_serial_str(cmdbreak);
      break;

      case 10: //sled = set_led on/off
        if (cmd[2][0]=='0')
          LED[atoi(cmd[1])]=0;
        if (cmd[2][0]=='1')
          LED[atoi(cmd[1])]=1;
      break;
      
      case 11: //gled = get_led
        write_serial_cmd(j);
        for(int i=0 ; i<sizeof(LED) ; i++)
        {
          write_serial(LED[i]);
          if(i<sizeof(LED)-1)
          {
            write_serial_str(paramseperator);
          }
        }
        write_serial_str(cmdbreak);
      break;

      case 12: //srtc = set_real_time_clock
        timestamp=atoi(cmd[1]);
      break;

      #if DHT11
      case 13: //gt = get temperature
        write_serial_cmd(j);
        write_serial(temp);
        write_serial_str(cmdbreak);
      break;

      case 14: //gh = get humidity
        write_serial_cmd(j);
        write_serial(humi);
        write_serial_str(cmdbreak);
      break;
      #endif

      case 15: //mode = set a mode
        displayMode=atoi(cmd[1]);
      break;
        
        
      default: 
        if(strlen(cmd[0]))
        {
          for(int i=0 ; i<sizeof(strerror)-1 ; i++)
          {
            write_serial_str(strerror[i]);
          }
          write_serial_str(cmdbreak);
        }
      }   
      for(i=0; i<paraCount; i++)                     //reset variables
        cmd[i][0]='\0';
      cmdStr[0]='\0';
      cmdStrIn=0;  
      i=0;  
    }  
  
  /* Serial communication end */
  }
}
#endif




/* read a char from the serial interfaces */
#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
char read_serial()
{
  char ch;
  switch(serial_com_port)
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
#endif

/* write a number/value to the serial interfaces */
#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
void write_serial(int value)
{
  switch(serial_com_port)
  {
    #if USBPORT0
    case 0: // write via usb
      Serial.print(value);
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // write via pin 0,1
      Serial1.print(value);
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // write via bluetooth 1
      BTSerial.print(value);
    break;
    #endif
    
    #if BLUETOOTH2    
    case 3: // write via bluetooth 2
      BTSerial2.print(value);
    break;
    #endif
    
    #if WLAN
    case 4: // write via wifi
    //    wifi.print
    break;
    #endif
  }
}
#endif

/* write a char to the serial interfaces */
#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
void write_serial_str(char value)
{
  switch(serial_com_port)
  {
    #if USBPORT0
    case 0: // write via usb
      Serial.print(value);
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // write via pin 0,1
      Serial1.print(value);
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // write via bluetooth 1
      BTSerial.print(value);
    break;
    #endif
    
    #if BLUETOOTH2
    case 3: // write via bluetooth 2
      BTSerial2.print(value);
    break;
    #endif
    
    #if WLAN
    case 4: // write via wifi
    //    wifi.print
    break;
    #endif
  }
}
#endif

/* 
  write the cmd to the serial port, e.g.: 
  you check led status with "gled" (=get led)
  than you get the answer:
  "led=0,0,0,..,0"
  the string "led=" is generated by this function to save memory
  the first letter will be ignored: 
   gled -> led=...
   ghum -> hum=...
*/
#if USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || BLUETOOTH2 || WLAN
void write_serial_cmd(int j)
{
  for(int i=1; i<sizeof(cmdStrCon[j])-1 ; i++)
  {
    if(cmdStrCon[j][i]!='\0')
    {
      write_serial_str(cmdStrCon[j][i]);
    }
  }
  write_serial_str('=');
}
#endif

