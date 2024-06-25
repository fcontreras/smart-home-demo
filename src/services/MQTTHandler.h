#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "../components/Component.h" // Include the base Component class
#include "../components/display/Display.h"

class Display;

class MQTTHandler {
  private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    Component** components;
    Display* display;

  public:
    MQTTHandler(Component** comps, Display* disp);
    void init();
    void loop();
    void connectToWifi(const char* ssid, const char* password);
    void connectToMqttServer();
    void subscribe(const char* topic);
    void publish(const char* topic, const char* message);
    void onMessageReceived(char* topic, byte* payload, unsigned int length);
    const char* getMqttId();
};

#endif // MQTTHANDLER_H
