# 📲 ESP32 Bluetooth Classic Serial

This project demonstrates how to use ESP32's **Bluetooth Classic** (SPP) with Arduino IDE.

## 📋 Features
- Bridge between Serial Monitor and Bluetooth serial terminal on Android.
- Send DS18B20 temperature readings every 10s.
- Accept commands "led_on"/"led_off" to toggle LED (GPIO 25).

## 🚀 How to use
1. Connect DS18B20 to GPIO 32 and LED to GPIO 25.
2. Open `bt_serial.ino` in Arduino IDE.
3. Install `DallasTemperature` and `OneWire` libraries.
4. Upload to ESP32.
5. Pair with Android phone and open "Serial Bluetooth Terminal".
6. Send commands or receive readings via Bluetooth.

## 🛠️ Dependencies
- `BluetoothSerial.h` (built into ESP32 Arduino core)
- `OneWire` + `DallasTemperature`

## 📄 License
MIT License – Free to use and modify. See [LICENSE](../LICENSE)
