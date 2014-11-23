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

//void shiftChar (){
  for(int i=9; i==0; i--){ 
      
        if(millis() >= waitUntilwriteChar) {
          waitUntilwriteChar = millis();
          resetAndBlack();
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
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,6));
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
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,6));
                  break;
                case 'M':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(3+i,3));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(5+i,2));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  pushToStrip(koordinate(5+i,5));
                  pushToStrip(koordinate(5+i,6));
                  break;
                case 'N':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,3));
                  pushToStrip(koordinate(3+i,3));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(5+i,2));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  pushToStrip(koordinate(5+i,5));
                  pushToStrip(koordinate(5+i,6));
                  break;
                case 'O':
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
                case 'P':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(4+i,4));
                  break;
                case 'Q':
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
                  pushToStrip(koordinate(5+i,6));
                  break;
                case 'R':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(4+i,6));
                  break;
                case 'S':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,6));
                  break;
                case 'T':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,3));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(2+i,5));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(3+i,2));
                  break;
                case 'U':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,6));
                  break;
                case 'V':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(2+i,3));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,2));
                  break;
                case 'W':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(4+i,6));
                  pushToStrip(koordinate(5+i,2));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  pushToStrip(koordinate(5+i,5));
                  pushToStrip(koordinate(5+i,6));
                  break;
                case 'X':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(2+i,3));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,5));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(5+i,2));
                  break;
                case 'Y':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(2+i,3));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(5+i,2));
                  break;
                case 'Z':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,3));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(3+i,3));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,6));
                  pushToStrip(koordinate(5+i,2));
                  pushToStrip(koordinate(5+i,6));
                  break;
                case ' ':         
                  break;
                case '1':
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(3+i,3));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,3));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,6));
                  pushToStrip(koordinate(4+i,7));
                  pushToStrip(koordinate(4+i,8));
                  break;
                case '2':
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,8));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,8));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,8));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,8));
                  pushToStrip(koordinate(1+i,7));
                  break;
                case '3':
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,7));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,7));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,7));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,4));
                  pushToStrip(koordinate(4+i,7));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,7));
                  break;
                case '4':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(2+i,5));
                  pushToStrip(koordinate(3+i,4));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(3+i,7));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(5+i,5));
                  break;
                case '5':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,7));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,4));
                  pushToStrip(koordinate(2+i,8));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,6));
                  pushToStrip(koordinate(4+i,8));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,7));
                  pushToStrip(koordinate(5+i,8));
                  break;
                case '6':
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(1+i,7));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,5));
                  pushToStrip(koordinate(2+i,8));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,8));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,6));
                  pushToStrip(koordinate(5+i,7));
                  break;
                case '7':
                  pushToStrip(koordinate(1+i,2));
                  pushToStrip(koordinate(1+i,8));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,6));
                  pushToStrip(koordinate(2+i,7));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,6));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(5+i,2));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  break;
                case '8':
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(1+i,7));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,5));
                  pushToStrip(koordinate(2+i,8));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,8));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  pushToStrip(koordinate(5+i,5));
                  pushToStrip(koordinate(5+i,6));
                  pushToStrip(koordinate(5+i,7));
                  break;
                case '9':
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,7));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,5));
                  pushToStrip(koordinate(2+i,8));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,5));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,5));
                  pushToStrip(koordinate(4+i,8));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  pushToStrip(koordinate(5+i,5));
                  pushToStrip(koordinate(5+i,6));
                  pushToStrip(koordinate(5+i,7));
                  break;
                case '0':
                  pushToStrip(koordinate(1+i,3));
                  pushToStrip(koordinate(1+i,4));
                  pushToStrip(koordinate(1+i,5));
                  pushToStrip(koordinate(1+i,6));
                  pushToStrip(koordinate(1+i,7));
                  pushToStrip(koordinate(2+i,2));
                  pushToStrip(koordinate(2+i,8));
                  pushToStrip(koordinate(3+i,2));
                  pushToStrip(koordinate(3+i,8));
                  pushToStrip(koordinate(4+i,2));
                  pushToStrip(koordinate(4+i,8));
                  pushToStrip(koordinate(5+i,3));
                  pushToStrip(koordinate(5+i,4));
                  pushToStrip(koordinate(5+i,5));
                  pushToStrip(koordinate(5+i,6));
                  pushToStrip(koordinate(5+i,7));
                  break;     
                default:
                  pushToStrip(0);
                  pushToStrip(1);
                  pushToStrip(2);
                  pushToStrip(3);
              }   
          displayStrip(CRGB::Red);
        }
        waitUntilwriteChar += oneSecondDelay;
        while(millis() < waitUntilwriteChar);
    }    
}



