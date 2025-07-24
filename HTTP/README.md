# 🌐 ESP32 HTTP Client-Server (Request ↔ Response)
This example shows how one ESP32 **client** requests data from another ESP32 **server** using HTTP over Wi‑Fi (no router).

## 🔌 Setup
1. Flash `server.ino` on ESP32 acting as server (AP).
   - Starts Wi‑Fi SSID: **ESP32‑AP**  
2. Flash `client.ino` on another ESP32 (client/STA).
3. Serial Monitor:
   - Server IP visible (default 192.168.4.1)
   - Client prints temperature/humidity every 5 seconds

## 🔍 How Requests Work
- Client sends: `GET /temperature`
- Server reads BME280, returns value like `23.45`
- Similarly for `GET /humidity` → humidity value
- You can use your phone connect to WiFi and check data

## ✅ Requirements
- 2x ESP32 boards
- BME280 sensor (server only)
- `WiFi`, `HTTPClient`, `Adafruit_BME280`, `Adafruit_Sensor` libraries

## 📜 License
MIT License (see `LICENSE`)
