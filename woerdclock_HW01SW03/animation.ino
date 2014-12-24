void animation() {
          if (clockaktion == true){
              clockaktion = false;    //Clock not aktion
              resetAndBlack();
          }
          
          random16_add_entropy( random());
          
          Fire2012(); // run simulation frame
          
          FastLED.show(); // display this frame
          FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void Fire2012()
{
  // Array of temperature readings at each simulation cell
  //static byte heatanim[ANIMLEDS];
  //static byte heat[ANIMLEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < ANIMLEDS; i++) {
      heatanim[i] = qsub8( heatanim[i],  random8(0, ((COOLING * 10) / ANIMLEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= ANIMLEDS - 1; k >= 2; k--) {
      heatanim[k] = (heatanim[k - 1] + heatanim[k - 2] + heatanim[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heatanim[y] = qadd8( heatanim[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < ANIMLEDS; j++) {
        leds[animath(j)] = HeatColor( heatanim[j]);
    }   
    
}

int  animath (int led){
 int x = 0;
 int y = 0;

   x = led%10;  //Zeile
   x = 9-x;    //Umrechnung unten anfangen
   y = led/10;  //Spalte
   y =  9-y;   //Umrechnung da spiegeverkehrt

 int newled = koordinate(x,y);
 return newled;

}
