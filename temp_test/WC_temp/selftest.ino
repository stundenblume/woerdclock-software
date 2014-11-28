// this function will switch every LED short on and off

void selftest(int pause){  
  
  int all_leds = 1;
  int i;
  for (i = 0; i <= 114; i = i + 1) { // wählt alle LEDS aus
  leds[i] = CRGB::Blue; 
  }
  FastLED.show();  // alle LEDS an
  
  delay(pause); // Pause
  
  for (i = 0; i <= 114; i = i + 1) { // wählt alle LEDS aus
  leds[i] = CRGB::Black;
  }
  FastLED.show();
}


