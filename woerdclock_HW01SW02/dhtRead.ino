#if DHT11

void dhtRead(){
  
  if(millis() >= waitUntilDHT) {
    // Wait a few seconds between measurements.
    if(DHT_TIMER >= 500){
  
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
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

  // Compute heat index
  // Must send in temp in Fahrenheit!
//  float hi = dht.computeHeatIndex(f, h);
//  int dht11_temp =
    #ifdef DEBUG
      Serial.print(F("Feuchte:"));
      Serial.print(humi);
      Serial.println(F(" %"));
      Serial.print(F("Temperatur: ")); 
      Serial.print(temp);
      Serial.print(F(" *C "));
      Serial.println();
    #endif
  
    int firstnumber = temp/10;
    int secondnumber = temp%10;
    //int check = 0;
    if (firstnumber > 0){
      writedht(firstnumber);
//      #ifdef DEBUG
//      Serial.print("firstdhttemp=");
//      Serial.print(firstnumber);
//      Serial.println(); 
//      #endif
    }
    writedht(secondnumber);
    writeChar('C');
//    #ifdef DEBUG
//      Serial.print("seconddhttemp=");
//      Serial.print(secondnumber);
//      Serial.println(); 
//     #endif
  
    DHT_TIMER = 0;
    } 
    else {
//    #ifdef DEBUG
//    Serial.print("DHTtimer=");   
//    Serial.print(DHT_TIMER);
//    Serial.println();
//    #endif   
    DHT_TIMER++;
    }
   waitUntilDHT += oneSecondDelay; 
  } 
}

void writedht(int check){

    for(int i=1;i>10;i++){
        if (i==check) writeChar('1');
        else if (i==check) writeChar('2');
        else if (i==check) writeChar('3');
        else if (i==check) writeChar('4');
        else if (i==check) writeChar('5');
        else if (i==check) writeChar('6');
        else if (i==check) writeChar('7');
        else if (i==check) writeChar('8');
        else if (i==check) writeChar('9');
        else if (i==check) writeChar('0');
    }  
}

#endif
