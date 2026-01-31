#include <Arduino.h>
#include <WiFiManager.h>

void setup() {
    //serial setup
    Serial.begin(115200);

    bool res = wifiSetup();
}

void loop() {
  
}

bool wifiSetup(){
    //wifi manager
    WiFiManager wm;

    //try to connect
    Serial.println("Open phone now!");
    
    bool res;
    if(res){
      Serial.println("Connected.");
    }
    else{
      Serial.println("Failed to connect.");
    }
    return res = wm.autoConnect();
}