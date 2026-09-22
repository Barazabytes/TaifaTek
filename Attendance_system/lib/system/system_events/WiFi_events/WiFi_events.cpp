#include "../../../communication/WiFi/wifi_service.h"
#include "WiFi_events.h"
#include <Arduino.h>
#include <WiFi.h>

WiFiService wifi;

void WiFi_events_init() {
    wifi.WiFiBegin();
}

bool is_done_connecting() {
    return wifi.is_wifi_connected();
}

WiFi_event_t WiFi_event_handler() {
    if(wifi.is_wifi_connected()) return WIFI_EVENT_CONNECTED;
    else return WIFI_EVENT_DISCONNECTED;
}
