#pragma once

#include <stdint.h>

typedef enum {
    WIFI_EVENT_CONNECTED,
    WIFI_EVENT_DISCONNECTED
} WiFi_event_t;

void           WiFi_events_init   ();
WiFi_event_t   WiFi_event_handler ();
bool           is_done_connecting ();