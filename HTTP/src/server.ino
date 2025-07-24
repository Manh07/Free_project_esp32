/*
 * Project: ESP32 Wi‑Fi HTTP Server (AP Mode)
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Creates an ESP32 AP + HTTP Server that responds to client GET requests:
 * - /temperature → returns BME280 temperature
 * - /humidity    → returns BME280 humidity
 */

#include <WiFi.h>
#include <Adafruit_BME280.h>

const char* ssid = "ESP32-AP";
const char* password = "12345678";

WiFiServer server(80);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1);
  }

  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("GET /temperature") >= 0) {
      float t = bme.readTemperature();
      client.printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%.2f", t);
    } else if (request.indexOf("GET /humidity") >= 0) {
      float h = bme.readHumidity();
      client.printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%.2f", h);
    } else {
      client.print("HTTP/1.1 404 Not Found\r\n\r\n");
    }
    delay(1);
    client.stop();
  }
}
