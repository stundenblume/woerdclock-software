void animation() {
	//if(millis() >= waitUntilHeart) {
//		autoBrightnessEnabled = false;
//		DEBUG_PRINT("showing heart");
//		waitUntilHeart = millis();
//		resetAndBlack();
//		pushToStrip(29); pushToStrip(30); pushToStrip(70); pushToStrip(89);
//		pushToStrip(11); pushToStrip(48); pushToStrip(68); pushToStrip(91);
//		pushToStrip(7); pushToStrip(52); pushToStrip(107);
//		pushToStrip(6); pushToStrip(106);
//		pushToStrip(5); pushToStrip(105);
//		pushToStrip(15); pushToStrip(95);
//		pushToStrip(23); pushToStrip(83);
//		pushToStrip(37); pushToStrip(77);
//		pushToStrip(41); pushToStrip(61);
//		pushToStrip(59);
//		displayStrip(CRGB::Red);
		waitUntilHeart += oneSecondDelay;
	//}
          random16_add_entropy( random());

          Fire2012(); // run simulation frame
          
          FastLED.show(); // display this frame
          FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
        leds[j] = HeatColor( heat[j]);
    }
}
