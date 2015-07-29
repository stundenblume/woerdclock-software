//this function will show all in EEPROM stored and current values of the buttonValues
#if CONFIGBUTTON
void showButtonValues(int time){
  alreadyCalibrated();
  resetAndBlack();
  
  for (int j=1;j<4;j++)  {
    
    pushToStrip(j-1);
    int value = EEPROM.read(j)*4;
    showINT(j-1,value);
    
    
  }
  displayStrip(CRGB::Blue);
  delay(time);
//  pushToStrip(3);  
//  showINT(8,hButtonValue);
//  delay(time);
//  
//  pushToStrip(2);  
//  showINT(10,okButtonValue);
//  delay(time);
//  
//  pushToStrip(1);  
//  showINT(9,mButtonValue);
//  delay(time);

//  showH(0);  
//  showM(0);  
//  showS(0);
//  delay(time/2);
}
#endif











