// this function let you adjust the time
#if CONFIGBUTTON
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
     // button 2, the user is ready 
    case 2:
      ok = true;
      break;
      // button 3, add one minute, if it is bigger than 59, set it back to 0
    case 3:
      timeExtension = TIMEEXTENSION;
      start = millis();
      m++;
      if (m>=60) m=0;
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
#endif
// check from the analog reading wich button is pressed
#if BUTTON || CONFIGBUTTON
byte whichButtonPressed(int val){
  byte button;
  
  if (val > 10 && val < (dButtonValue + TOLLERANCE)) button = 1;          //mButtonValue is befor read from EEPROM, TOLLARANCE = 10 
  else if (val > 10 && val < okButtonValue + TOLLERANCE) button = 2;
  else if (val > 10 && val < uButtonValue + TOLLERANCE) button = 3;
  else button = 4;

  return button; // return the number from wich button is pressed
}
#endif


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

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
