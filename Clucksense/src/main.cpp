#include <Arduino.h>
#include <WiFiManager.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "../include/espcom.h"

bool wifiSetup();
void getHelloWorld();
const char* StatusURL = "http://www.clucksense.com/api/status";

//mac addresses of different peripherals
uint8_t door_controller_addr[] = {0xCC, 0x7B, 0x5C, 0xA7, 0xEC, 0xF8};


//command definitions
#define OPEN_DOOR 1;
#define CLOSE_DOOR 2;
#define SET_TEMP 3;

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


