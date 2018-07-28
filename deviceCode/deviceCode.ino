#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            D5
#define DHTTYPE           DHT11 

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
 
  Serial.begin(115200);    //Serial connection
  WiFi.begin("SSID", "Password");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }

  digitalWrite(D4, HIGH); //Turn board LED on when conncetion succeed
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
 
}
 
void loop() {
  
 sensors_event_t event;  
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   dht.temperature().getEvent(&event);
   float temerature = event.temperature * 1.8 + 32; 
   dht.humidity().getEvent(&event);
   float humidity = event.relative_humidity;
   
   HTTPClient http;    //Declare object of class HTTPClient
   http.begin("http://<server address>:3000/log?room=X15&temp="+ String(temerature)+"&humidity="+ String(humidity));      //Request
 
   int httpCode = http.POST("Message from ESP8266");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(5000);  //Send a request every 5 seconds
 
}
