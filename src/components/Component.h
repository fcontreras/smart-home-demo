#ifndef COMPONENT_H
#define COMPONENT_H

#include <Arduino.h>

class MQTTHandler; // Forward declaration

class Component {
  protected:
    MQTTHandler* mqttHandler;

  public:
    void setMQTTHandler(MQTTHandler* handler);
    virtual void handleMessage(const String& topic, const String& message) = 0;
    virtual const char** getSubscribeTopics() = 0;
    void subscribeToTopics();
    void publishMessage(const String& topic, const String& message);
};

#endif // COMPONENT_H
