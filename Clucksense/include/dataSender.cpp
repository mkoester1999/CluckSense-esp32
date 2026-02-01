#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//api endpoint urls :)
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
String sendData(String msg){
    //send the server our sensor readings
    HTTPClient http;
    http.begin(SENDURL); 
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(msg);

    //recieve response
    if (httpCode > 0) {
        String response = http.getString();
        Serial.println(response);
        //unpack response, to be sent to sensor node by main. 
        StaticJsonDocument<128> doc;
        deserializeJson(doc, response);
        String csv = String(doc["doorOpen"].as<int>()) + "," +
             String(doc["doorClosed"].as<int>()) + "," +
             String(doc["targetTemp"].as<int>());

        Serial.println(csv);
        return(csv);
    }
    else{
      //we dont really care if this fails sometimes.
      Serial.printf("POST failed: %s\n", http.errorToString(httpCode).c_str());
      return "";
    }
    http.end();
}