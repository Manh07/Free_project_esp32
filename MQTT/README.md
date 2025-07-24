# ESP32 MQTT – Publish BME280 Sensor Readings (Temperature, Humidity) and Control Output

This project demonstrates how to use the ESP32 as an MQTT client to:

- Publish temperature and humidity readings from a BME280 sensor.
- Subscribe to MQTT messages to control an LED output.

It integrates with a **Mosquitto MQTT broker** (e.g., on Raspberry Pi/Laptop) and a **Node-RED dashboard**.

### MQTT Topics Used:
- **Publish**:
  - `esp32/temperature`
  - `esp32/humidity`
- **Subscribe**:
  - `esp32/output`

## 📦 Components Used
- ESP32 Dev Board
- BME280 Sensor (I2C)
- LED (GPIO 4)
- Mosquitto MQTT Broker (e.g., on Raspberry Pi/laptop)
- Node-RED
- Node-RED Dashboard

## 🧠 Features
- Connects to Wi-Fi
- Reads temperature & humidity every 5s from BME280
- Publishes sensor data to MQTT topics
- Subscribes to `esp32/output` to control onboard LED
- Works with any MQTT dashboard
- Access any browser in your local network and type: http://Your_RPi_IP_address:1880/ui

## 🔧 How It Works
1. ESP32 connects to Wi-Fi and MQTT broker.
2. Every 5 seconds:
   - Reads temperature and humidity.
   - Publishes readings to `esp32/temperature` and `esp32/humidity`.
3. Listens for messages on topic `esp32/output`:
   - `"on"` → turns LED on.
   - `"off"` → turns LED off.

## 📄 License
MIT License – Free to use and modify. See [LICENSE](../../LICENSE)