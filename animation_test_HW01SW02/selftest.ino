

void selftest(int pause){                                                      
  // Move a single white led 
  for(int whiteLed = 0; whiteLed < WS2812BCOUNT; whiteLed = whiteLed + 1) {
    // Turn our current led on to white, then show the leds
    leds[whiteLed] = CRGB::White;
    FastLED.setBrightness(BRIGHTNESS);
    // Show the leds (only one of which is set to white, from above)
    FastLED.show();

    // Wait a little bit
    delay(pause);

    // Turn our current led back to black for the next loop around
    leds[whiteLed] = CRGB::Black;
  }
   
}

// this funktion will switch every LED short on an off in RGB colors

void selftest_RGB(int pause){  
  
  
  int i;
  
  for (i = 0; i <= 113; i = i + 1) { // wählt alle LEDS aus
  leds[i] = CRGB::Red; 
  }
  FastLED.show();  // alle LEDS an
  
  delay(pause); // Pause
  
    for (i = 0; i <= 113; i = i + 1) { // wählt alle LEDS aus
  leds[i] = CRGB::Green; 
  }
  FastLED.show();  // alle LEDS an
  
  delay(pause); // Pause
  
    for (i = 0; i <= 113; i = i + 1) { // wählt alle LEDS aus
  leds[i] = CRGB::Blue; 
  }
  FastLED.show();  // alle LEDS an
  
  delay(pause); // Pause
  
  for (i = 0; i <= 114; i = i + 1) { // wählt alle LEDS aus
  leds[i] = CRGB::Black;
  }
  FastLED.show();
}
