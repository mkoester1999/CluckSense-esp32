#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include <LiquidCrystal_I2C.h>
#include "../include/dataSender.h"

//uart pins
#define TX_PIN 17
#define RX_PIN 16

//wifi and lcd
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
  //print uuid to the user so they can pair with their phone.
  lcd.setCursor(0,0);
  lcd.print(uuid);
  //init uart connection on serial2 (tx2 and rx2)
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop(){
  //recieve sensor data, if there is any
  if (Serial2.available()) {
      String msg = Serial2.readStringUntil('\n');
      StaticJsonDocument<256> doc;
      deserializeJson(doc, msg);

      //append the coop id, the uuid
      doc["coopID"] = "Coop_1"; //change to uuid eventually

      String out;
      serializeJson(doc, out);
      //update coop
      String command = sendData(out);
      if(command != ""){
        Serial2.printf("%s\n", command);
        //Serial2.printf("DoorOpen,1\ntargetTemp,60");
      }
      //Serial2.printf("doorOpen,1\ntargetTemp,60\n");
  }
}

bool wifiSetup(){
  //wifi manager object
  WiFiManager wm;

  //try to connect
  bool res;
  return res = wm.autoConnect("CluckSense_Config");
}