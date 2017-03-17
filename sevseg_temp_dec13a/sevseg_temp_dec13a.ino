#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object

int val;
int tempPin = 0;

void setup() {


//Serial.begin(9600);

byte numDigits = 4;

byte digitPins[] = {2, 3, 4, 5};

byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);

sevseg.setBrightness(90);

}


unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;
float farh;
void loop() {



if((millis() - lastDebounceTime) > debounceDelay) {
  

  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;
  farh = (cel*9)/5 + 32;
  int ifa = farh;
  
  
  Serial.print("TEMPRATURE = ");
  Serial.print(farh);
  Serial.print(" *F");
  Serial.println();
  lastDebounceTime = millis();
}

sevseg.setNumber(farh, 2);
sevseg.refreshDisplay(); // Must run repeatedly


}
