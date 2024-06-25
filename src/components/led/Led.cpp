#include "Led.h"

static const char* topicsToListen[] = {
  "led/power",
  nullptr
};

Led::Led() : pin(12), mqttHandler(nullptr) {}

void Led::init() {
    pinMode(pin, OUTPUT);
    off();
}

void Led::on() {
    digitalWrite(pin, HIGH);
    // mqttHandler->publish("led/status", "on");
}

void Led::off() {
    digitalWrite(pin, LOW);
    // mqttHandler->publish("led/status", "off");
}

void Led::handleMessage(const String& topic, const String& message) {
    if (topic == String(mqttHandler->getMqttId()) + "/led/power") {
        if (message.equalsIgnoreCase("on")) {
            on();
        } else if (message.equalsIgnoreCase("off")) {
            off();
        }
    }
}

const char** Led::getSubscribeTopics() {
    return topicsToListen;
}
