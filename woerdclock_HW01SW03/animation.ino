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
//		waitUntilHeart += oneSecondDelay;
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
    for( int y = 9; y > 0; y--) {
       for (int x = 0; x < 11; x++){
        heat[koordinate(x,y)] = qsub8( heat[koordinate(x,y)],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
      }
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int w= 0; w < 9; w++){
      for( int v= 11; v >= 0; v--) {
        heat[koordinate(v,w)] = (heat[koordinate(v,w+1)] + heat[koordinate(v,w+1)] + heat[koordinate(v,w+1)] ) / 3;
      }
    }
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int z = random8(2);
      int r = random8(10);
      heat[z] = qadd8( heat[koordinate(r,z)], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 4; j < NUM_LEDS; j++) {
        leds[j] = HeatColor( heat[j]);
    }
}
