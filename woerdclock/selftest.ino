// this function will switch every LED short on and off

void selftest(int pause){                                                      
  for(int whiteLed = 0; whiteLed < WS2812BCOUNT; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB::White; // Turn our current led on to white, then show the leds
    FastLED.show(); // Show the leds (only one of which is set to white, from above)
    delay(pause); // Wait a little bit
    leds[whiteLed] = CRGB::Black; // Turn our current led back to black for the next loop around
  }
}




