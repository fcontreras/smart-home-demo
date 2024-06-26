#include <ArduinoJson.h>
#include <ESP32Tone.h>
#include "Buzzer.h"

static const char* topicsToListen[] = {
  "buzzer/birthday",
  nullptr
};

Buzzer::Buzzer() {}

void Buzzer::init() {
    pinMode(pin, OUTPUT);
}

void Buzzer::birthday() {
  tone(pin, 294, 250, 0);  //The four parameters are pin, frequency, delay and channel 
  tone(pin, 440, 250, 0);
  tone(pin, 392, 250, 0);
  tone(pin, 532, 250, 0);
  tone(pin, 494, 250, 0);
  tone(pin, 392, 250, 0);
  tone(pin, 440, 250, 0);
  tone(pin, 392, 250, 0);
  tone(pin, 587, 250, 0);
  tone(pin, 532, 250, 0);
  tone(pin, 392, 250, 0);
  tone(pin, 784, 250, 0);
  tone(pin, 659, 250, 0);
  tone(pin, 532, 250, 0);
  tone(pin, 494, 250, 0);
  tone(pin, 440, 250, 0);
  tone(pin, 698, 250, 0);
  tone(pin, 659, 250, 0);
  tone(pin, 532, 250, 0);
  tone(pin, 587, 250, 0);
  tone(pin, 532, 500, 0);
  noTone(pin, 0);  //Close
}

void Buzzer::handleMessage(const String& topic, const String& message) {
    if (topic == String(this->mqttHandler->getMqttId()) + "/buzzer/play") {
      if (message == "birthday") {
        birthday();
      }
    }
}

const char** Buzzer::getSubscribeTopics() {
    return topicsToListen;
}

void Buzzer::loop() {}
