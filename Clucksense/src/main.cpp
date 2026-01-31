#include <Arduino.h>
#include <WiFiManager.h>

bool wifiSetup();

void setup() {
    //serial setup
    Serial.begin(115200);

    bool res = wifiSetup();
    if(res){
      Serial.println("Connected");
    }
    else{
      Serial.println("Not Connected.");
    }
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