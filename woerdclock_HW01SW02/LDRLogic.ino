#if LDR
void doLDRLogic() {
	if(millis() >= waitUntilLDR && autoBrightnessEnabled) {
		DEBUG_PRINT(F("doing LDR logic"));
		waitUntilLDR = millis();
		int ldrVal = map(analogRead(ANALOGPIN), 0, 1023, 20, 180);
		FastLED.setBrightness(ldrVal);
		FastLED.show();
		DEBUG_PRINT(ldrVal);
		waitUntilLDR += oneSecondDelay;
	}
        else if(millis() >= waitUntilLDR && !autoBrightnessEnabled) {
                FastLED.setBrightness(brightness);
                FastLED.show();
		//DEBUG_PRINT(brightness);
		waitUntilLDR += oneSecondDelay;  
        }
}
#endif
