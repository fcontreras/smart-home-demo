#include <ArduinoJson.h>
#include "RaindropSensor.h"

static const char* topicsToListen[] = { nullptr };

RaindropSensor::RaindropSensor() {}

void RaindropSensor::init() {
    pinMode(pin, INPUT);
}

void RaindropSensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int val = analogRead(pin);
    if (val != previousVal) {
      previousVal = val;
      StaticJsonDocument<1000> doc;
      doc["water"] = val;
      doc["time"] = currentMillis;

      char jsonBuffer[1000];
      size_t n = serializeJson(doc, jsonBuffer);

      publishMessage("raindrop/status", jsonBuffer);
    }
  }
}

void RaindropSensor::handleMessage(const String& topic, const String& message) {}

const char** RaindropSensor::getSubscribeTopics() {
  return topicsToListen;
}
