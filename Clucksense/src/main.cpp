#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include <LiquidCrystal_I2C.h>
#include "../include/dataSender.h"

#define TX_PIN 17
#define RX_PIN 16

bool wifiSetup();
String uuid;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  //connect to wifi
  bool res = wifiSetup();
  if(res){
    Preferences prefs;
    prefs.begin("config", false);
    uuid = prefs.getString("uuid", "");
    if(uuid == ""){
      uuid = getUUID();
      prefs.putString("uuid", uuid);
    }
    prefs.end();
  }else{
    Serial.println("Failed to Connect.");
    exit(1);
  }
  lcd.setCursor(0,0);
  lcd.print(uuid);
  //init uart connection on serial2 (tx2 and rx2)
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop(){
  //recieve sensor data
  if (Serial2.available()) {
      String msg = Serial2.readStringUntil('\n');
      StaticJsonDocument<256> doc;
      deserializeJson(doc, msg);

      doc["coopID"] = "Coop_1";

      String out;
      serializeJson(doc, out);
      Serial.println(out);
      //update coop ai
      sendData(out);
  }
  //update coop api
  //send commands
  
}

bool wifiSetup(){
  //wifi manager object
  WiFiManager wm;

  //try to connect
  bool res;
  return res = wm.autoConnect("CluckSense_Config");
}