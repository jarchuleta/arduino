
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>




const char* ssid = "Bluewaves";
const char* password = "JamesIsTheKing";

const long interval = 3000;

const char* SERVER_IP = "192.168.0.100";



void setup() {
   Serial.begin(115200);
   delay(100);
   Serial.println("Preparing the Door Status Monitor project...");

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  


  pinMode(0, INPUT); 
  pinMode(2, INPUT);
    
}

void loop() {
  
  int val0 = digitalRead(0);
  int val2 = digitalRead(2);
  

  Serial.println("val0:" + String(val0) + " val2:"+ String(val2) );
  delay(500);
  
   
}


void post(){

        HTTPClient http;
        http.begin(SERVER_IP, 8080, "/index.php");
        http.addHeader("Content-Type", "text/plain");
        auto httpCode = http.POST("foo");
        Serial.println(httpCode);
     
        http.end();

 
}

