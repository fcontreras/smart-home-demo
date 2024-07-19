#ifndef TH_SENSOR_H
#define TH_SENSOR_H

#include <Arduino.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"
#include "xht11.h"

class TemperatureHumiditySensor : public Component {
  private:
    unsigned long previousMillis = 0;
    const long interval = 2000;
    int previousTempVal = 0;
    int previousHumVal = 0;
    xht11 xht;
    void startReading();

  public:
    TemperatureHumiditySensor();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // TH_SENSOR_H
