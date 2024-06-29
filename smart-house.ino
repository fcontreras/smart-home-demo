#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "src/arduino-secrets.h"

//Components
#include "src/components/led/Led.h"
#include "src/components/display/Display.h"
#include "src/components/motion/MotionSensor.h"
#include "src/components/fan/Fan.h"
#include "src/components/servo/SmartServo.h"
#include "src/components/temp_hum/TemperatureHumiditySensor.h"
#include "src/components/raindrop/RaindropSensor.h"
#include "src/components/buzzer/Buzzer.h"
#include "src/components/pixel/Pixel.h"
#include "src/components/gas/GasSensor.h"

//Services
#include "src/services/MQTTHandler.h"

// Components
Led led;
Display display;
MotionSensor motionSensor;
Fan fan;
SmartServo doorServo(13, "door/position");
SmartServo windowServo(5, "window/position");
TemperatureHumiditySensor tempHumSensor;
RaindropSensor raindropSensor;
Buzzer buzzer;
Pixel pixel;
GasSensor gasSensor;
Component* components[] = { &led, &motionSensor, &fan, &doorServo, &windowServo, &tempHumSensor, &raindropSensor, &buzzer, &pixel, &gasSensor, nullptr }; // Array to hold components

// MQTT Handler
MQTTHandler mqttHandler(components, &display);

void setup() {
    Serial.begin(9600);

    // Initialize components
    display.init();
    // pixel.setDisplay(&display);
    // pixel.init();
    int i = 0;
    while(components[i] != nullptr) {
      components[i]->setDisplay(&display);
      components[i]->init();
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
    // pixel.loop();
}
