Serial Communication Modul for Wördclock
===================

is a part of wördclock, a Arduino powered and WS2812B featured Wordclock.

This is the Serial Communication Modul for Wördclock v0.71 by Marcel Müller.
It based on parser for serial communication on Arduino by (c) 140801 Thomas Peetz

wc_serial_mode is the main programm.
serial_com.ino includes the routine for serial communication.

At first you have to select the hardware that is connected via #define ... 1
and select the hardware that you don't want to use via #define ... 0
With this, you can save memory.

The default BAUDRATE is 9600 for all ports:
Serial (=usb)
Serial (=pin 0,1)
BTSerial (=Software Serial)
BTSerial2 (=Software Serial)
Actually, wifi is not implementet, but comming soon.

The communication works passive.
Send a command and you get an answer.
For example, to check the actual color of the leds type glc for get_led_color.
You get the values like:
lc=R,G,B
This data was read from SRAM.

You can change the color with slc (=set_led_color).
For example, to get a nice red:
slc=255,0,0

This data is stored in SRAM only.
For permanent storage use slcp.
The data will be copied from SRAM to EEPROM.
The EEPROM memory has a specified life of 100,000 write/erase cycles, 
so you may need to be careful about how often you write to it.
You can check the color in EEPROM with glcp.

You can do all the same with the led brightness.

With the command help, you get the full list.
