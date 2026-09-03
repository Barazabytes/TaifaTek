#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// Data structure shared between sender and receiver
typedef struct {
    String text;
} EspNowData;


// Initialize WiFi + ESP-NOW
bool ESPNow_Init();

// Add another ESP32 as a peer
bool ESPNow_AddPeer();

// Send a packet to a peer
bool ESPNow_Send(const EspNowData &data);

// Check whether new data has arrived
bool ESPNow_Available();

// Get the most recently received packet
EspNowData ESPNow_GetData();
