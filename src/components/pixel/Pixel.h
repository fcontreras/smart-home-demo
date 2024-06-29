#ifndef PIXEL_H
#define PIXEL_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class Pixel : public Component {
  private:
    void colorWipe(uint32_t color, int wait);
    void theaterChase(uint32_t color, int wait);
    void rainbow(int wait);
    void theaterChaseRainbow(int wait);
    void off();

  public:
    Pixel();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // PIXEL_H
