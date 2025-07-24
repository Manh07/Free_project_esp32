/*
 * Project: ESP32 WiFi Mesh - Sensor Broadcast Example
 * Author: David Manh
 * License: MIT License
 *
 * Description:
 * Each node in the mesh network broadcasts a simulated sensor value (random number).
 * All nodes receive and print the sensor data from other nodes via Serial.
 *
 * Requires: painlessMesh, ArduinoJson, TaskScheduler, AsyncTCP (ESP32)
 */

#include <painlessMesh.h>

// Mesh network credentials
#define   MESH_PREFIX     "esp32-mesh"
#define   MESH_PASSWORD   "meshpassword"
#define   MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

// Function prototype
void sendSensorData();

// Task to send sensor data every 2 seconds
Task taskSendSensor(TASK_SECOND * 2, TASK_FOREVER, &sendSensorData);

// Send a random sensor value as a JSON string
void sendSensorData() {
  int sensorValue = random(0, 100); // Simulated sensor value
  String msg = "{";
  msg += "\"node\":" + String(mesh.getNodeId()) + ",";
  msg += "\"value\":" + String(sensorValue);
  msg += "}";
  mesh.sendBroadcast(msg);
}

// Callback when a message is received
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("[Sensor] Received from %u: %s\n", from, msg.c_str());
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  userScheduler.addTask(taskSendSensor);
  taskSendSensor.enable();
}

void loop() {
  mesh.update();
} 