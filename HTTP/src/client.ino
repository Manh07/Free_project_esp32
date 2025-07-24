/*
 * Project: ESP32 Wi‑Fi HTTP Client
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Connects to AP server and sends HTTP GET to:
 * - /temperature
 * - /humidity
 * Prints the received data.
 */

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-AP";
const char* password = "12345678";
const char* serverIP = "192.168.4.1";  // IP của server ESP32

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting…");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to AP");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(String("http://") + serverIP + "/temperature");
    int code1 = http.GET();
    if (code1 > 0) {
      Serial.print("Temp: ");
      Serial.println(http.getString());
    }
    http.end();

    http.begin(String("http://") + serverIP + "/humidity");
    int code2 = http.GET();
    if (code2 > 0) {
      Serial.print("Humidity: ");
      Serial.println(http.getString());
    }
    http.end();
  }
  delay(5000);
}
