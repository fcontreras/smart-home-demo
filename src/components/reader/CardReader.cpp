#include <ArduinoJson.h>
#include "CardReader.h"

static const char* topicsToListen[] = {
  nullptr
};

CardReader::CardReader() : mfrc522(0x28) {}

void CardReader::init() {
  Wire.begin();
  mfrc522.PCD_Init();
}

void CardReader::handleMessage(const String& topic, const String& message) {}

const char** CardReader::getSubscribeTopics() {
    return topicsToListen;
}

void CardReader::loop() {
  unsigned long currentMillis = millis();

  boolean canPublishSameValue = currentMillis - previousPublicationMillis >= intervalBetweenSameValue;
  if (currentMillis - previousMillis >= interval) {  
    previousMillis = currentMillis;

    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      String value = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        value = value + String(mfrc522.uid.uidByte[i]);
      }

      StaticJsonDocument<1000> doc;
      doc["value"] = value;
      doc["time"] = currentMillis;

      char jsonBuffer[1000];
      size_t n = serializeJson(doc, jsonBuffer);

      if (value == previousValue) {
        if (canPublishSameValue) {
          previousPublicationMillis = currentMillis;
          publishMessage("reader/value", jsonBuffer);
        }
      } else {
        previousPublicationMillis = currentMillis;
        publishMessage("reader/value", jsonBuffer);
        previousValue = value;
      }
    }
  }
}
