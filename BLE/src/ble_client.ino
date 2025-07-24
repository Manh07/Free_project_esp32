/*
 * Project: ESP32 BLE Client
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * BLE client scans for the server, connects, and reads temperature & humidity values.
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEClient.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_TEMP_UUID      "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_HUMID_UUID     "c0b1a111-1c2d-4ab3-8fcc-6e2c9f8f1234"

static BLEAdvertisedDevice* targetDevice = nullptr;
static bool doConnect = false;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      targetDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      BLEDevice::getScan()->stop();
    }
  }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() {
  if (doConnect && targetDevice) {
    BLEClient*  pClient  = BLEDevice::createClient();
    pClient->connect(targetDevice);

    BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
    auto tempChar = pRemoteService->getCharacteristic(CHAR_TEMP_UUID);
    auto humidChar = pRemoteService->getCharacteristic(CHAR_HUMID_UUID);

    if (tempChar->canRead()) {
      float temp;
      tempChar->readValue((uint8_t*)&temp, sizeof(temp));
      Serial.printf("Temp: %.2f °C\n", temp);
    }

    if (humidChar->canRead()) {
      float humid;
      humidChar->readValue((uint8_t*)&humid, sizeof(humid));
      Serial.printf("Humidity: %.2f%%\n", humid);
    }

    pClient->disconnect();
    delete targetDevice;
    targetDevice = nullptr;
    doConnect = false;
    BLEDevice::getScan()->start(30);
  }

  delay(2000);
}
