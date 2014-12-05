void serial_com(void)
{
  /* Welcome + help text */
  const char strwelcome[]  = "\nWelcome to WördClock Controller Interface  \n\r version 0.71";
  const char strhelp1[] = 
  "\n Possible commands are:"
  "\n\r help           help text"
  "\n\r slb=0-255 	set led brightness 0-255"
  "\n\r glb            get led brightness"
  "\n\r slbp           store led brightness permanent"
  "\n\r glbp           get permanent led brightness"
  "\n\r slc=R,G,B      set led color (R,G,B) (0-255)"
  "\n\r glc            get led color";
  
  const char strhelp2[] =
  "\n\r slcp           store led color permanent"
  "\n\r glcp           get permanent led color"
  "\n\r sled=0-114,0/1 set led by number off/on"
  "\n\r srtc           set unix time stamp for clock"
  "\n\r grtc           get unix time stamp and time from clock";

  const char strhelp3[] =
  "\n\r gtem           get temperature"
  "\n\r ghum           get humidity"
  "\n\r mode           set the mode\n";

  const char strerror[] = "error";
  const char paramseperator = ',';
  const char cmdbreak = '\n';
  
  /* Check which port is actually available 
      This is realy primitive, because there is a ranking.
      If usb send permanent data, bluetooth will be ignored.
      If you dislike this, we need a state machine.
  */
  serial_com_port = 255; //default, means no port
  
  if(USBPORT0 || BLUETOOTH0 || BLUETOOTH1 || WLAN)
  {
  #if USBPORT0
  if(Serial.available())
  {
    serial_com_port = 0;
  }
  #endif
  #if BLUETOOTH0
  else if(Serial1.available())
  {
    serial_com_port = 1;
  }
  #endif
  
  #if WLAN
  //  else if(wifi.available())
  //  {
  //    serial_com_port = 4;
  //  }
  #endif
  }
  else
  {
    
    #if BLUETOOTH1
    BTSerial.listen();
    if(BTSerial.available())
    {
      serial_com_port = 2;
    }
    #endif
    
    #if BLUETOOTH2
    BTSerial2.listen();
    if(BTSerial2.available())
    {
      serial_com_port = 3;
    }
    #endif
    
  }
  
  
  /* Serial communication start */
  /* based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz */
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
	EEPROM.write(0, LEDbright);
      break;

      case  5: //glbp = get_led_brightness_permanent (get from EEPROM)
        write_serial_cmd(j);
        write_serial(EEPROM.read(0));
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
        EEPROM.write(1, LEDcolorR);
        EEPROM.write(2, LEDcolorG);
        EEPROM.write(3, LEDcolorB);
      break;

      case 9: //glcp = get_led_color_permanent (get from EEPROM)
        write_serial_cmd(j);
        write_serial(EEPROM.read(1));
        write_serial_str(paramseperator);
        write_serial(EEPROM.read(2));
        write_serial_str(paramseperator);
        write_serial(EEPROM.read(3));
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
        write_serial(dht_temperature);
        write_serial_str(cmdbreak);
      break;

      case 14: //gh = get humidity
        write_serial_cmd(j);
        write_serial(dht_humidity);
        write_serial_str(cmdbreak);
      break;
      #endif

      case 15: //mode = set a mode
        mode=atoi(cmd[1]);
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





/* read a char from the serial interfaces */
char read_serial()
{
  char ch;
  switch(serial_com_port)
  {
    #if USBPORT0
    case 0: // read from usb
    if(Serial.available())
    {                   
      ch=Serial.read();
      return ch;
    }
    break;
    #endif
    
    #if BLUETOOTH0
    case 1: // read from pin 0,1
    if(Serial1.available())
    {                   
      ch=Serial1.read();
      return ch;
    }
    break;
    #endif
    
    #if BLUETOOTH1
    case 2: // read via bluetooth 1
    if(BTSerial.available())
    {                   
      ch=BTSerial.read();
      return ch;
    }
    break;
    #endif

    #if BLUETOOTH2   
    case 3: // read via bluetooth 2
      if(BTSerial2.available())
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


/* write a number/value to the serial interfaces */
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


/* write a char to the serial interfaces */

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


/* 
  write the cmd to the serial port, e.g.: 
  you check led status with "gled" (=get led)
  than you get the answer:
  "led=0,0,0,..,0"
  the string "led=" is generated by this function to save memory
*/
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
