// this functions will toggle the LEDs corrosponding to the current time

/*

 1. es ist xx Uhr
 2. es ist fünf nach XX
 3. es ist zehn nach XX
 4. es ist viertel nach XX
 5. es ist zwanzig nach XX
 6. es ist fünf vor halb YY
 7. es ist halb YY
 8. es ist fünf nach halb YY
 9. es ist zwanzig vor YY
 10. es ist viertel vor YY
 11. es ist zehn vor YY
 12. es ist fün vor YY
 
 */


// toggle right capitals
///////////////////////////

void showTime(){
  // show: es ist
  setItIs();

  setM();
  setH();
  setS();

  if (m<5) setUhr();

  FastLED.show();
  Serial.println();
}


// Logic to switch hours
/////////////////////////

void setH(){
  byte H=h;

  if (m>39) H++;

  switch(H){
  case 0:
    set12();
    break;
  case 1:
    set1();
    break;
  case 2:
    set2();
    break;
  case 3:
    set3();
    break;
  case 4:
    set4();
    break;
  case 5:
    set5H();
    break;
  case 6:
    set6();
    break;
  case 7:
    set7();
    break;
  case 8:
    set8();
    break;
  case 9:
    set9();
    break;
  case 10:
    set10H();
    break;
  case 11:
    set11();
    break;
  } 
}


// Logic to switch minutes
/////////////////////////////

void setM(){
  if (m<5) ;
  else if (m<10){
    set5();
    setPast();
  }
  else if (m<15){
    set10(); 
    setPast();
  }
  else if (m<20){
    setQuater();
    setPast();
  }    
  else if (m<25){
    set20();
    setPast();
  }
  else if (m<30){
    set5(); 
    setTo();
    setHalf();
    setPast();
  }
  else if (m<35){
    setHalf(); 
    setPast();
  }
  else if (m<40){
    set5(); 
    setPast();
    setHalf();
    setPast();
  }
  else if (m<45){
    set20();
    setTo();
  }
  else if (m<50){
    setQuater();
    setTo();
  }
  else if (m<55){
    set10(); 
    setTo();
  }
  else if (m<60){
    set5(); 
    setTo();
  }
}

// Logic to switch seconds
/////////////////////////////

void setS(){

}


// Set correct LEDs for other text
///////////////////////////////////

void setQuater(){
  //leds[11] = CRGB::White; //U
  Serial.print(" quater");
}
void setHalf(){
  //leds[11] = CRGB::White; //U
  Serial.print(" half");
}
void setTo(){
  //leds[11] = CRGB::White; //U
  Serial.print(" to");
}
void setPast(){
  //leds[11] = CRGB::White; //U
  Serial.print(" past");
}
void setItIs(){
  leds[14] = CRGB::White; //e
  leds[15] = CRGB::White; //s

  leds[35] = CRGB::White; //i
  leds[54] = CRGB::White; //s
  leds[55] = CRGB::White; //t
  Serial.print("it is");
}

void setUhr(){
  leds[75] = CRGB::White; //U
  leds[94] = CRGB::White; //h
  leds[95] = CRGB::White; //r
  Serial.print(" o'clock");
}


//Set LEDs for hours
////////////////////////

void set12(){
  //leds[11] = CRGB::White; //U
  Serial.print(" twelve");
}
void set1(){
  //leds[11] = CRGB::White; //U
  Serial.print(" one");
}
void set2(){
  //leds[11] = CRGB::White; //U
  Serial.print(" two");
}
void set3(){
  //leds[11] = CRGB::White; //U
  Serial.print(" three");
}
void set4(){
  //leds[11] = CRGB::White; //U
  Serial.print(" four");
}
void set5H(){
  //leds[11] = CRGB::White; //U
  Serial.print(" five*");
}
void set6(){
  //leds[11] = CRGB::White; //U
  Serial.print(" six");
}
void set7(){
  //leds[11] = CRGB::White; //U
  Serial.print(" seven");
}
void set8(){
  //leds[11] = CRGB::White; //U
  Serial.print(" eight");
}
void set9(){
  Serial.print(" nine");
}
void set10H(){
  //leds[11] = CRGB::White; //U
  Serial.print(" ten*");
}
void set11(){
  //leds[11] = CRGB::White; //U
  Serial.print(" eleven");
}


//set LEDs for minutes
/////////////////////////

void set5(){
  //leds[11] = CRGB::White; //U
  Serial.print(" five");
}
void set10(){
  //leds[11] = CRGB::White; //U
  Serial.print(" ten");
}
void set20(){
  //leds[11] = CRGB::White; //U
  Serial.print(" twenty");
}

