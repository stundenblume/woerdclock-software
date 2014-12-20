#include "DHT.h"
#include <Wire.h>
#include "RTClib.h"

//----MODULE----//
#define DHTMOD 1
#define RTCCLK 0
#define MIC 0
#define LDRMOD 1

//----PINS----//

#define DHTPIN 6     // what pin we're connected to
#define MICPIN 0
#define LDRPIN A6
#define BUTTONS 4


#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600); 
 
  dht.begin();
  
  
  #ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
}

void loop() {

  // Wait a few seconds between measurements.
  delay(2000);
  
  Serial.println("------ Module Test ------");
  
  #if DHTMOD
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  Serial.println("--> DHT11 Module <--");
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial.println();
    
  } else {

 
    
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.println(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C ");
    Serial.println();
  }
 
  #endif
  
  #if RTCCLK
  
    DateTime now = rtc.now();
    Serial.println("--> RTC I2C Module <--");
    
    Serial.print("Datum: ");
    
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.println('/');
    
    Serial.print("Zeit: ");
    
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    //Serial.print(" since midnight 1/1/1970 = ");
    Serial.print("Unixtime: ");
    Serial.println(now.unixtime());
    //Serial.print("s = ");
    //Serial.print(now.unixtime() / 86400L);
    //Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    //DateTime future (now.unixtime() + 7 * 86400L + 30);
    /*
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    */
    Serial.println();
  #endif

  
  #if LDRMOD
  
  Serial.println("--> LDR Module <--");
  int LDRReading = analogRead(LDRPIN);
  Serial.println("Helligkeit: "); 
  Serial.println(LDRReading);
  
  #endif
  
  #if MICMOD
  
  #endif
  
}
