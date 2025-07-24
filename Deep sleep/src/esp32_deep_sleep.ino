/*
 * Project: ESP32 Deep Sleep Demo
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Demonstrates deep sleep wake-up via timer, touch, and push button
 */

#include <WiFi.h>    // not used, included for completeness
#define uS_TO_S_FACTOR 1000000ULL  // microseconds to seconds
#define TIME_TO_SLEEP  10         // sleep duration in seconds

RTC_DATA_ATTR int bootCount = 0;

void printWakeupReason(){
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  switch(reason){
    case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup: TIMER"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup: TOUCHPAD"); break;
    case ESP_SLEEP_WAKEUP_EXT0:
    case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup: EXTERNAL"); break;
    default: Serial.println("Wakeup: OTHER"); break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);  // wait basic startup
  ++bootCount;
  Serial.println("Boot Count: " + String(bootCount));
  printWakeupReason();

  // --- WAKEUP CONFIG ---
  // 1. Timer wake-up
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  
  // 2. Touch wake-up on T4 (GPIO 13)
  touchAttachInterrupt(T4, NULL, 40);  // threshold = 40
  esp_sleep_enable_touchpad_wakeup();

  // 3. External wake-up on GPIO 33 (EXT0)
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);

  Serial.println("Entering deep sleep for " + String(TIME_TO_SLEEP) + " seconds/await event");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
  // won't be called
}
