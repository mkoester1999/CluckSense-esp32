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

// Function declarations
extern void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);
extern int init_esp_now();
extern void send_broadcast_message(struct_message *msg);

// Broadcast address used to get all other devices
extern uint8_t broadcastAddress[];

// Define peerInfo globally to register the peer device
extern esp_now_peer_info_t peerInfo;

#endif // ESP_COMM_H
