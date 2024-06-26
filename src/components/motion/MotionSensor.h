#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class MotionSensor : public Component {
  private:
    const byte pin = 14;
    unsigned long previousMillis = 0;
    const long interval = 500;
    int previousVal = -1;
    void startReading();

  public:
    MotionSensor();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // LED_H
