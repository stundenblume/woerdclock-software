//this function will calculate the current time

void calcTime(){
  if (s>=59){
    s=0;
    if (m>=59){
      m=0;
      if(h>=23) h=0;
      else{
        h++;
        if (RTCpresent){
          DateTime now = RTC.now();
          h=now.hour();
          m=now.minute();
          s=now.second();     
        }
      }
    }
    else m++;
  }
  else s++;
}

