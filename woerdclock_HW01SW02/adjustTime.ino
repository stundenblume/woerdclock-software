// this function let you adjust the time
void adjustTime(){
   DEBUG_PRINT("adjustTime");
   pushSET_T();

  int timeExtension=0;
  unsigned long start = millis(); // store the time, so you can leaf this menue afer a given time
  boolean ok = false; // we will use this to detect the ok button
  while(!ok && millis()-start<AUTOENDTIME+timeExtension){ // if the user didn't hit the ok button or there are no inputs for over x seconds, leaf this function
    switch (whichButtonPressed(analogRead(ANALOGPIN))){ // check wich button is pressed
      // button 1, add one hour, if it is bigger than 23, set it back to 0
    case 1:
      timeExtension = TIMEEXTENSION;
      start = millis();
      h++;
      if (h>=24) h=0;
      break;

      // button 3, add one minute, if it is bigger than 59, set it back to 0
    case 2:
      timeExtension = TIMEEXTENSION;
      start = millis();
      m++;
      if (m>=60) m=0;
      break;

      // button 2, the user is ready
    case 3:
      ok = true;
      break;
    }

    // show the new time
    resetAndBlack();
    timeToStrip(h, m);
    displayStrip(defaultColor);
    DEBUG_PRINT("h");
    DEBUG_PRINT(h);
    DEBUG_PRINT("m");
    DEBUG_PRINT(m);
    delay(150);
    
    
  }
  if (RTCpresent && ok){
    RTC.adjust(DateTime(ye, mo, da, h, m, 0));
  } // if the RTC is present, store the new time in the RTC
}

// check from the analog reading wich button is pressed
byte whichButtonPressed(int val){
  byte button;
  
  if (val > 10 && val < (mButtonValue - TOLLERANCE)) button = 1;          //mButtonValue is befor read from EEPROM, TOLLARANCE = 10 
  else if (val > 10 && val < mButtonValue + TOLLERANCE) button = 2;
  else if (val > 10 && val < okButtonValue + TOLLERANCE) button = 3;
  else button = 4;

  return button; // return the number from wich button is pressed
}

 void pushSET_T()  {
	resetAndBlack();
        pushToStrip(koordinate(0,0));      //S
	pushToStrip(koordinate(1,0));
	pushToStrip(koordinate(2,0));
	pushToStrip(koordinate(0,1));
	pushToStrip(koordinate(0,2));
        pushToStrip(koordinate(1,2));
        pushToStrip(koordinate(2,2));
        pushToStrip(koordinate(2,3));
        pushToStrip(koordinate(2,4));
        pushToStrip(koordinate(1,4));
        pushToStrip(koordinate(0,4));
        
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
       
        pushToStrip(koordinate(4,6));      //T
        pushToStrip(koordinate(5,6));
        pushToStrip(koordinate(6,6));
        pushToStrip(koordinate(5,7));
        pushToStrip(koordinate(5,8));
        pushToStrip(koordinate(5,9));
 
        displayStrip(defaultColor);
        delay(2000);       
}
