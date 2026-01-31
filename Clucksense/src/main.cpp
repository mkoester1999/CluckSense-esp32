#include <Arduino.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include "../include/dataSender.h"
#include "../include/espcom.h"

bool wifiSetup();
void send_espcom_msg(uint8_t command, bool door_status, int8_t temp);
void get_espcom_msg(peripheral_resp* msg);
//mac addresses of different peripherals
uint8_t door_controller_addr[] = {0xCC, 0x7B, 0x5C, 0xA7, 0xEC, 0xF8};
//global uuid :)
String uuid;

//struct of espnow Rx
peripheral_resp rxMsg;

//command definitions
#define OPEN_DOOR 1;
#define CLOSE_DOOR 2;
#define SET_TEMP 3;

//Rx type definitions
#define DOOR 1;
#define TEMP 2;
#define HUMIDITY 3;
#define WATER 4;
#define FOOD 5;

//static pointers for checking if values are null before sending
static bool* door = nullptr;
static int* temp = nullptr;
static int* humidity = nullptr;
static bool* food = nullptr;
static bool* water = nullptr;

void setup() {
    //serial setup
    Serial.begin(115200);

    //try and connect to wifi
    bool res = wifiSetup();
    if(res){
      Serial.println("Connected");
      //preferences writes the uuid to persistent memory, if already there we just pull it.
      Preferences prefs;
      prefs.begin("config", false);
      uuid = prefs.getString("uuid", "");
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
    //send test message
    send_espcom_msg(1, true, 0); 
}

void loop() {

  //listen for msg response from esp_now
  espcom_get_last_message(&rxMsg);
  //get info and send in one line
  //fill in espcom?
  sendData(uuid);
  delay(5000);
}

bool wifiSetup(){
  //wifi manager
  WiFiManager wm;

  //try to connect
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

void get_espcom_msg(peripheral_resp* msg)
{
  espcom_get_last_message(msg);
}