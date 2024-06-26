#include <ArduinoJson.h>
#include "MotionSensor.h"

static const char* topicsToListen[] = { nullptr };

MotionSensor::MotionSensor() {}

void MotionSensor::init() {
    pinMode(pin, INPUT);
}

void MotionSensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int val = digitalRead(pin);
    if (val != previousVal) {
      previousVal = val;
      StaticJsonDocument<1000> doc;
      doc["motion"] = val ? "true":  "false";
      doc["time"] = currentMillis;

      char jsonBuffer[1000];
      size_t n = serializeJson(doc, jsonBuffer);

      publishMessage("motion/status", jsonBuffer);
    }
  }
}

void MotionSensor::handleMessage(const String& topic, const String& message) {}

const char** MotionSensor::getSubscribeTopics() {
  return topicsToListen;
}
