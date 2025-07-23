/*
 * Project: ESP32 Web Server - LED Control
 * Author: David Manh
 * License: MIT License
 * 
 * Description:
 * A simple ESP32 web server to control two LEDs using Arduino IDE.
 * Access the ESP32's IP address from a browser to toggle GPIO 26 and 27.
 */

#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
WiFiServer server(80);

String header;
String output26State = "off";
String output27State = "off";

const int output26 = 26;
const int output27 = 27;

unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(output26, OUTPUT); pinMode(output27, OUTPUT);
  digitalWrite(output26, LOW); digitalWrite(output27, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    previousTime = millis();
    String currentLine = "";
    while (client.connected() && millis() - previousTime <= timeoutTime) {
      if (client.available()) {
        char c = client.read(); header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE html><html>");
            client.println("<button onclick=\"window.location.href='/26/on'\">LED26 ON</button>");
            client.println("<button onclick=\"window.location.href='/26/off'\">LED26 OFF</button>");
            client.println("</html>");
            break;
          } else currentLine = "";
        } else if (c != '\r') currentLine += c;

        if (header.indexOf("GET /26/on") >= 0) { digitalWrite(output26, HIGH); }
        if (header.indexOf("GET /26/off") >= 0) { digitalWrite(output26, LOW); }
      }
    }
    header = "";
    client.stop();
  }
}
