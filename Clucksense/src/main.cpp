#include <Arduino.h>
#include <WiFiManager.h>
#include <WebServer.h>
#include <HTTPClient.h>

bool wifiSetup();
void getHelloWorld();
const char* StatusURL = "http://www.clucksense.com/api/status";

void setup() {
    //serial setup
    Serial.begin(115200);

    bool res = wifiSetup();
    if(res){
      Serial.println("Connected");
    }
    else{
      Serial.println("Not Connected.");
      exit(1);
    }

    getHelloWorld();
}

void loop() {
  
}

bool wifiSetup(){
    //wifi manager
    WiFiManager wm;

    //try to connect
    Serial.println("Open phone now!");
    
    bool res;
    return res = wm.autoConnect();
}

void getHelloWorld() {

  HTTPClient http;
  http.begin(StatusURL);  // Adjust your hostname here

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    // Get the response body as a raw string
    String payload = http.getString();

    Serial.println("Raw response:");
    Serial.println(payload);  // This is the raw string response
  } else {
    Serial.printf("HTTP GET failed, code: %d\n", httpCode);
  }

  http.end();
}