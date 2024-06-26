#include <ArduinoJson.h>
#include "Fan.h"

static const char* topicsToListen[] = {
  "fan/power",
  nullptr
};

Fan::Fan() {}

void Fan::init() {
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    digitalWrite(pinA, LOW);
    off();
}

void Fan::on() {
  if (previousOnVal == -1) {
    setSpeed(1);
  } else {
    setSpeed(previousOnVal);
  }
  
}

void Fan::off() {
  analogWrite(pinB, 0);
}

void Fan::setSpeed(int speed) {
  if (speed == 0) {
    analogWrite(pinB, 0);
  } else {
    previousOnVal = speed;
    int pwmValue = map(speed, 0, 10, 52, 255);
    analogWrite(pinB, pwmValue);
  }
}

void Fan::handleMessage(const String& topic, const String& message) {
    if (topic == String(this->mqttHandler->getMqttId()) + "/fan/power") {
        if (message.equalsIgnoreCase("on")) {
            on();
        } else if (message.equalsIgnoreCase("off")) {
            off();
        } else {
          int speed = message.toInt();
          if (speed >= 0 && speed <= 10) {
            setSpeed(speed);
          }
        }
    }
}

const char** Fan::getSubscribeTopics() {
    return topicsToListen;
}

void Fan::loop() {}
