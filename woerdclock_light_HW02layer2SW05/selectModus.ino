// this function let you select the modus
#if BUTTON
void selectModus(){
  
  if (analogRead(ANALOGPIN)<10){
    unsigned long start = millis(); // store the time, so you can leaf this menue afer a given time 
    while (millis()-start<AUTOENDTIME && !modus){                          //5s time to presses the h Button to start the select Modus
      int okButtonpressed = whichButtonPressed(analogRead(ANALOGPIN));
      if(okButtonpressed == 2){
        modus = true;
      }
    }
  }
  
  
  if (modus){
    unsigned long start = millis(); // store the time, so you can leaf this menue afer a given time
    while(millis()-start<AUTOENDTIME){ // if the jumper is open and 5 seconds not over and ok not pressed, this function is in action
      modus = false;
      switch (whichButtonPressed(analogRead(ANALOGPIN))){ // check which button is pressed
      case 1://next Mod
        start = millis();
        displayMode++;
        if (displayMode>=5) displayMode=0;
        break;
  
        
      case 3://prev Mod
        start = millis();
        displayMode--;
        if (displayMode<0) displayMode=4;
        break;
 
      }

  // show the new Modus
     switch(displayMode) {
  		case 0:              //ONOFF
  			resetAndBlack();
  	                pushToStrip(0);
                          displayStrip(CRGB::Blue);
                          //writeChar('0');
                          delay(150);
  			break;
  		case 1:              //Anim
                          resetAndBlack();
  	                pushToStrip(1);
                          displayStrip(CRGB::Green);
  			//writeChar('1');
                          delay(150);           
  			break;
  		case 2:              //ClockColor or Mic 
                          resetAndBlack();
  	                pushToStrip(2);
                          displayStrip(CRGB::Red);
  			//writeChar('2');
                          delay(150);
  			break;
  		case 3:               //Clock with Temp
                          resetAndBlack();
  	                pushToStrip(3);
                          displayStrip(CRGB::Yellow);
  			//writeChar('3');
                          delay(150);
  			break;
  		case 4:                //CLOCK
                          resetAndBlack();
  	                pushToStrip(0);
                          pushToStrip(1);
                          displayStrip(CRGB::Blue);
  			//writeChar('4');
                          delay(150);
  			break;
  		default:
                          resetAndBlack();
  	                pushToStrip(0);
                          pushToStrip(1);
                          displayStrip(CRGB::Blue);
  			//writeChar('4');
                          delay(150);
  			break;
  	} 
      }
    }
}
#endif

