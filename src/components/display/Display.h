#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../Component.h"

class Display : public Component {
  private:
    LiquidCrystal_I2C mylcd;
    MQTTHandler* mqttHandler;

  public:
    Display();
    void init();
    void showMessage(const String message, const int delayAfterMessage);
    void sm(const String m, const int d);
    void sm(const String m);

    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
};

#endif // DISPLAY_H
