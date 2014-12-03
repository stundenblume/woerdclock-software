#if DHT11

void dhtRead(){
  // Wait a few seconds between measurements.
  if(DHT_TIMER >= 5000){
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humi = dht.readHumidity();
  // Read temperature as Celsius
  temp = dht.readTemperature();

  
  // Check if any reads failed and exit early (to try again).
    if (isnan(humi) || isnan(temp)) {
      #ifdef DEBUG
      Serial.println("Failed to read from DHT sensor!");
      #endif
      return;
    }

  // Compute heat index
  // Must send in temp in Fahrenheit!
//  float hi = dht.computeHeatIndex(f, h);
//  int dht11_temp =
#ifdef DEBUG
  Serial.print("Feuchte:");
  Serial.print(humi);
  Serial.println(" %");
  Serial.print("Temperatur: "); 
  Serial.print(temp);
  Serial.print(" *C ");
  Serial.println();
#endif
  
  int firstnumber = temp/10;
  int secondnumber = temp%10;
  int check = 0;
  if (firstnumber > 0){
    writedht(firstnumber); 
  }
  writedht(secondnumber);
  
  DHT_TIMER = 0;
  } 
  else {
#ifdef DEBUG   
  Serial.print(DHT_TIMER);
#endif   
  DHT_TIMER++;
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
