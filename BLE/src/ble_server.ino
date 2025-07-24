/*
 * Project: ESP32 BLE Server
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * BLE server advertises two characteristics (e.g., temperature & humidity)
 * that can be read or notified by a BLE client.
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_TEMP_UUID      "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_HUMID_UUID     "c0b1a111-1c2d-4ab3-8fcc-6e2c9f8f1234"

BLECharacteristic *pTempCharacteristic;
BLECharacteristic *pHumidCharacteristic;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32_BLE_Server");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pTempCharacteristic = pService->createCharacteristic(
                         CHAR_TEMP_UUID,
                         BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                       );
  pHumidCharacteristic = pService->createCharacteristic(
                          CHAR_HUMID_UUID,
                          BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                        );

  pTempCharacteristic->addDescriptor(new BLE2902());
  pHumidCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEDevice::startAdvertising();
  Serial.println("BLE Server started, waiting for connections...");
}

void loop() {
  float temp = 25.0 + random(-500, 500) / 100.0;
  float humid = 60.0 + random(-300, 300) / 100.0;

  pTempCharacteristic->setValue((uint8_t*)&temp, sizeof(temp));
  pHumidCharacteristic->setValue((uint8_t*)&humid, sizeof(humid));
  pTempCharacteristic->notify();
  pHumidCharacteristic->notify();

  Serial.printf("Notified: temp=%.2f, humid=%.2f\n", temp, humid);
  delay(5000);
}
