/*
 * Project: ESP32 LoRa Receiver (RFM95)
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Receives LoRa packets and prints them via Serial Monitor.
 */

#include <SPI.h>
#include <LoRa.h>

#define ss    5
#define rst   14
#define dio0  2

void setup() {
  Serial.begin(115200);
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (true);
  }
  Serial.println("LoRa Receiver ready.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String msg = "";
    while (LoRa.available()) {
      msg += (char)LoRa.read();
    }
    Serial.println("Received: " + msg);
  }
}
