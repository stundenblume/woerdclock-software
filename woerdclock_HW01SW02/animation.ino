void animation() {
	if(millis() >= waitUntilHeart) {
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
	}
}
