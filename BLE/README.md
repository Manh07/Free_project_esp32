# 📶 ESP32 BLE Server & Client

Demonstrates ESP32 acting as a BLE server and client using Arduino IDE (no images included).

## 🔧 Features
- **Server**: advertises temperature & humidity characteristics; notifies new values every 5 seconds. You can use nRF Connect for Mobile to check data
- **Client**: scans for server, connects, reads temp & humidity, prints to Serial.

## 🚀 How to use
1. Open `ble_server.ino` and `ble_client.ino` in Arduino IDE.
2. Flash each to separate ESP32 boards.
3. Open Serial Monitor (115200 baud).
4. Client will display readings from the server periodically.

## 🛠️ Dependencies
- BLE support via `ESP32 BLE Arduino` library (included in ESP32 Arduino core).

## 📄 License
MIT License – Free to use and modify. See [LICENSE](../../LICENSE).
