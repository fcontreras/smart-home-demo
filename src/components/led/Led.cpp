#include <ArduinoJson.h>
#include "Led.h"

static const char* topicsToListen[] = {
  "led/power",
  nullptr
};

Led::Led() {}

void Led::init() {
    pinMode(pin, OUTPUT);
    off();
}

void Led::on() {
    digitalWrite(pin, HIGH);
    unsigned long currentMillis = millis();

    // StaticJsonDocument<1000> doc;
    // doc["status"] = "on";
    // doc["time"] = currentMillis;

    // char jsonBuffer[1000];
    // size_t n = serializeJson(doc, jsonBuffer);
    
    // publishMessage("led/status", jsonBuffer);
}

void Led::off() {
    digitalWrite(pin, LOW);
    unsigned long currentMillis = millis();

    // StaticJsonDocument<1000> doc;
    // doc["status"] = "off";
    // doc["time"] = currentMillis;

    // char jsonBuffer[1000];
    // size_t n = serializeJson(doc, jsonBuffer);
    
    // publishMessage("led/status", jsonBuffer);
}

void Led::handleMessage(const String& topic, const String& message) {
    if (topic == String(this->mqttHandler->getMqttId()) + "/led/power") {
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

void Led::loop() {}
