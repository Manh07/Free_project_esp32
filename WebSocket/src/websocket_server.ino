/*
 * Project: ESP32 WebSocket Server (LED Control)
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * ESP32 hosts a WebSocket server and web page to control onboard LED (GPIO 2) in real-time.
 * All connected clients are updated instantly when the LED state changes.
 */

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

bool ledState = 0;
const int ledPin = 2;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 WebSocket LED Control</title>
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
  <style>body { font-family: Arial; text-align: center; margin: 0; } .button { padding: 15px 50px; font-size: 24px; color: #fff; background: #0f8b8d; border: none; border-radius: 5px; }</style>
</head>
<body>
  <h1>ESP32 WebSocket LED Control</h1>
  <h2>LED State: <span id=\"state\">%STATE%</span></h2>
  <button class=\"button\" onclick=\"toggleLED()\">Toggle</button>
  <script>
    var gateway = `ws://${window.location.hostname}/ws`;
    var ws;
    window.addEventListener('load', onLoad);
    function onLoad() { initWebSocket(); }
    function initWebSocket() {
      ws = new WebSocket(gateway);
      ws.onmessage = function(event) {
        document.getElementById('state').innerText = event.data;
      }
    }
    function toggleLED() { ws.send('toggle'); }
  </script>
</body>
</html>
)rawliteral";

String processor(const String& var) {
  if (var == "STATE") return ledState ? "ON" : "OFF";
  return String();
}

void notifyClients() {
  ws.textAll(ledState ? "ON" : "OFF");
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    if (strncmp((char*)data, "toggle", len) == 0) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    client->text(ledState ? "ON" : "OFF");
  } else if (type == WS_EVT_DATA) {
    handleWebSocketMessage(arg, data, len);
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println(WiFi.localIP());
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.begin();
}

void loop() { ws.cleanupClients(); }
