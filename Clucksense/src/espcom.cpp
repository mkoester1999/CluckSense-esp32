#include "espcom.h"  // Include the header file for declarations

// Broadcast address used to get all other devices
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  // Broadcast to all devices

// Definition of peerInfo (global for ESP-NOW)
esp_now_peer_info_t peerInfo;  // Define peerInfo here

// Callback function for when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("Delivery Success");
    } else {
        Serial.println("Delivery Fail");
    }
}

// Initialize ESP-NOW and set up the peer (broadcast)
int init_esp_now()
{
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return 1;
    }

    // Register the send callback function
    esp_now_register_send_cb(OnDataSent);

    // Register the peer (broadcast all messages)
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);  // Set broadcast address
    peerInfo.channel = 0;  // Use the current Wi-Fi channel
    peerInfo.encrypt = false;  // Don't use encryption for simplicity

    // Add the peer to the ESP-NOW network
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return 1;
    }

    return 0;
}

// Send a broadcast message using ESP-NOW
void send_broadcast_message(struct_message *msg)
{
    // Send the struct as a message over ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)msg, sizeof(struct_message));

    if (result == ESP_OK) {
        Serial.println("Message sent successfully!");
    } else {
        Serial.println("Error sending message");
    }
}
