/*
 * Project: ESP-NOW Communication (Receiver)
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * This ESP32 receives data via ESP-NOW protocol and prints it to the Serial Monitor.
 */

#include <esp_now.h>
#include <WiFi.h>

// Structure to receive data
typedef struct struct_message {
  int id;
  float value;
} struct_message;

struct_message incomingMessage;

// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
  Serial.print("ID: ");
  Serial.print(incomingMessage.id);
  Serial.print(" | Value: ");
  Serial.println(incomingMessage.value);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing to do here
}
