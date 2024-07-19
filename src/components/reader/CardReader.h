#ifndef CARDREADER_H
#define CARDREADER_H

#include <Arduino.h>
#include <Wire.h>
#include "MFRC522_I2C.h"
#include "../Component.h"
#include "../../services/MQTTHandler.h"

class CardReader : public Component {
  private:
    MFRC522 mfrc522;
    unsigned long previousMillis = 0;
    const long interval = 50;
    const long intervalBetweenSameValue = 5000;
    unsigned long previousPublicationMillis = 0;
    String previousValue;

  public:
    CardReader();

    void init() override;
    void handleMessage(const String& topic, const String& message) override;
    const char** getSubscribeTopics() override;
    void loop() override;
};

#endif // CARDREADER_H
