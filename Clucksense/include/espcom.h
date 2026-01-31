#ifndef ESP_COMM_H
#define ESP_COMM_H

#include <Arduino.h>
#include <esp_now.h>

// Declaration of functions and external variables
extern void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);
extern int init_esp_now(const uint8_t *mac_addr);

// Message struct for communication
typedef struct struct_message 
{
  uint8_t command;
  bool door_status;
  int8_t temp;
} struct_message;

extern struct_message command;
extern esp_now_peer_info_t peerInfo; // Declare peerInfo here as extern

#endif
