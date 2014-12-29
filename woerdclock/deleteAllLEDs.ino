/************************************************************
 * Functionname....: deleteAllLEDs()
 * Description.....: This function will turn off all LEDs
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: -
 * Global Variables: WS2812BCOUNT
 * Output..........: -
 ************************************************************/
void deleteAllLEDs(){
  for(byte i=0;i<WS2812BCOUNT;i++) leds[i] = CRGB::Black;
}

