#include <ArduinoJson.h>
#include "SmartServo.h"

SmartServo::SmartServo(byte pin, const String& openCloseTopic) : pin(pin), openCloseTopic(openCloseTopic) {}

void SmartServo::init() {
  servo.attach(pin);
  close();
}

void SmartServo::open() {
  servo.write(openPosition);
}

void SmartServo::close() {
  servo.write(closePosition);
}

void SmartServo::handleMessage(const String& topic, const String& message) {
    if (topic == (String(this->mqttHandler->getMqttId()) + "/" + openCloseTopic)) {
      if (message.equalsIgnoreCase("open")) {
        open();
      } else if (message.equalsIgnoreCase("close")) {
        close();
      }
    }
}

const char** SmartServo::getSubscribeTopics() {
  static const char* topicsToListen[] = { nullptr, nullptr };   // We use dynamic memory for topic storage
  topicsToListen[0] = openCloseTopic.c_str();
  return topicsToListen;
}

void SmartServo::loop() {}
