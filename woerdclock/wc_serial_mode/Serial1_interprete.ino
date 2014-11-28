/* 
  Use the serial communication across bluetooth via pin 0,1 (Tx,Rx)
  Try Bluetooth Terminal for serial communication via mobile
  
  state: tested, works fine
*/
void Serial1_interprete(void)
{
  /* Serial1 communication start */
  int i,j,k;

  if(Serial1.available()){                   // check to see if at least one character is available
    char ch=Serial1.read();
    //Serial1.print(ch);                       // no echo
    if(int(ch)>32)                          // ignore spaces 
      cmdStr[cmdStrIn++]=ch;
    cmdStr[cmdStrIn]='\0';
    if((ch=='\n')||(ch=='\r')){            // end of commandline
      i=0; 
      j=0; 
      k=0;                                 // split the commandline in command and parameters
      Serial1.println();      
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
        printhelptext1();
        break;
        
      case  2: 
//slb = set_led_brightness (store in SRAM)
	if(cmd[1][0]){
	LEDbright = atoi(cmd[1]);
        }
        break;

      case  3: 
//glb = get_led_brightness (get from SRAM)
	Serial1.println(LEDbright);
        break;

      case  4: 
//slbp = set_led_brightness_permanent (store in EEPROM)
	EEPROM.write(0, LEDbright);
        /*        
        Serial1.print("Now, LED brightness is: ");
        Serial1.println(EEPROM.read(0));
        */
        break;

      case  5: 
//glbp = get_led_brightness_permanent (get from EEPROM)
	Serial1.println(EEPROM.read(0));
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
        Serial1.print(LEDcolorR);
        Serial1.print(",");
        Serial1.print(LEDcolorG);
        Serial1.print(",");
        Serial1.println(LEDcolorB);
        break;

      case  8: 
//slcp = set_led_color_permanent (store in EEPROM)
        EEPROM.write(1, LEDcolorR);
        EEPROM.write(2, LEDcolorG);
        EEPROM.write(3, LEDcolorB);
        /*
        Serial1.print("Now, LED color is: ");
        Serial1.print(EEPROM.read(1));
        Serial1.print(",");
        Serial1.print(EEPROM.read(2));
        Serial1.print(",");
        Serial1.println(EEPROM.read(3));
        */
        break;

	case 9:
//glcp = get_led_color_permanent (get from EEPROM)
        Serial1.print(EEPROM.read(1));
        Serial1.print(",");
        Serial1.print(EEPROM.read(2));
        Serial1.print(",");
        Serial1.println(EEPROM.read(3));
	break;
        
      default: 
        if(strlen(cmd[0])){
          Serial1.println("error");
        }
      }   
      for(i=0; i<paraCount; i++)                     //reset variables
        cmd[i][0]='\0';
      cmdStr[0]='\0';
      cmdStrIn=0;  
      i=0;  
    }  
  }
  /* Serial1 communication end */
}

void printhelptext1 (void)
{
  /* Welcome and help text */
  Serial1.print(F("\nWelcome to WordClock Controller Interface\
  \n\r version 0.5\
  \n\r"));
               
  Serial1.print(F("\npossible commands are:\
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
