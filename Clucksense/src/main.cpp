#include <Arduino.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include "../include/dataSender.h"
#include "../include/uartcom.h"

bool wifiSetup();
void send_espcom_msg(uint8_t command, bool door_status, int8_t temp);
//mac addresses of different peripherals
uint8_t door_controller_addr[] = {0xCC, 0x7B, 0x5C, 0xA7, 0xEC, 0xF8};
//global uuid :)
String uuid;

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

#define TX_PIN 17
#define RX_PIN 16

//static pointers for checking if values are null before sending
static bool* door = nullptr;
static int* temp = nullptr;
static int* humidity = nullptr;
static bool* food = nullptr;
static bool* water = nullptr;


void readUART(SensorData* _status);


//init sensorData
static SensorData latestData;
static bool haveData = true;

//Timer data for sending to server
static unsigned long lastSendMs = 0;
constexpr unsigned long SEND_INTERVAL_MS = 5000;

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

    //init uart communication
    uart_link_begin(1, 115200, RX_PIN, TX_PIN);
}

void loop() {

  // ---- Continuously read UART ----
  SensorData incoming;
  if (uart_read_sensor(incoming)) {
    latestData = incoming;
    haveData = true;
  }

  // ---- Periodic send to server ----
  unsigned long now = millis();
  if (haveData && (now - lastSendMs >= SEND_INTERVAL_MS)) {
    lastSendMs = now;

    // You already have this:
    sendData("test");
  }

  // Keep loop responsive
  delay(5);
}

bool wifiSetup(){
  //wifi manager
  WiFiManager wm;

  //try to connect
  bool res;
  return res = wm.autoConnect();
}