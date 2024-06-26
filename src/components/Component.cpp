#include "Component.h"
#include "../services/MQTTHandler.h"
#include "display/Display.h"

void Component::setMQTTHandler(MQTTHandler* handler) {
  mqttHandler = handler;
}

void Component::setDisplay(Display* d) {
  display = d;
}

void Component::subscribeToTopics() {
  int i = 0;
  while(getSubscribeTopics()[i] != nullptr) {
    String topic = String(mqttHandler->getMqttId()) + "/" + getSubscribeTopics()[i];
    mqttHandler->subscribe(topic.c_str());
    i++;
  }
}

void Component::publishMessage(const String& topic, const String& message) {
    String fullTopic = String(mqttHandler->getMqttId()) + "/" + topic;
    mqttHandler->publish(fullTopic.c_str(), message.c_str());
}
