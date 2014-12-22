String command = ""; // Stores response of the HC-06 Bluetooth device


void setup() {
  // Open serial communications:
  Serial.begin(9600);
  Serial.println("Type AT commands!");
  
  // The HC-06 defaults to 9600 according to the datasheet.
  Serial1.begin(9600);
}

void loop() {
  // Read device output if available.
  if (Serial1.available()) {
    while(Serial1.available()) { // While there is more to be read, keep reading.
      command += (char)Serial1.read();
    }
    
    Serial.println(command);
    command = ""; // No repeats
  }
  
  // Read user input if available.
  if (Serial.available()){
    delay(10); // The delay is necessary to get this working!
    Serial1.write(Serial.read());
  }
}
