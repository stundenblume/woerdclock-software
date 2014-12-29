/************************************************************
 * Functionname....: initRTC()
 * Description.....: This function will check if a RTC is present
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: h, m, s
 * Output..........: -
 ************************************************************/
void initRTC(){
  if (RTC.isrunning()) {
    RTCpresent = true;
    Serial.println("RTC present");
    DateTime now = RTC.now();
    h=now.hour();
    m=now.minute();
    s=now.second();     
  }
  else{
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
    Serial.print("No RTC or RTC not running. Setting date to ");
    Serial.print(__DATE__);
    Serial.print(" and time to ");
    Serial.print(__TIME__);
    Serial.println(".");
  }
}


