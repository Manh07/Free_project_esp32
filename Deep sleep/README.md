# 💤 ESP32 Deep Sleep Demo

This project shows how to use ESP32 **deep sleep** and wake-up in 3 ways:
1. **Timer**: wake after fixed interval (e.g., 10s)  
2. **Touch pad**: wake on touch (e.g., T4)  
3. **External**: wake on button press (e.g., GPIO 33) :contentReference[oaicite:2]{index=2}

## 📋 Features
- Count and display boot cycles using RTC memory (`bootCount`)  
- Show wake-up source in Serial Monitor  
- Supports timer, touchpad, and external button wake-up  

## 🔧 Hardware
- ESP32 Devkit board  
- Push button on GPIO 33, pulled to HIGH  
- Optional: nothing else for timer/wake  

## 🚀 Usage
1. Open `esp32_deep_sleep.ino` in Arduino IDE  
2. Upload to ESP32  
3. Open Serial Monitor (115200 baud)  
4. Watch boot count and wake-up reason logs  
5. Try timer, touchpad, or button to wake it up

## 📄 License
MIT License – Free to use and modify. See [LICENSE](../../LICENSE)
