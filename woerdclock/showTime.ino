/************************************************************
 * Functionname....: showTime(byte type)
 * Description.....: This function will display the current time in different styles.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: type (0-255); how the time will be displayed.
 *                0: like other wordclocks
 *                1: binary
 *                2: like 7 segment displays
 *                3: analog (not supportet jet)
 * Global Variables: h, m, s
 * Output..........: -
 ************************************************************/
void showTime(byte type){

  deleteAllLEDs();

  Serial.print("type: ");
  Serial.print(type);
  Serial.print(" ");
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.print(s);
  Serial.print(" ");

  switch (type){
  case 1:
    binaryType();
    break;
  case 2:
    segmentType();
    break;
  default:
    wordclockType();
    break;
  }

  FastLED.show();
  Serial.println();
}

/************************************************************
 * Functionname....: wordclocktype()
 * Description.....: This function will display the current time like other wordclocks.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Input...........: -
 * Global Variables: m
 * Output..........: -
 *               
 * 1. es ist xx Uhr
 * 2. es ist fünf nach XX
 * 3. es ist zehn nach XX
 * 4. es ist viertel nach XX
 * 5. es ist zwanzig nach XX
 * 6. es ist fünf vor halb YY
 * 7. es ist halb YY
 * 8. es ist fünf nach halb YY
 * 9. es ist zwanzig vor YY
 * 10. es ist viertel vor YY
 * 11. es ist zehn vor YY
 * 12. es ist fün vor YY
 ************************************************************/
void wordclockType(){
  // show: es ist
  setItIs();

  setH();
  setM();

  if (m<5) setUhr(); // Just show for full hour "o'clock"
}

/************************************************************
 * Functionname....: setH()
 * Description.....: This function will light up the correct capitals to display the hour.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: h
 * Output..........: -
 ************************************************************/
