#include "MQTTHandler.h"
#include "../../settings.h"

MQTTHandler::MQTTHandler(Component** comps, Display* disp)
    : mqttClient(wifiClient), components(comps), display(disp) {
}

void MQTTHandler::init() {
    mqttClient.setServer(mqtt_broker, mqtt_port);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) { this->onMessageReceived(topic, payload, length); });

    int i = 0;
    while(components[i] != nullptr) {
      components[i]->setMQTTHandler(this);
      i++;
    }
}

void MQTTHandler::loop() {
    if (!mqttClient.connected()) {
        connectToMqttServer();
    }
    mqttClient.loop();
}

void MQTTHandler::connectToWifi(const char* ssid, const char* password) {
    display->sm("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(5000);
    }
    display->sm("WiFi Connected");
}

void MQTTHandler::connectToMqttServer() {
    while (!mqttClient.connected()) {
        display->sm("Connecting to MQTT...");
        if (mqttClient.connect(mqtt_client_id)) {
            display->sm("MQTT Connected");

            int i = 0;
            while(components[i] != nullptr) {
              components[i]->subscribeToTopics();
              i++;
            }
        } else {
            display->sm("MQTT Connect Failed");
            delay(5000);
        }
    }
}

void MQTTHandler::subscribe(const char* topic) {
    mqttClient.subscribe(topic);
}

void MQTTHandler::publish(const char* topic, const char* message) {
    mqttClient.publish(topic, message);
}

void MQTTHandler::onMessageReceived(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }


    int i = 0;
    while(components[i] != nullptr) {
      components[i]->handleMessage(String(topic), message);
      i++;
    }
}

const char* MQTTHandler::getMqttId() {
    return mqtt_client_id;
}
