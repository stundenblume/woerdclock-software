// this function will switch every LED short on and off

void selftest(int pause){                                                      
  // Move a single white led 
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    // Turn our current led on to white, then show the leds
    leds[whiteLed] = CRGB::White;
    FastLED.setBrightness(brightness);
    // Show the leds (only one of which is set to white, from above)
    FastLED.show();

    // Wait a little bit
    delay(pause);

    // Turn our current led back to black for the next loop around
    leds[whiteLed] = CRGB::Black;
  }
}
