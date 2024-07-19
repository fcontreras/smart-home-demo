#include <ArduinoJson.h>
#include "Button.h"

Button::Button(byte pin, const String& buttonId) {
  this->pin = pin;
  this->buttonId = buttonId;
}

void Button::init() {
  pinMode(pin, INPUT);
}

void Button::handleMessage(const String& topic, const String& message) { }

const char** Button::getSubscribeTopics() {
  static const char* topics[] = { nullptr }; // No topics to subscribe to
  return topics;
}

void Button::loop() {
  byte reading = digitalRead(pin);
  unsigned long currentMillis = millis();

  if (reading == LOW) { //We just care about pressed
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      StaticJsonDocument<1000> doc;
      doc["id"] = buttonId;
      doc["time"] = millis();

      char jsonBuffer[1000];
      size_t n = serializeJson(doc, jsonBuffer);

      publishMessage("button/" + buttonId + "/pressed", jsonBuffer);
    }
  }
}