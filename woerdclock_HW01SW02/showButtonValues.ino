//this function will show all in EEPROM stored and current values of the buttonValues

void showButtonValues(int time){
  alreadyCalibrated();
  
  for (int j=1;j<4;j++)  {
    showH(j);
    int value = EEPROM.read(j)*4;
    showINT(value);
    delay(time);
  }
  showH(4);  
  showINT(hButtonValue);
  delay(time);
  
  showH(5);  
  showINT(okButtonValue);
  delay(time);
  
  showH(6);  
  showINT(mButtonValue);
  delay(time);

  showH(0);  
  showM(0);  
  showS(0);
  delay(time/2);
}












