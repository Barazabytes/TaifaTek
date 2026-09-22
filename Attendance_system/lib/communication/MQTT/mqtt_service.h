#pragma once

#include <Arduino.h>

class MQTTService {
private:
    bool is_connected;
    bool done_connecting;
    bool published;

    bool response_received;
    String received_payload;
    String received_topic;

    static MQTTService* instance;
    static void mqtt_callback(char* topic, byte* payload, unsigned int length);

public:
    void init            ();
    bool is_mqtt_connect ();
    bool mqtt_connect    ();
    bool mqtt_publish    (const char* topic, const char* payload);
    bool mqtt_subscribe  (const char* topic);
    
    void mqtt_loop();
    bool message_received();
    String get_received_payload();
    String get_received_topic();
    void clear_received_message();
};