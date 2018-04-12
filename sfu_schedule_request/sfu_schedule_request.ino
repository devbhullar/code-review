#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "ZTE_A1";
const char* password = "ztepass";

const String year = "2016";
const String term = "Summer";
const String department = "mse";
const String courseNumber = "320";
const String courseSection = "d100";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    Serial.println("Connecting to internet with WiFi...");
    delay(1000); 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { // If WiFi is connected
 
    HTTPClient http;

    String url = "http://www.sfu.ca/bin/wcm/course-outlines?" + year + "/" + term + "/" + department + "/" + courseNumber + "/" + courseSection; // REST API request url

    http.begin(url);
    int httpReturn = http.GET();                                                                 
 
    if (httpReturn > 0) { 
 
      String receivedData = http.getString();   
      Serial.println(receivedData);
    }
 
    http.end();   //Close connection
 
  }
 
  delay(10000);
 
}