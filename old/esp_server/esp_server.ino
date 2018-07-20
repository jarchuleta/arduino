
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>



const char* ssid = "Bluewaves";
const char* password = "JamesIsTheKing";


ESP8266WebServer server(80);


void setup() {
  Serial.begin(115200);
 

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(2, INPUT);


  server.on("/", []() {
    String message = "";

    message += "Pin 0:";
    message += "<br>";
    message += "Pin 1:";
    message += "<br>";
    message += "Pin 2:";
    message += digitalRead(2);
    message += "<br>";
    message += "Pin 3:";
    message += "<br>";
    message += "Pin 4:";
    message += "<br>";

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

  delay(10);
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


