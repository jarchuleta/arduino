#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h> 
#include "config.h" 

WiFiManager wifiManager;
ESP8266WebServer server(80);

void setup() {
   Serial.begin(115200);
   
    //reset saved settings
    //wifiManager.resetSettings();



   // put your setup code here, to run once:
   wifiManager.autoConnect();

  

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", []() {
    String message = "";

    message += "Pin 0:";
    message += digitalRead(2);


    server.send(200, "text/html", message);
  });


  server.begin();
}

int flag = 0;
void loop() {
  server.handleClient();


  if (digitalRead(2) == 0 && flag == 0) {
    Serial.println("Open");
    makerdoor_status();
    flag = 1;

  }

  if (digitalRead(2) == 1 && flag == 1) {
    flag = 0;
    Serial.println("Close");

  }

}


const char* host = "maker.ifttt.com";
const char* apiKey = "eNdr5Ubz3_s8BDc5n9xXXukMWzSGahUxVmQgw5jHk_H";
void makerdoor_status() {

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/trigger/Door_status/with/key/";
  url += apiKey;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: 13\r\n\r\n" +
               "value1=opened\r\n");

  delay(10);

}

