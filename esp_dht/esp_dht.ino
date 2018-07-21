#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>  

#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2




ESP8266WebServer server(80);

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266

float humidity, temp_f;  // Values read from sensor
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000; 



void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   

    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature(true);     // Read temperature as Fahrenheit
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

void handle_root() {
  gettemperature();
  server.send(200, "text/html", "Hello from the weather esp8266. <br> Temp:"+String((int)temp_f)+" Humidity: "+String((int)humidity)+"% <br> <a href=\"/temp\">/temp</a> or <a href=\"/humidity\">/humidity</a>");
  delay(100);
}



WiFiManager wifiManager;
void setup() { 

gettemperature();
String sTemp =  "Temp:"+String((int)temp_f)+" Humidity: "+String((int)humidity)+"% ";

char temp[100];

sTemp.toCharArray(temp,100);
wifiManager.setCustomHeadElement(temp);
// set up a custom page for temp dispaly. 

 //reset saved settings
    wifiManager.resetSettings();

dht.begin();           // initialize temperature sensor

   Serial.begin(115200);
  // put your setup code here, to run once:
  wifiManager.autoConnect();

  

 //if you get here you have connected to the WiFi
 Serial.println("connected...yeey :)");

Serial.println("");
  Serial.println("DHT Temperature Reading Server");
  wifi_station_set_hostname("ESP Temperature");
  //Serial.print("Connected to ");
  //Serial.println(ssid);
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());

 server.on("/", handle_root);
  
  server.on("/temp", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    gettemperature();       // read sensor
    webString="Temperature: "+String((int)temp_f)+" F";   // Arduino has a hard time with float to string
    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });

  server.on("/humidity", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    gettemperature();           // read sensor
    webString="Humidity: "+String((int)humidity)+"%";
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });
  
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
   server.handleClient();

}




