#ifndef COMPONENT_H
#define COMPONENT_H

#include <Arduino.h>

class MQTTHandler; // Forward declaration
class Display;

class Component {
  protected:
    MQTTHandler* mqttHandler;
    Display* display;

  public:
    void setMQTTHandler(MQTTHandler* handler);
    void subscribeToTopics();
    void publishMessage(const String& topic, const String& message);
    void setDisplay(Display* display);

    virtual void init() = 0;
    virtual void handleMessage(const String& topic, const String& message) = 0;
    virtual const char** getSubscribeTopics() = 0;
    virtual void loop() = 0;
};

#endif // COMPONENT_H
