/************************************************************
 * Functionname....: selftest(int pause)
 * Description.....: This function will light up every LED once.
 * Author..........: Sebastian Setz
 * modified by.....: -
 * Inpup...........: pause; this will define how fast the selftest will be
 * Global Variables: -
 * Output..........: -
 ************************************************************/
void selftest(int pause){                                                      
  for(int i = 0; i < WS2812BCOUNT; i++) {
    leds[i] = CRGB::White; // Turn our current led on to white, then show the leds
    FastLED.show(); // Show the leds (only one of which is set to white, from above)
    delay(pause); // Wait a little bit
    leds[i] = CRGB::Black; // Turn our current led back to black for the next loop around
  }
}




