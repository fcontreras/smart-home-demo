#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class Led : public Component {
  private:
    byte pin;
    MQTTHandler* mqttHandler;

  public:
    Led();
    void init();
    void on();
    void off();

    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
};

#endif // LED_H
