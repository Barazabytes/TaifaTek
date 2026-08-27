#include "wifi_service.h"
#include "wifi_config.h"
#include "WiFi.h"


void WiFiService::WiFiBegin() {
    // Service implementation
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
};