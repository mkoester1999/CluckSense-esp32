#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* UUIDURL = "http://www.clucksense.com/api/generate-code";

String getUUID() {
  HTTPClient http;
  http.begin(UUIDURL); 

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    // Get the response body as a raw string
    String payload = http.getString();
    http.end();
    
    //parse json
    StaticJsonDocument<128> doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err) {
        Serial.println("JSON parse failed");
        exit(1);
    }
    //return the uuid
    return doc["data"].as<String>();
  } else {
    Serial.printf("HTTP GET failed, code: %d\n", httpCode);
    exit(1);
    http.end();
  }
}

void sendData(int, int, bool, bool){
    
}