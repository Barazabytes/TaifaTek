/**
 * @file Esp_now.cpp
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The esp_now protocol implementation
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */



#include "Esp_now.h"
#include "Esp_now_config.h"
#include <esp_now.h>
#include <WiFi.h>

void EspNow::init() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Registering data sending and receive callback functions
    esp_now_register_send_cb(onDataSent);
    esp_now_register_recv_cb(onDataRecv);

    // Adding peer
    addPeer();

}

void EspNow::addPeer() {
    esp_now_peer_info peer = {};

    memcpy(peer.peer_addr, PEER_ADDRESS, 6);
    peer.channel = 0;
    peer.encrypt = false;

    if (esp_now_add_peer(&peer) != ESP_OK)
        Serial.println("Failed to add peer.");

}

void EspNow::send(const void *data, size_t len) {
    esp_err_t result = esp_now_send(PEER_ADDRESS, (const uint8_t *)data, len);

    if(result != ESP_OK)
        Serial.println("Failed to send Data");

}

void EspNow::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

    Serial.print("Send Status: ");

    if (status == ESP_NOW_SEND_SUCCESS)
        Serial.println("Success");
    else
        Serial.println("Failed");

}


void EspNow::onDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {

    memcpy(rxBuffer, incomingData, len);
    rxLength = len;

}


uint8_t EspNow::rxBuffer[250];
int EspNow::rxLength = 0;

bool EspNow::available() {
    return rxLength > 0;
}


void EspNow::receive(void *data, size_t len) {
    memcpy(data, rxBuffer, len);
    rxLength = 0;
}
