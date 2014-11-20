boolean buttonCalibration(){

  pushSET_C();

  // waiting, reading and saving the values of the buttons
  unsigned long start=millis();
  for(int i=1;i<4;i++){
    // wait for button press, after "AUTOENDCALIBRATIONTIME" the calibration will end
    while(analogRead(ANALOGPIN)<10){
      delay(10);
      if(millis()-start>AUTOENDTIME && alreadyCalibrated()) {
        i=4;
        break;
      }
    }
    delay(10); // wait for a settled value
    int value = analogRead(ANALOGPIN);
    if (i<4 && value != 0) EEPROM.write(i, value/4); // write the value to EEPROM position i
    // display wich button value is saved
    switch (i){
    case 1:
      showS(1+2);
      break;
    case 2:
      showS(1);
      break;
    case 3:
      showS(0);
      break;
    default:
      showS(1+2+8+16);
    }
    while(analogRead(ANALOGPIN)>10) delay (10);
    start=millis();
  }
  showButtonValues(500); // show the values of the buttonValues and wich values for them are stored in the EEPROM
}

void pushSET_C()  {
        resetAndBlack();
        
	pushToStrip(koordinate(0,0));      //S
	pushToStrip(koordinate(1,0));
	pushToStrip(koordinate(2,0));
	pushToStrip(koordinate(0,1));
	pushToStrip(koordinate(0,2));
        pushToStrip(koordinate(1,2));
        pushToStrip(koordinate(2,2));
        pushToStrip(koordinate(3,2));
        pushToStrip(koordinate(4,2));
        pushToStrip(koordinate(4,1));
        pushToStrip(koordinate(4,0));
        
        pushToStrip(koordinate(4,0));       //E
        pushToStrip(koordinate(5,0));
        pushToStrip(koordinate(6,0));
        pushToStrip(koordinate(4,1));
        pushToStrip(koordinate(4,2));
        pushToStrip(koordinate(4,3));
        pushToStrip(koordinate(4,4));
        pushToStrip(koordinate(5,4));
        pushToStrip(koordinate(6,4));
        pushToStrip(koordinate(4,2));
        pushToStrip(koordinate(5,2));
        
        pushToStrip(koordinate(8,0));      //T
        pushToStrip(koordinate(9,0));
        pushToStrip(koordinate(10,0));
        pushToStrip(koordinate(9,1));
        pushToStrip(koordinate(9,2));
        pushToStrip(koordinate(9,3));
        pushToStrip(koordinate(9,4));
       
        pushToStrip(koordinate(4,6));      //C
        pushToStrip(koordinate(5,6));
        pushToStrip(koordinate(6,6));
        pushToStrip(koordinate(4,7));
        pushToStrip(koordinate(4,8));
        pushToStrip(koordinate(4,9));
        pushToStrip(koordinate(5,9));
        pushToStrip(koordinate(6,9)); 
        
        displayStrip(defaultColor);
}


void pushSET_()  {
        resetAndBlack();
        
	pushToStrip(koordinate(0,0));      //S
	pushToStrip(koordinate(1,0));
	pushToStrip(koordinate(2,0));
	pushToStrip(koordinate(0,1));
	pushToStrip(koordinate(0,2));
        pushToStrip(koordinate(1,2));
        pushToStrip(koordinate(2,2));
        pushToStrip(koordinate(3,2));
        pushToStrip(koordinate(4,2));
        pushToStrip(koordinate(4,1));
        pushToStrip(koordinate(4,0));
        
        displayStrip(defaultColor);
}


// this function will read the values for the buttonValues from the EEPROM. It will return true if all values are NOT 0

boolean alreadyCalibrated(){
  hButtonValue=EEPROM.read(1)*4;
  mButtonValue=EEPROM.read(2)*4;
  okButtonValue=EEPROM.read(3)*4;

  if (hButtonValue*okButtonValue*mButtonValue!=0) return true;
  else return false;
}










