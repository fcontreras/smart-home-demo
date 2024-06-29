#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class Buzzer : public Component {
  private:
    const byte pin = 25;
    void birthday();

  public:
    Buzzer();
    
    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // BUZZER_H
