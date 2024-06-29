#include <ArduinoJson.h>
#include "GasSensor.h"

static const char* topicsToListen[] = { nullptr };

GasSensor::GasSensor() {}

void GasSensor::init() {
    pinMode(pin, INPUT);
}

void GasSensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int val = digitalRead(pin);
    if (val != previousVal) {
      previousVal = val;
      StaticJsonDocument<1000> doc;
      doc["gas"] = val;
      doc["time"] = currentMillis;

      char jsonBuffer[1000];
      size_t n = serializeJson(doc, jsonBuffer);

      publishMessage("gas/status", jsonBuffer);
    }
  }
}

void GasSensor::handleMessage(const String& topic, const String& message) {}

const char** GasSensor::getSubscribeTopics() {
  return topicsToListen;
}
