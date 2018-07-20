
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>




const char* ssid = "Bluewaves";
const char* password = "JamesIsTheKing";

const long interval = 3000;

ESP8266WebServer server(80);
MDNSResponder mdns;
String webPage = "";

void setup() {
   Serial.begin(115200);
   delay(100);
   Serial.println("Preparing the Door Status Monitor project...");

digitalWrite(2,LOW);

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

    if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");

    pinMode(2, OUTPUT);
    //ADC_MODE(ADC_VCC);
  }

 String message = "";

message += "<html>";
message += "<body>";

message += "<h1>Esp</h1>";

message += "LED Control:";
message += "         <form method=\"get\" >";
message += "                 <input type=\"submit\" value=\"ON\" name=\"button\">";
message += "                 <input type=\"submit\" value=\"OFF\" name=\"button\">";
message += "       </form>";

message += "</body>";
message += "</html>";




    server.on("/", [](){
       String message = "";
/*
 String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
*/

message += "<html>";
message += "<body>";

message += "<h1>Esp</h1>";


if ( server.args() > 0  && server.arg(0) == "ON" ){
  message += "Turning on LED";
  digitalWrite(2,HIGH);
  message += "<br/>";
}
if ( server.args() > 0  && server.arg(0) == "OFF" ){
  message += "Turning off LED";
  digitalWrite(2,LOW);
  message += "<br/>";
}

message += "LED Control:";
message += "         <form method=\"get\" >";
message += "                 <input type=\"submit\" value=\"ON\" name=\"button\">";
message += "                 <input type=\"submit\" value=\"OFF\" name=\"button\">";
message += "       </form>";

message += "</body>";
message += "</html>";
      
      Serial.println("webpage hit");  
    server.send(200, "text/html", message);
    
    });
 server.begin();
  Serial.println("HTTP server started");


   
}

void loop() {
   server.handleClient();

   Serial.print("Loop Voltage:");
   Serial.println(ESP.getVcc());
   delay(2000);
   
}