void setH(){
  byte H=h;

  if (H>12) H=H-12; // Convert to 12h format
  if (m>=25)H++; // if the spelling flips from 20 minutes past xx to 5 minutes to half yy
  if (H>12) H=1; // handle the overflow from 12 to 1 o'clock

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

/************************************************************
 * Functionname....: setM()
 * Description.....: This function will light up the correct capitals to display the minutes.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: m
 * Output..........: -
 ************************************************************/
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

/************************************************************
 * Functionname....: setQuater()
 * Description.....: This function will light up the correct capitals to display "viertel".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void setQuater(){
  lightUp(2,4,10);
  Serial.print(" quater");
}

/************************************************************
 * Functionname....: setHalf()
 * Description.....: This function will light up the correct capitals to display "halb".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void setHalf(){
  lightUp(4,0,3);
  Serial.print(" half");
}

/************************************************************
 * Functionname....: setTo()
 * Description.....: This function will light up the correct capitals to display "vor".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void setTo(){
  lightUp(3,0,2);
  Serial.print(" to");
}

/************************************************************
 * Functionname....: setPast()
 * Description.....: This function will light up the correct capitals to display "nach".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void setPast(){
  lightUp(3,7,10);
  Serial.print(" past");
}

/************************************************************
 * Functionname....: setItIs()
 * Description.....: This function will light up the correct capitals to display "es ist".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void setItIs(){
  lightUp(0,0,1);
  lightUp(0,3,5);
  Serial.print("it is");
}

/************************************************************
 * Functionname....: setUhr()
 * Description.....: This function will light up the correct capitals to display "Uhr".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void setUhr(){
  lightUp(9,8,10);
  Serial.print(" o'clock");
}

/************************************************************
 * Functionname....: set1()
 * Description.....: This function will light up the correct capitals to display "ein(s)".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set1(){
  if(m>=0 && m<5)lightUp(5,0,2);
  else lightUp(5,0,3);
  Serial.print(" one");
}

/************************************************************
 * Functionname....: set2()
 * Description.....: This function will light up the correct capitals to display "zwei".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set2(){
  lightUp(5,7,10);
  Serial.print(" two");
}

/************************************************************
 * Functionname....: set3()
 * Description.....: This function will light up the correct capitals to display "drei".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set3(){
  lightUp(2,0,3);
  Serial.print(" three");
}

/************************************************************
 * Functionname....: set4()
 * Description.....: This function will light up the correct capitals to display "vier".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set4(){
  lightUp(6,7,10);
  Serial.print(" four");
}

/************************************************************
 * Functionname....: set5H()
 * Description.....: This function will light up the correct capitals to display "fünf" for hour.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set5H(){
  lightUp(4,7,10);
  Serial.print(" five*");
}

/************************************************************
 * Functionname....: set6()
 * Description.....: This function will light up the correct capitals to display "sechs".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set6(){
  lightUp(7,0,4);
  Serial.print(" six");
}

/************************************************************
 * Functionname....: set7()
 * Description.....: This function will light up the correct capitals to display "sieben".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set7(){
  lightUp(8,0,5);
  Serial.print(" seven");
}

/************************************************************
 * Functionname....: set8()
 * Description.....: This function will light up the correct capitals to display "acht".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set8(){
  lightUp(7,7,10);
  Serial.print(" eight");
}

/************************************************************
 * Functionname....: set9()
 * Description.....: This function will light up the correct capitals to display "neun".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set9(){
  lightUp(9,3,6);
  Serial.print(" nine");
}

/************************************************************
 * Functionname....: set10H()
 * Description.....: This function will light up the correct capitals to display "zehn" for hour.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set10H(){
  lightUp(9,0,3);
  Serial.print(" ten*");
}

/************************************************************
 * Functionname....: set11()
 * Description.....: This function will light up the correct capitals to display "elf".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set11(){
  lightUp(4,5,7);
  Serial.print(" eleven");
}

/************************************************************
 * Functionname....: set12()
 * Description.....: This function will light up the correct capitals to display "zwölf".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set12(){
  lightUp(8,6,10);
  Serial.print(" twelve");
}

/************************************************************
 * Functionname....: set5()
 * Description.....: This function will light up the correct capitals to display "fünf" for minutes.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set5(){
  lightUp(0,7,10);
  Serial.print(" five");
}

/************************************************************
 * Functionname....: set10()
 * Description.....: This function will light up the correct capitals to display "zehn" for minutes.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set10(){
  lightUp(1,0,3);
  Serial.print(" ten");
}

/************************************************************
 * Functionname....: set20()
 * Description.....: This function will light up the correct capitals to display "zwanzig".
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void set20(){
  lightUp(1,4,10);
  Serial.print(" twenty");
}

/************************************************************
 * Functionname....: binaryType()
 * Description.....: This function will display the current time in binary style.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: h, m, s
 * Output..........: -
 ************************************************************/
void binaryType(){
  for (byte i=9;i>9-6;i--){
    if (bitRead(h,i)) leds[koordinate(0,i)] = CRGB::White;
    if (bitRead(m,i)) leds[koordinate(2,i)] = CRGB::White;
    if (bitRead(s,i)) leds[koordinate(4,i)] = CRGB::White;
  }
}

/************************************************************
 * Functionname....: segmentType()
 * Description.....: This function will display the current time in text style.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: h, m, s
 * Output..........: -
 ************************************************************/
void segmentType(){
  // these are the ":" between hours and minutes
  leds[koordinate(5,4)] = CRGB::White;
  leds[koordinate(5,2)] = CRGB::White;

  byte H=h;

  if (H>13)H=H-12;

  // display hours
  if (H>9) show7segment(1,0);
  show7segment(H,1);

  // display minutes
  show7segment(m/10,2);
  show7segment(m-m/10,3);
}

/************************************************************
 * Functionname....: show7segment()
 * Description.....: This function will display single numbers at a specific position.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: byte number (0-9), wich number should be shown
 *                   byte position (0-3), where shuld the number be shown
 * Global Variables: -
 * Output..........: -
 *
 * 0 ... XXX .X. XXX XXX X.. XXX XXX XXX XXX XXX
 * 1 ... X.X .X. ..X ..X X.X X.. X.. ..X X.X X.X
 * 2 .X. X.X .X. XXX XXX XXX XXX XXX ..X XXX XXX
 * 3 ... X.X .X. X.. ..X ..X ..X X.X ..X X.X ..X
 * 4 ... XXX .X. XXX XXX ..X XXX XXX ..X XXX XXX
 *    *   0   1   2   3   4   5   6   7   8   9
 *
 ************************************************************/
void show7segment(byte number, byte pos){
  if(pos==0 && number!=1) number=10; // on pos=0 just "1" can be displayed, because of to less space.

  switch (number){
  case 0:
    lightUp(0,0+pos*3,2+pos*3);
    for (byte i=1;i<4;i++){
      leds[koordinate(0+pos*3,i)] = CRGB::White;
      leds[koordinate(2+pos*3,i)] = CRGB::White;
    }
    lightUp(4,0+pos*3,2+pos*3);
    break;
  case 1:
    for (byte i=0;i<5;i++) leds[koordinate(0+pos*3,i)] = CRGB::White;
    break;
  case 2:
    lightUp(0,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,1)] = CRGB::White;
    lightUp(2,0+pos*3,2+pos*3);
    leds[koordinate(0+pos*3,3)] = CRGB::White;
    lightUp(4,0+pos*3,2+pos*3);
    break;
  case 3:
    lightUp(0,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,1)] = CRGB::White;
    lightUp(2,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,3)] = CRGB::White;
    lightUp(4,0+pos*3,2+pos*3);
    break;
  case 4:
    for (byte i=0;i<3;i++){
      leds[koordinate(0+pos*3,i)] = CRGB::White;
    }
    leds[koordinate(1+pos*3,1)] = CRGB::White;
    leds[koordinate(2+pos*3,2)] = CRGB::White;
    for (byte i=2;i<5;i++){
      leds[koordinate(2+pos*3,i)] = CRGB::White;
    }
    break;
  case 5:
    lightUp(0,0+pos*3,2+pos*3);
    leds[koordinate(0+pos*3,1)] = CRGB::White;
    lightUp(2,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,3)] = CRGB::White;
    lightUp(4,0+pos*3,2+pos*3);
    break;
  case 6:
    lightUp(0,0+pos*3,2+pos*3);
    leds[koordinate(0+pos*3,1)] = CRGB::White;
    lightUp(2,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,3)] = CRGB::White;
    leds[koordinate(0+pos*3,3)] = CRGB::White;
    lightUp(4,0+pos*3,2+pos*3);
    break;
  case 7:
    lightUp(0,0+pos*3,1+pos*3);
    for (byte i=0;i<5;i++) leds[koordinate(2+pos*3,i)] = CRGB::White;
    break;
  case 8:
    lightUp(0,0+pos*3,2+pos*3);
    leds[koordinate(0+pos*3,1)] = CRGB::White;
    leds[koordinate(2+pos*3,1)] = CRGB::White;
    lightUp(2,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,3)] = CRGB::White;
    leds[koordinate(0+pos*3,3)] = CRGB::White;
    lightUp(4,0+pos*3,2+pos*3);
    break;
  case 9:
    lightUp(0,0+pos*3,2+pos*3);
    leds[koordinate(0+pos*3,1)] = CRGB::White;
    leds[koordinate(2+pos*3,1)] = CRGB::White;
    lightUp(2,0+pos*3,2+pos*3);
    leds[koordinate(2+pos*3,3)] = CRGB::White;
    lightUp(4,0+pos*3,2+pos*3);
    break;
  default:
    leds[koordinate(0+pos*3,2)] = CRGB::White;
    break;
  }
}
