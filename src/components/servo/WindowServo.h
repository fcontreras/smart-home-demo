#ifndef WSERVO_H
#define WSERVO_H

#include <Arduino.h>
#include <ESP32_Servo.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class WindowServo : public Component {
  private:
    const byte pin = 5;
    Servo servo;
    const int openPosition = 180;
    const int closePosition = 0;

  public:
    WindowServo();
    void open();
    void close();

    void init();
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // WSERVO_H
