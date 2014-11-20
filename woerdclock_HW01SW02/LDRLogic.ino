void doLDRLogic() {
	if(millis() >= waitUntilLDR && autoBrightnessEnabled) {
		DEBUG_PRINT("doing LDR logic");
		waitUntilLDR = millis();
		int ldrVal = map(analogRead(ANALOGPIN), 0, 1023, 0, 150);
		FastLED.setBrightness(255-ldrVal);
		FastLED.show();
		DEBUG_PRINT(ldrVal);
		waitUntilLDR += oneSecondDelay;
	}
        else if(millis() >= waitUntilLDR && !autoBrightnessEnabled) {
                FastLED.setBrightness(brightness);
                FastLED.show();
		DEBUG_PRINT(brightness);
		waitUntilLDR += oneSecondDelay;  
        }
}
