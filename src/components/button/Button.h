#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class Button : public Component {
  
  private:
    String buttonId;
    byte pin;
    unsigned long previousMillis = 0;
    const long interval = 1000;
    
  public:
    Button(byte pin, const String& buttonId);

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif