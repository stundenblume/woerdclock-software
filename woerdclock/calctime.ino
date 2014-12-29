/************************************************************
 * Functionname....: calcTime()
 * Description.....: This function will calc the current time and sync it every hour with the RTC. Expact if it is in fast forward mode.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: h, m, s
 * Output..........: -
 ************************************************************/
void calcTime(){
  if (s>=59){
    s=0;
    if (m>=59){
      m=0;
      if(h>=23) h=0;
      else{
        h++;
        if (RTCpresent && TIMESCALE == 1){
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

