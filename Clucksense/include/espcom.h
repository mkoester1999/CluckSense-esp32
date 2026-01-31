#ifndef ESP_COMM_H
#define ESP_COMM_H

#include <Arduino.h>
#include <esp_now.h>

// Define the struct for the message to be sent
typedef struct struct_message {
  uint8_t command;   // Command byte
  bool door_status;  // Door status (open/close)
  int8_t temp;       // Temperature value (signed 8-bit integer)

} struct_message;

typedef struct peripheral_resp
{
  uint8_t type;
  bool door_status;
  int8_t temp;
  int8_t humidity;
  bool food;
  bool water;

}peripheral_resp;

// Function declarations
extern void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);
extern int init_esp_now();
extern void send_broadcast_message(struct_message *msg);
extern void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

// accessors for checking & getting last message
extern bool espcom_check_msg_recv();
extern bool espcom_get_last_message(peripheral_resp* msg);

// Broadcast address used to get all other devices
extern uint8_t broadcastAddress[];

// Define peerInfo globally to register the peer device
extern esp_now_peer_info_t peerInfo;

extern peripheral_resp myResp;


#endif // ESP_COMM_H

