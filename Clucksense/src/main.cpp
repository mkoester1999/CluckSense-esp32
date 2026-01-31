#include <Arduino.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include "../include/dataSender.h"

bool wifiSetup();

void setup() {
    //serial setup
    Serial.begin(115200);

    bool res = wifiSetup();
    if(res){
      Serial.println("Connected");
      //preferences writes to persistent memory
      Preferences prefs;
      prefs.begin("config", false);
      String uuid = prefs.getString("uuid", "");
      if(uuid == ""){
        uuid = getUUID();
        prefs.putString("uuid", uuid);
      }
      prefs.end();
      Serial.println(uuid);
    }
    else{
      Serial.println("Not Connected.");
      exit(1);
    }
}

void loop() {
  //get info and send in one line
  delay(1000);
  //espnow stuff
}

bool wifiSetup(){
    //wifi manager
    WiFiManager wm;

    //try to connect
    Serial.println("Open phone now!");
    
    bool res;
    return res = wm.autoConnect();
}

