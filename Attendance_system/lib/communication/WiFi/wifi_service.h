#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <WiFi.h>

class WiFiService {
public:
    void WiFiBegin();
    bool is_wifi_connected();
};