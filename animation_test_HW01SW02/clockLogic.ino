void clockLogic() {
	if(millis() >= waitUntilRtc) {
		DEBUG_PRINT("Uhrzeit Mode");
		waitUntilRtc = millis();
		DateTime now = RTC.now();
                if(testMinutes != now.minute() || testHours != now.hour()) {
			testMinutes = now.minute();
			testHours = now.hour();
			resetAndBlack();
			timeToStrip(testHours, testMinutes);
			displayStrip(defaultColor);
		}
		waitUntilRtc += oneSecondDelay;
	}
}
