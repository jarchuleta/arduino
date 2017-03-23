#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>  

WiFiManager wifiManager;

void setup() {

 //reset saved settings
    wifiManager.resetSettings();


   Serial.begin(115200);
  // put your setup code here, to run once:
  wifiManager.autoConnect();

  

 //if you get here you have connected to the WiFi
 Serial.println("connected...yeey :)");

}

void loop() {
  // put your main code here, to run repeatedly:

}
