#pragma once

#include <stdint.h>

typedef enum {
    MQTT_EVENT_CONNECTED_TO_SERVER,
    MQTT_EVENT_DISCONNECTED_FROM_A_SERVER
} mqtt_event_t;

void           mqtt_events_init     ();
mqtt_event_t   mqtt_event_handler   ();
bool           is_done_publishing   (const char* topic, const char* payload);
bool           mqtt_done_connecting ();
bool           is_done_subscribing  (const char* topic);
void           mqtt_events_loop     ();
bool           is_message_received  ();