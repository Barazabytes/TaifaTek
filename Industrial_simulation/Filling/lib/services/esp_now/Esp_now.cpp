#include "Esp_now.h"
#include "Esp_now_config.h"

// Stores received data
static EspNowData receivedData;

// Becomes true whenever a packet arrives
static volatile bool newDataAvailable = false;

static void OnDataSent(const uint8_t *macAddress, esp_now_send_status_t status) {
    Serial.print("ESP-NOW Send Status: ");
    if (status == ESP_NOW_SEND_SUCCESS)
        Serial.println("Success");
    else
        Serial.println("Failed");
}

static void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
    // Make sure the received packet has the expected size
    if (len == sizeof(EspNowData)){
        memcpy(&receivedData, incomingData, sizeof(receivedData));
        newDataAvailable = true;
    }
}

bool ESPNow_Init() {
    // ESP-NOW normally uses WiFi station mode
    WiFi.mode(WIFI_STA);
    delay(100);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK){
        Serial.println("ESP-NOW initialization failed");
        return false;
    }

    // Register callbacks
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("ESP-NOW initialized successfully");

    return true;
}


bool ESPNow_AddPeer() {
    if (esp_now_is_peer_exist(PEER_ADDRESS)){
        Serial.println("Peer already registered");
        return true;
    }

    esp_now_peer_info_t peerInfo = {};

    memcpy(peerInfo.peer_addr, PEER_ADDRESS, 6);

    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    peerInfo.ifidx = WIFI_IF_STA;

    esp_err_t result = esp_now_add_peer(&peerInfo);

    if (result != ESP_OK){
        Serial.print("Failed to add peer. Error: ");
        Serial.println(result);

        return false;
    }

    Serial.println("ESP-NOW peer added");

    return true;
}


bool ESPNow_Send(const EspNowData &data) {
    esp_err_t result =
        esp_now_send(PEER_ADDRESS, reinterpret_cast<const uint8_t *>(&data), sizeof(data));

    if (result == ESP_OK)
        return true;

    Serial.print("ESP-NOW send error: ");
    Serial.println(result);

    return false;
}


bool ESPNow_Available() {
    return newDataAvailable;
}


EspNowData ESPNow_GetData() {
    newDataAvailable = false;
    return receivedData;
}