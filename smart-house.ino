#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <src/arduino-secrets>

#include <src/components/led/Led.h>
#include <src/components/display/Display.h>
#include <src/services/MQTTHandler.h>

// Components
Led led;
Display display;
Component* components[] = { &led, &display, nullptr }; // Array to hold components

// MQTT Handler
MQTTHandler mqttHandler(components, &display);

void setup() {
    // Initialize components
    led.init();
    display.init();

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
}
