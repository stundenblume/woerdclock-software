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
  for(byte i=0;i<WS2812BCOUNT;i++) leds[i] = CRGB::Black;

  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.print(s);
  Serial.print(" ");

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

  if (m>24) H++;
  if (H>12) H=1;

  switch(H){
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
  default:
    set12();
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
  }
  else if (m<35){
    setHalf(); 
  }
  else if (m<40){
    set5(); 
    setPast();
    setHalf();
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
  for (int i=0;i<m%5 && m%5>0;i++) leds[i] = CRGB::White;
}

// Logic to switch seconds
/////////////////////////////

void setS(){

}


// Set correct LEDs for other text
///////////////////////////////////

void setQuater(){
  lightUp(2,4,10);
  Serial.print(" quater");
}
void setHalf(){
  lightUp(4,0,3);
  Serial.print(" half");
}
void setTo(){
  lightUp(3,0,2);
  Serial.print(" to");
}
void setPast(){
  lightUp(3,7,10);
  Serial.print(" past");
}
void setItIs(){
  lightUp(0,0,1);

  lightUp(0,3,5);
  Serial.print("it is");
}

void setUhr(){
  lightUp(9,8,10);
  Serial.print(" o'clock");
}


//Set LEDs for hours
////////////////////////

void set12(){
  lightUp(8,6,10);
  Serial.print(" twelve");
}
void set1(){
  if(m<5)lightUp(5,0,3);
  else lightUp(5,0,2);
  Serial.print(" one");
}
void set2(){
  lightUp(5,7,10);
  Serial.print(" two");
}
void set3(){
  lightUp(2,0,3);
  Serial.print(" three");
}
void set4(){
  lightUp(6,7,10);
  Serial.print(" four");
}
void set5H(){
  lightUp(4,7,10);
  Serial.print(" five*");
}
void set6(){
  lightUp(7,0,4);
  Serial.print(" six");
}
void set7(){
  lightUp(8,0,5);
  Serial.print(" seven");
}
void set8(){
  lightUp(7,7,10);
  Serial.print(" eight");
}
void set9(){
  lightUp(9,3,6);
  Serial.print(" nine");
}
void set10H(){
  lightUp(9,0,3);
  Serial.print(" ten*");
}
void set11(){
  lightUp(4,5,7);
  Serial.print(" eleven");
}


//set LEDs for minutes
/////////////////////////

void set5(){
  lightUp(0,7,10);
  Serial.print(" five");
}
void set10(){
  lightUp(1,0,3);
  Serial.print(" ten");
}
void set20(){
  lightUp(1,4,10);
  Serial.print(" twenty");
}




