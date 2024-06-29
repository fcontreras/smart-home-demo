#include "Pixel.h"

static const char* topicsToListen[] = {
  "pixel/control",
  nullptr
};

Adafruit_NeoPixel strip(4, 26, NEO_GRB + NEO_KHZ800);
Pixel::Pixel() {}

void Pixel::init() {
  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void Pixel::handleMessage(const String& topic, const String& message) {
  if (topic == String(this->mqttHandler->getMqttId()) + "/pixel/control") {
    if (message.equalsIgnoreCase("rainbow")) {
      rainbow(10);
    } else if (message.equalsIgnoreCase("rainbow2")) {
      theaterChaseRainbow(50); 
    } else if (message.equalsIgnoreCase("off")) {
      off();
    }
  }
}

const char** Pixel::getSubscribeTopics() {
  return topicsToListen;
}

void Pixel::loop() {}

void Pixel::off() {
  strip.clear();
  strip.show();
}

void Pixel::colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void Pixel::theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 3; b++) {
      strip.clear();
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
    }
  }
}

void Pixel::rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

void Pixel::theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  for (int a = 0; a < 30; a++) {
    for (int b = 0; b < 3; b++) {
      strip.clear();
      for (int c = b; c < strip.numPixels(); c += 3) {
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}
