void clockLogic() {
	if(millis() >= waitUntilRtc) {
		DEBUG_PRINT("Uhrzeit Mode");
		waitUntilRtc = millis();
		DateTime now = RTC.now();
                if(testMinutes != now.minute() || testHours != now.hour() || dhtaktion) {
			dhtaktion = false;    //dht not in aktion 
                        testMinutes = now.minute();
		  	testHours = now.hour();
			resetAndBlack();
			timeToStrip(testHours, testMinutes);
			//displayStrip(defaultColor);
                        displayStrip(LEDcolorR, LEDcolorG, LEDcolorB);
		}
		waitUntilRtc += oneSecondDelay;
	}
}

void clockLogiColor() {
  
  if(millis() >= waitUntilRtc) {
		DEBUG_PRINT("Uhrzeit Mode Color");
		waitUntilRtc = millis();
		DateTime now = RTC.now();
                if(testMinutes != now.minute() || testHours != now.hour() || dhtaktion) {
			dhtaktion = false;    //dht not in aktion 
                        testMinutes = now.minute();
		  	testHours = now.hour();
                        defaultColor = nextColor();
			resetAndBlack();
			timeToStrip(testHours, testMinutes);
			displayStrip(defaultColor);

		}
		waitUntilRtc += oneSecondDelay;
	}
}
