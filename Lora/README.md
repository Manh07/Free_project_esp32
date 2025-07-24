# 📡 ESP32 LoRa (RFM95) Sender & Receiver

This project demonstrates basic LoRa communication using ESP32 and RFM95 modules.

## 🔧 Features
- Sender: Transmits “hello N” every 2s via LoRa
- Receiver: Listens and prints received packets to Serial

## 📋 Hardware
- 2× ESP32 DevKit boards
- 2× RFM95 LoRa modules (set to 868 MHz, 915 MHz or 433MHz as per your region)
- Jumper wires & breadboard

## 🚀 How to use
1. Open both sketches (`.ino`) in Arduino IDE
2. Adjust frequency if needed
3. Upload to respective ESP32 boards
4. Open Serial Monitor on both:
   - Sender prints “Sent: hello N”
   - Receiver prints “Received: hello N”

## 📄 License
MIT License – Free to use and modify. See [LICENSE](../../LICENSE)
