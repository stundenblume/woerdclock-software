// this function will light up a set of LEDs

void lightUp(byte y, byte startX, byte toX){
  for (byte i=startX;i<=toX;i++) leds[koordinate(i,y)] = CRGB::White; 
}

