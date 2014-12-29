/************************************************************
 * Functionname....: lightUp(byte y, byte startX, byte toX)
 * Description.....: This function will switch a line of LEDs, based on userinput
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: h, m, s
 * Output..........: -
 ************************************************************/
void lightUp(byte y, byte startX, byte toX){
  for (byte i=startX;i<=toX;i++) leds[koordinate(i,y)] = CRGB::White; 
}

