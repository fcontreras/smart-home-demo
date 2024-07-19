#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class GasSensor : public Component {
  private:
    const byte pin = 23;
    unsigned long previousMillis = 0;
    const long interval = 500;
    int previousVal = -1;

  public:
    GasSensor();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // GAS_SENSOR_H
