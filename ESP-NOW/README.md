# ESP32 ESP-NOW Communication

This project demonstrates how to set up **ESP-NOW** communication between two ESP32 boards using the Arduino IDE.

ESP-NOW is a wireless communication protocol developed by Espressif that allows multiple ESP32 boards to exchange data without the need for Wi-Fi.

## 🔌 Hardware Required
- Two ESP32 development boards

## 📋 Project Overview
- **Sender** ESP32 board:
  - Sends temperature readings and an ID value via ESP-NOW every second.
- **Receiver** ESP32 board:
  - Receives the data and prints it to the Serial Monitor.

## 🚀 Getting Started
### 1. Flash the receiver
- Upload `espnow_receiver.ino` to one ESP32 board.
- Open Serial Monitor and get the MAC address of that ESP32.
### 2. Update the sender
- Edit `espnow_sender.ino` and replace the line:
uint8_t broadcastAddress[] = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };

## 📜 License
This project is licensed under the MIT License – feel free to use, modify, and distribute.