#include <SoftwareSerial.h>

SoftwareSerial btSerial(12, 11); // RX | TX
 
void setup() {
  Serial.begin(57600);
  
  btSerial.begin(38400);  // HC-05 default speed in AT command more

Serial.println("connected"); 
if (btSerial.available()) {
  Serial.println("Input AT: ");
}

}
 
void loop() {

  if (btSerial.available()) {
  Serial.println("Input AT: ");
}

  if (btSerial.available())  Serial.write(btSerial.read());
  if (Serial.available())    btSerial.write(Serial.read());
}
