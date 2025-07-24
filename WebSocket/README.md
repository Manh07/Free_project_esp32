# 🌐 ESP32 WebSocket Server

This project demonstrates how to use the ESP32 as a WebSocket server to control an onboard LED (GPIO 2) via a web interface, with real-time state updates for all connected clients.

## 📝 Features

- Real-time bidirectional communication using WebSocket protocol
- Control the onboard LED (GPIO 2) from a web page
- All clients receive instant state updates
- Simple, responsive web interface

## 🛠 Hardware

- ESP32 DevKit
- Onboard LED (GPIO 2) or external LED

## 🚀 How to use

1. Install the required libraries via Arduino Library Manager or from the GitHub links above
2. Open `src/websocket_server.ino` in Arduino IDE
3. Set your WiFi `ssid` and `password`
4. Upload the code to your ESP32
5. Open Serial Monitor to get the ESP32 IP address
6. Open the IP address in your browser to control the LED and see real-time updates

## 📄 License

MIT License – Free to use and modify. See [LICENSE](../../LICENSE)
