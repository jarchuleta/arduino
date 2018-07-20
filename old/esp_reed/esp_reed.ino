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
    post_status("zero");
    flag = 1;
  }

  if (digitalRead(2) == 1 && flag == 1) {
    flag = 0;
    Serial.println("Close");
    post_status("one");

  }

}

  char *url = "/sensor.php"; // page
  char *host = "copyTrades-jamesarchuleta846885.codeanyapp.com"; // no http
 
void post_status(String value) {

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  

   
    String data = "key=123&name=" + (String)ESP.getChipId() + "&event=door&value=" + value;

    
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: "+ data.length() +"\r\n\r\n" +
               data + "\r\n");

  delay(10);

}

