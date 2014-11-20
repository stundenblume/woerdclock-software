void doIRLogic() {
	uint8_t brightness = 0;
	if (irrecv.decode(&irDecodeResults)) {
		DEBUG_PRINT("Received IR code");
		delay(50);
		switch(irDecodeResults.value) {
			case ONOFF:
				displayMode = ONOFF;
				break;
			case AUTO:
				autoBrightnessEnabled = !autoBrightnessEnabled;
				break;
			case BLUE_DOWN:
				//TODO
				break;
			case BLUE_UP:
				//TODO
				break;
			case BRIGHTER:
				autoBrightnessEnabled = false;
				brightness = FastLED.getBrightness();
				if(brightness <= 255 - 50) {
					FastLED.setBrightness(brightness + 50);
				} else {
					FastLED.setBrightness(255);
				}
				FastLED.show();
				break;
			case DIM:
				autoBrightnessEnabled = false;
				brightness = FastLED.getBrightness();
				if(brightness >= 50) {
					FastLED.setBrightness(brightness - 50);
				} else {
					FastLED.setBrightness(0);
				}
				FastLED.show();
				break;
			case DIY1:
				displayMode = DIY1;
				autoBrightnessEnabled = true;
				//to force display update
				testMinutes = -1;
				testHours = -1;
				break;
			case DIY2:
				displayMode = DIY2;
				break;
			case DIY3:
				displayMode = DIY3;
				break;
			case DIY4:
				displayMode = DIY4;
				break;
			case DIY5:
				displayMode = DIY5;
				break;
			case DIY6:
				displayMode = DIY6;
				break;
			case FLASH:
				displayMode = FLASH;
				break;
			case QUICK:
				defaultColor = nextColor();
				displayStrip();
				break;
			case SLOW:
				defaultColor = prevColor();
				displayStrip();
				break;
			default:
				DEBUG_PRINT("IR DEFAULT");
				break;
		}
		irrecv.resume();
	}
}
