// font: http://robey.lag.net/2010/01/23/tiny-monospace-font.html

void writeChar(char val){
  //setBrightness(255);
//  showH(0);
//  showM(0);
//  showS(0);


//  delay(CHARSHOWTIME);
//  showH(0);
//  showM(0);
//  showS(0);
//  delay(CHARSHOWTIME/4);
//}

void shiftChar (){
  for(i=9; i==0; i--){ 
  
    if(millis() >= waitUntilwriteChar) {
      waitUntilwriteChar = millis();
      resetAndBlack();
      pushToStrip(29);
        switch (val){
            case 'A':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,2));
              pushToStrip(koordinate(2+i,4));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,3));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(3+i,5));
              pushToStrip(koordinate(3+i,6));
              break;
            case 'B':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,2));
              pushToStrip(koordinate(2+i,4));
              pushToStrip(koordinate(2+i,6));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(2+i,6));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,3));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(3+i,5));
              pushToStrip(koordinate(3+i,6));
              break;
            case 'C':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,2));
              pushToStrip(koordinate(2+i,6));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,6));
              pushToStrip(koordinate(4+i,2));
              pushToStrip(koordinate(4+i,6));
              break;
            case 'D':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,2));
              pushToStrip(koordinate(2+i,6));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,6));
              pushToStrip(koordinate(4+i,2));
              pushToStrip(koordinate(4+i,3));
              pushToStrip(koordinate(4+i,4));
              pushToStrip(koordinate(4+i,5));
              pushToStrip(koordinate(4+i,6));
              break;
            case 'E':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,2));
              pushToStrip(koordinate(2+i,4));
              pushToStrip(koordinate(2+i,6));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(2+i,6));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(3+i,6));
              break;
            case 'F':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,2));
              pushToStrip(koordinate(2+i,4));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              break;
            case 'K':
              pushToStrip(koordinate(1+i,2));
              pushToStrip(koordinate(1+i,3));
              pushToStrip(koordinate(1+i,4));
              pushToStrip(koordinate(1+i,5));
              pushToStrip(koordinate(1+i,6));
              pushToStrip(koordinate(2+i,4));
              pushToStrip(koordinate(2+i,4));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              pushToStrip(koordinate(3+i,2));
              pushToStrip(koordinate(3+i,4));
              break;
            case 'L':
              showH(2+4+8);
              showM(1+4+16);
              showS(1+2+4+16);
              break;
            case 'M':
              showH(1+2+4+8+16);
              showM(4);
              showS(1+2+4+8+16);
              break;
            case 'N':
              showH(1+16);
              showM(1+2+4+8+16);
              showS(1+16);
              break;
            case 'O':
              showH(1+2+4+8+16);
              showM(1);
              showS(1);
              break;
            case 'P':
              showH(1+2+4+8+16);
              showM(4+8);
              showS(1+2+4+8+16);
              break;
            case 'Q':
              showH(1+2+4+8+16);
              showM(2+4+8);
              showS(1+2+4+8+16);
              break;
            case 'R':
              showH(1+2+4+8+16);
              showM(2+4+16);
              showS(1+4+8);
              break;
            case 'S':
              showH(1+8);
              showM(1+4+16);
              showS(2+16);
              break;
            case 'T':
              showH(16);
              showM(1+2+4+8+16);
              showS(16);
              break;
            case 'U':
              showH(2+4+8+16);
              showM(1);
              showS(1+2+4+8+16);
              break;
            case 'V':
              showH(2+8);
              showM(4);
              showS(2+8);
              break;
            case 'W':
              showH(2+8);
              showM(4);
              showS(2+8);
              break;
            case 'X':
              showH(2+8);
              showM(4);
              showS(2+8);
              break;
            case 'Y':
              showH(2+8);
              showM(4);
              showS(2+8);
              break;
            case 'Z':
              showH(2+8);
              showM(4);
              showS(2+8);
              break;
            case ' ':
              break;
            default:
              showH(1);
              showM(1);
              showS(1);
  }   
      displayStrip(CRGB::Red);
     }
     waitUntilwriteChar += oneSecondDelay;
  }
}



