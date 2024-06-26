#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <src/arduino-secrets>

//Components
#include "src/components/led/Led.h"
#include "src/components/display/Display.h"
#include "src/components/motion/MotionSensor.h"
#include "src/components/fan/Fan.h"

//Services
#include "src/services/MQTTHandler.h"

// Components
Led led;
Display display;
MotionSensor motionSensor;
Fan fan;
Component* components[] = { &led, &motionSensor, &fan, nullptr }; // Array to hold components

// MQTT Handler
MQTTHandler mqttHandler(components, &display);

void setup() {
    Serial.begin(9600);

    // Initialize components
    display.init();
    int i = 0;
    while(components[i] != nullptr) {
      components[i]->init();
      components[i]->setDisplay(&display);
      i++;
    }

    // Connect to WiFi
    mqttHandler.connectToWifi(wifi_ssid, wifi_secret);

    // Initialize MQTT
    mqttHandler.init();

    // Connect to MQTT server
    mqttHandler.connectToMqttServer();
}

void loop() {
    // Handle MQTT loop
    mqttHandler.loop();
    
    // Loop components
    int i = 0;
    while(components[i] != nullptr) {
      components[i]->loop();
      i++;
    }

}
