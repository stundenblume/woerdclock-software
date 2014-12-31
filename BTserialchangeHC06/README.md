BTserialchangeHC06
===================

- is a part of wördclock, an Arduino powered and WS2812B featured Wordclock.
- This is a standalone sketch.
- You can use it to modify your bluetooth module HC-06 with an Arduino.
- No serial monitor is required.

How to connect:
- Arduino (5V) with BT (Vcc)
- Arduino (Gnc) with BT (Gnc)
- Arduino (pin 2) with BT (TX)
- Arduino (pin 3) with BT (RX)
- Arduino (pin 7) with BT (KEY Pin)

How to use it: At first, modify the sketch:
* set the actual baudrate of the bluetooth module, see manual of the module 
- with mySerial.begin(9600);
* set the new name with 
- mySerial.print("AT+NAMEWC-HC06-BD9600");
- where WC-HC06-BD9600 is the new name
* set the new baudrate with
- mySerial.print("AT+BAUD4");
- where BAUD4 is for 9600baud

Then install the sketch on the Arduino and reboot it.

Ready.

If you have changed the baudrate, you have a new baudrate.
Set this baudrate as actual baudrate for new changes.
