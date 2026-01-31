#include "espcom.h"  // Include the header file

// Broadcast address used to get all other devices
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// **Definition of peerInfo** (this is the line that was missing)
esp_now_peer_info_t peerInfo;  // Define peerInfo here

// Callback function for when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"); 
}

int init_esp_now(uint8_t* mac_addr)
{
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return 1;
    }

    // Set up callback for async
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    // Will currently broadcast all messages. Insecure but okay for this case
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return 1;
    }

    return 0;
}
