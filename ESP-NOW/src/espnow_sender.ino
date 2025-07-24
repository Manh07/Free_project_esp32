/*
 * Project: ESP-NOW Communication (Sender)
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * This ESP32 sends messages to another ESP32 using ESP-NOW protocol.
 */

#include <esp_now.h>
#include <WiFi.h>

// Structure to send data
typedef struct struct_message {
  int id;
  float value;
} struct_message;

struct_message messageToSend = {1, 42.0};

// MAC Address of the receiver (replace with your board's MAC)
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Delivery status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &messageToSend, sizeof(messageToSend));

  if (result == ESP_OK) {
    Serial.println("Sent successfully");
  } else {
    Serial.println("Error sending the data");
  }

  delay(2000);
}
