#include "Display.h"
#include "../../services/MQTTHandler.h"

static const char* topicsToListen[] = {
  "display/message",
  nullptr
};

Display::Display()
  : mylcd(0x27, 16, 2) {}

void Display::init() {
    mylcd.init();
    mylcd.backlight();
    mylcd.clear();
}

void Display::showMessage(const String message, const int delayAfterMessage) {
    mylcd.clear();
    mylcd.setCursor(0, 0);
    if (message.length() > 16) {
        mylcd.print(message.substring(0, 16));
        mylcd.setCursor(0, 1);
        mylcd.print(message.substring(16));
    } else {
        mylcd.print(message);
    }

    if (delayAfterMessage > 0) {
        delay(delayAfterMessage);
    }
}

void Display::sm(const String m) {
    showMessage(m, 0);
}

void Display::sm(const String m, const int d) {
    showMessage(m, d);
}

void Display::handleMessage(const String& topic, const String& message) {
    if (topic == String(this->mqttHandler->getMqttId()) + "/display/message") {
        sm(message);
    }
}

const char** Display::getSubscribeTopics() {
    return topicsToListen;
}

void Display::loop() {}