void clockLogic() {
	if(millis() >= waitUntilClock) {
		DEBUG_PRINT("Uhrzeit Mode");
		waitUntilClock = millis();
                #if RTCLOCK
		//DateTime now = RTC.now();
//                #if DEBUG
//                        Serial.print(now.year(), DEC);
//                        Serial.print('/');
//                        Serial.print(now.month(), DEC);
//                        Serial.print('/');
//                        Serial.print(now.day(), DEC);
//                        Serial.print(' ');
//                        Serial.print(now.hour(), DEC);
//                        Serial.print(':');
//                        Serial.print(now.minute(), DEC);
//                        Serial.print(':');
//                        Serial.print(now.second(), DEC);
//                        Serial.println();
//                #endif
                if(testMinutes != minute() || testHours != hour() || dhtaktion || colorchange) {
			dhtaktion = false;    //dht not in aktion
                        clockaktion = true;    //Clock in aktion
                        colorchange = false;  //color not change over serial
                        testMinutes = minute();
                        #if  RUNDECLOCK
                          testMinutes = testMinutes + 2;
                        #endif
		  	testHours = hour();
			resetAndBlack();
			timeToStrip(testHours, testMinutes);
			//displayStrip(defaultColor);
                        displayStrip(LEDcolorR, LEDcolorG, LEDcolorB);
                        
		}
                #endif
                #if DCFMODUL && !RTCLOCK
                if(testMinutes != minute() || testHours != hour() || dhtaktion || colorchange) {
			dhtaktion = false;    //dht not in aktion
                        clockaktion = true;    //Clock in aktion
                        colorchange = false;  //color not change over serial 
                        testMinutes = minute();
                        #if  RUNDECLOCK
                          testMinutes = testMinutes + 2;
                        #endif
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

void clockLogiColor() {
  
  if(millis() >= waitUntilClock) {
		DEBUG_PRINT("Uhrzeit Mode Color");
		waitUntilClock = millis();
		//DateTime now = RTC.now();
                clockaktion = true;    //Clock in aktion
                if(testMinutes != minute() || testHours != hour() || dhtaktion) {
			dhtaktion = false;    //dht not in aktion 
                        testMinutes = minute();
		  	testHours = hour();
                        defaultColor = nextColor();
			resetAndBlack();
			timeToStrip(testHours, testMinutes);
			displayStrip(defaultColor);

		}
		waitUntilClock += oneSecondDelay;
	}
}
