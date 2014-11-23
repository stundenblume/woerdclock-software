// this function let you select the modus
void selectModus(){
  
  int timeExtension=0;
  unsigned long start = millis(); // store the time, so you can leaf this menue afer a given time
  boolean ok = false; // we will use this to detect the ok button
  while(!ok && millis()-start<AUTOENDTIME+timeExtension){ // if the user didn't hit the ok button or there are no inputs for over x seconds, leaf this function
    switch (whichButtonPressed(analogRead(ANALOGPIN))){ // check wich button is pressed
      // button 1, add one hour, if it is bigger than 23, set it back to 0
    case 1:
      timeExtension = TIMEEXTENSION;
      start = millis();
      displayMode++;
      if (displayMode>=5) displayMode=0;
      break;

      // button 3, add one minute, if it is bigger than 59, set it back to 0
    case 2:
      timeExtension = TIMEEXTENSION;
      start = millis();
      displayMode--;
      if (displayMode<0) displayMode=4;
      break;

      // button 2, the user is ready
    case 3:
      ok = true;
      break;
    }
// show the new Modus
   switch(displayMode) {
		case 0:              //ONOFF
			writeChar('0');
                        delay(150);
			break;
		case 1:              //FAST
			writeChar('1');
                        delay(150);           
			break;
		case 2:              //DISCO
			writeChar('2');
                        delay(150);
			break;
		case 3:               //ANIM
			writeChar('3');
                        delay(150);
			break;
		case 4:                //CLOCK
			writeChar('4');
                        delay(150);
			break;
		default:
			writeChar('4');
                        delay(150);
			break;
	} 
  }
}


