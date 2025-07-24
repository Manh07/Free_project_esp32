# 📡 ESP32 WiFi Mesh (painlessMesh)

This project demonstrates how to set up a simple WiFi mesh network using the painlessMesh library on ESP32 (and ESP8266). All nodes broadcast messages to each other in a self-organizing, self-healing mesh network.

## 📝 Features

- True mesh network: no central controller or router required
- All nodes can send and receive broadcast messages
- Self-organizing, self-healing network
- Compatible with both ESP32 and ESP8266

## 🛠 Hardware

- 2 or more ESP32 (or ESP8266) boards

## 📦 Dependencies

- [painlessMesh](https://github.com/gmag11/painlessMesh)    
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [TaskScheduler](https://github.com/arkhipenko/TaskScheduler)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) (ESP32 only)

> Install all libraries via Arduino Library Manager or from the links above.

## 🚀 How to use

1. Install the required libraries
2. Open `src/none.ino` in Arduino IDE
3. Upload the code to 2 or more ESP32/ESP8266 boards
4. Open Serial Monitor (115200 baud) on each board
5. Watch the broadcast messages and mesh events in real time

## 📄 License

MIT License – Free to use and modify. See [LICENSE](../../LICENSE)

## 🗂 Examples

- **mesh_sensor_broadcast.ino**: Each node broadcasts a simulated sensor value (random number) as JSON. All nodes print received data to Serial.
