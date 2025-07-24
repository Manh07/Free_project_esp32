/*
 * Project: ESP32 Bluetooth Classic Serial
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Uses ESP32's Bluetooth Classic (SPP) to bridge
 * between Serial Monitor and a smartphone terminal app.
 * Also sends DS18B20 temperature readings every 10s
 * and toggles LED via commands "led_on" / "led_off".
 */

#include "BluetoothSerial.h"
#include <OneWire.h>
#include <DallasTemperature.h>

BluetoothSerial SerialBT;

const int ledPin = 25;
const int oneWireBus = 32;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

unsigned long lastTemp = 0;
const long tempInterval = 10000;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Test");
  sensors.begin();
  Serial.println("BT Serial started. Pair and connect via phone.");
}

void loop() {
  if (Serial.available()) SerialBT.write(Serial.read());
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim();
    if (cmd == "led_on") digitalWrite(ledPin, HIGH);
    else if (cmd == "led_off") digitalWrite(ledPin, LOW);
  }

  if (millis() - lastTemp >= tempInterval) {
    lastTemp = millis();
    sensors.requestTemperatures();
    float t = sensors.getTempCByIndex(0);
    String msg = "Temp: " + String(t) + " C";
    SerialBT.println(msg);
    Serial.println(msg);
  }
}
