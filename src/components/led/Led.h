#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class Led : public Component {
  private:
    const byte pin = 12;

  public:
    Led();
    void on();
    void off();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // LED_H
