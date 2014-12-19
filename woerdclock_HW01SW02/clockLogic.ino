void clockLogic() {
	if(millis() >= waitUntilClock) {
		DEBUG_PRINT("Uhrzeit Mode");
		waitUntilClock = millis();
                #if RTCLOCK
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
                #endif
                #if DCFMODUL && !RTCLOCK
                if(testMinutes != minute() || testHours != hour() || dhtaktion) {
			dhtaktion = false;    //dht not in aktion 
                        testMinutes = minute();
		  	testHours = hour();
			resetAndBlack();
			timeToStrip(testHours, testMinutes);
			//displayStrip(defaultColor);
                        displayStrip(LEDcolorR, LEDcolorG, LEDcolorB);
		}
                #endif
		waitUntilClock += oneSecondDelay;
	}
}

//void clockLogiColor() {
//  
//  if(millis() >= waitUntilClock) {
//		DEBUG_PRINT("Uhrzeit Mode Color");
//		waitUntilClock = millis();
//		DateTime now = RTC.now();
//                if(testMinutes != now.minute() || testHours != now.hour() || dhtaktion) {
//			dhtaktion = false;    //dht not in aktion 
//                        testMinutes = now.minute();
//		  	testHours = now.hour();
//                        defaultColor = nextColor();
//			resetAndBlack();
//			timeToStrip(testHours, testMinutes);
//			displayStrip(defaultColor);
//
//		}
//		waitUntilClock += oneSecondDelay;
//	}
//}
