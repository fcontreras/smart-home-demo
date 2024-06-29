#ifndef SSERVO_H
#define SSERVO_H

#include <Arduino.h>
#include <ESP32_Servo.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class SmartServo : public Component {
  private:
    byte pin;
    String openCloseTopic;
    Servo servo;
    const int openPosition = 180;
    const int closePosition = 0;

  public:
    SmartServo(byte pin, const String& openCloseTopic);
    void open();
    void close();

    void init();
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // SSERVO_H
