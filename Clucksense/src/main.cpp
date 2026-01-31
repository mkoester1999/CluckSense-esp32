#include <Arduino.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include "../include/dataSender.h"
#include "../include/espcom.h"

bool wifiSetup();
void send_espcom_msg(uint8_t command, bool door_status, int8_t temp);

//mac addresses of different peripherals
uint8_t door_controller_addr[] = {0xCC, 0x7B, 0x5C, 0xA7, 0xEC, 0xF8};


//command definitions
#define OPEN_DOOR 1;
#define CLOSE_DOOR 2;
#define SET_TEMP 3;

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
    
    //init esp-now
    init_esp_now();
    //send message
    send_espcom_msg(1, true, 0); 
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


void send_espcom_msg(uint8_t command, bool door_status, int8_t temp)
{
  struct_message myMessage;
  myMessage.command = command;
  myMessage.door_status = door_status;
  myMessage.temp = temp;

  send_broadcast_message(&myMessage);
}
