#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//urls :)
const char* UUIDURL = "http://www.clucksense.com/api/generate-code";
const char* SENDURL = "http://www.clucksense.com/api/update-coop";

/*
  gets a fresh uuid from the database
*/
String getUUID() {
  //send get request
  HTTPClient http;
  http.begin(UUIDURL); 
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    // Get the response body as a raw string
    String payload = http.getString();
    http.end();
    
    //parse string into json
    StaticJsonDocument<128> doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err) {
        Serial.println("JSON parse failed");
        exit(1);
    }
    //return the uuid
    return doc["data"].as<String>();
    //if we couldnt contact the server for some reason
  } else {
    Serial.printf("HTTP GET failed, code: %d\n", httpCode);
    http.end();
    exit(1);
  }
}

/*
  takes the uuid, and sends all of the sensor data to the server, then it recieves some commands in response.
*/
void sendData(String msg){
    //send post
    HTTPClient http;
    http.begin(SENDURL); 
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(msg);

    //recieve response
    if (httpCode > 0) {
        String response = http.getString();
        Serial.println("Server response:");
        Serial.println(response);
        //unpack response and send to driver, to be sent to sensor node. 
    }
    else{
      Serial.printf("POST failed: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}