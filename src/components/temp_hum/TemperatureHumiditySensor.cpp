#include <ArduinoJson.h>
#include "TemperatureHumiditySensor.h"

static const char* topicsToListen[] = { nullptr };

TemperatureHumiditySensor::TemperatureHumiditySensor() : xht(17) {}

void TemperatureHumiditySensor::init() {}

void TemperatureHumiditySensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    unsigned char dht[4] = { 0, 0, 0, 0 };
    xht.receive(dht);
    if (dht[0] != previousHumVal || dht[2] != previousTempVal) {
      previousHumVal = dht[0];
      previousTempVal = dht[2];

      //publish all
      StaticJsonDocument<1000> doc;
      doc["temperature"] = dht[2];
      doc["humidity"] = dht[0];
      doc["time"] = currentMillis;
      char jsonBuffer[1000];
      size_t n = serializeJson(doc, jsonBuffer);
      publishMessage("temp_hum/status", jsonBuffer);

      //Publish temp
      StaticJsonDocument<1000> tempDoc;
      tempDoc["temperature"] = dht[2];
      tempDoc["time"] = currentMillis;
      char tempJsonBuffer[1000];
      serializeJson(tempDoc, tempJsonBuffer);
      publishMessage("temp_hum/temperature/status", tempJsonBuffer);
      
      //Publish Hum
      StaticJsonDocument<1000> humDoc;
      humDoc["humidity"] = dht[0];
      humDoc["time"] = currentMillis;
      char humJsonBuffer[1000];
      serializeJson(humDoc, humJsonBuffer);
      publishMessage("temp_hum/humidty/status", humJsonBuffer);
    }
  }
}

void TemperatureHumiditySensor::handleMessage(const String& topic, const String& message) {}

const char** TemperatureHumiditySensor::getSubscribeTopics() {
  return topicsToListen;
}
