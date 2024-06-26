#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class Fan : public Component {
  private:
    const byte pinA = 19;
    const byte pinB = 18;
    int previousOnVal = -1;
    void setSpeed(int val);

  public:
    Fan();
    void on();
    void off();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // LED_H
