#pragma once
#include <Arduino.h>

class MQTTService {
public:
    void MQTTConnect();
    void MQTTPublish(const char* topic, const char* payload);
    void MQTTSubscribe(const char* topic);
    void MQTTLoop();

    bool MessageAvailable();
    String GetMessage();
    String GetTopic();

private:
    static void MQTTCallback(
        char* topic,
        byte* payload,
        unsigned int length
    );

    static String receivedMessage;
    static String receivedTopic;
    static bool messageAvailable;
};