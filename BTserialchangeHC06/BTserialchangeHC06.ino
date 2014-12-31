/*******************************************
* Name.......: BTserialchangeHC06
* Author.....: Marcel Müller
* Version....: 0.1
* Date.......: 2014-12-31
* License....: This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
		To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
* Description: Change the properties of your bluetooth module hc-06 with an Arduino e.g. Arduino Yun
- no serial monitor is required
- Arduino (5V) with BT (Vcc)
- Arduino (Gnc) with BT (Gnc)
- Arduino (pin 2) with BT (TX)
- Arduino (pin 3) with BT (RX)
********************************************/


#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {
  /* The actual baudrate of the bluetooth modul */
   mySerial.begin(9600);
  /* The new name for the bluetooth modul */
   mySerial.print("AT+NAMEWC-HC06-BD9600");
  /* The new baudrate for the modul */
   //mySerial.print("AT+BAUD4"); //BAUD4=9600, BAUD5=19200, BAUD6=38400, BAUD7=57600, BAUD8=115200 
}

void loop() {
}
