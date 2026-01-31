#include <Arduino.h>
#include <WiFiManager.h>

void setup() {
    //serial setup
    Serial.begin(115200);

    //wifi manager
    WiFiManager wm;

    //try to connect
    Serial.println("Open phone now!");
    
    bool res;
    res = wm.autoConnect();

    if(!res){
      Serial.println("failed to connect");
    }
    else{
      Serial.println("Connected.");
    }

}

void loop() {
  
}

