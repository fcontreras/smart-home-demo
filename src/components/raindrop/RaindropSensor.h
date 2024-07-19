#ifndef RAINDROP_SENSOR_H
#define RAINDROP_SENSOR_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class RaindropSensor : public Component {
  private:
    const byte pin = 34;
    unsigned long previousMillis = 0;
    const long interval = 2000;
    int previousVal = -1;
    void startReading();

  public:
    RaindropSensor();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // RAINDROP_SENSOR_H
