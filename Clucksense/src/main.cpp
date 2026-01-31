#include <Arduino.h>
#include <ArduinoJson.h>
#define TX_PIN 17
#define RX_PIN 16

void setup() {
  Serial.begin(115200);

  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop(){
  //recieve sensor data
  if (Serial2.available()) {
      String msg = Serial2.readStringUntil('\n');
      StaticJsonDocument<256> doc;
      deserializeJson(doc, msg);

      doc["coopID"] = "12345678";

      String out;
      serializeJson(doc, out);
      Serial.println(out);
      //update coop ai

  }
  //update coop api
  //send commands
  
}