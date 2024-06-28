#include <ArduinoJson.h>
#include "WindowServo.h"

static const char* topicsToListen[] = {
  "window/position",
  nullptr
};

WindowServo::WindowServo() {}

void WindowServo::init() {
  servo.attach(pin);
  close();
}

void WindowServo::open() {
  servo.write(openPosition);
}

void WindowServo::close() {
  servo.write(closePosition);
}

void WindowServo::handleMessage(const String& topic, const String& message) {
    if (topic == String(this->mqttHandler->getMqttId()) + "/window/position") {
        if (message.equalsIgnoreCase("open")) {
            open();
        } else if (message.equalsIgnoreCase("close")) {
            close();
        }
    }
}

const char** WindowServo::getSubscribeTopics() {
    return topicsToListen;
}

void WindowServo::loop() {}
