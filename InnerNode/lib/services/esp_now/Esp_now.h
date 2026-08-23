/**
 * @file Esp_now.h
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The esp_now header file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#pragma once

#include <esp_now.h>

class EspNow {

private:
    static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void addPeer   ();
    static void onDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

    static uint8_t rxBuffer[250];
    static int rxLength;

public:
    void init();
    void send(const void *data, size_t len);

    bool available();
    void receive(void *data, size_t len);
    
};