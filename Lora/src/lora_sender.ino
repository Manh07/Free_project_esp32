/*
 * Project: ESP32 LoRa Sender (RFM95)
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Sends a "hello" message + counter via LoRa RFM95 using ESP32.
 */

#include <SPI.h>
#include <LoRa.h>

#define ss    5
#define rst   14
#define dio0  2

long counter = 0;

void setup() {
  Serial.begin(115200);
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (true);
  }
  Serial.println("LoRa Sender ready.");
}

void loop() {
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter++);
  LoRa.endPacket();
  Serial.println("Sent: hello " + String(counter-1));
  delay(2000);
}
