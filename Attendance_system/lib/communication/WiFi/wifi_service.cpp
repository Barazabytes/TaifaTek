#include "wifi_service.h"
#include "wifi_config.h"
#include "WiFi.h"

void WiFiService::WiFiBegin() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
};

bool WiFiService::is_wifi_connected() {
    if (WiFi.status() != WL_CONNECTED) return false;
    else return true;
}
