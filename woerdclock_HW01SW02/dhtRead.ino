#if DHT11

void dhtRead(){
  // Wait a few seconds between measurements.
  if(millis() >= waitUntilDHT) {
    DEBUG_PRINT(F("DHT logic"));
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    waitUntilDHT = millis();
    humi = dht.readHumidity();
    // Read temperature as Celsius
    temp = dht.readTemperature();

  
      // Check if any reads failed and exit early (to try again).
        if (isnan(humi) || isnan(temp)) {
          #ifdef DEBUG
          Serial.println(F("Failed to read from DHT sensor!"));
          #endif
          return;
        }
      #ifdef DEBUG
        Serial.print(F("Feuchte:"));
        Serial.print(humi);
        Serial.println(F(" %"));
        Serial.print(F("Temperatur: ")); 
        Serial.print(temp);
        Serial.print(F(" *C "));
        Serial.println();
      #endif
  //make text
  #if TEXT
    int firstnumber = temp/10;      //first Number of temp
    int secondnumber = temp%10;     //second Number of temp
    //int check = 0;
    if (firstnumber > 0){           //first Number needed?
      writedht(firstnumber);        //show first Number
    }
    writedht(secondnumber);         //show second Number
    writeChar('C');                 //show C
    firstnumber = humi/10;          //first Number of humidity
    secondnumber = humi%10;         //second Number of humidity
    if (firstnumber > 0){           //first Number needed?
      writedht(firstnumber);
    } 
    writedht(secondnumber);         //show second Number
    writeChar('p');                 //show %
    dhtaktion = true;
    waitUntilDHT = millis();
    waitUntilDHT += dhtDelay;
   #endif 
  } 
}
#endif
#if TEXT
//funkction to show the right Number
void writedht(int check){            

        if (check==0) writeChar('0');
        else if (check==1) writeChar('1');
        else if (check==2) writeChar('2');
        else if (check==3) writeChar('3');
        else if (check==4) writeChar('4');
        else if (check==5) writeChar('5');
        else if (check==6) writeChar('6');
        else if (check==7) writeChar('7');
        else if (check==8) writeChar('8');
        else if (check==9) writeChar('9'); 
}
#endif
