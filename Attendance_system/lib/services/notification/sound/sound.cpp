#include "../drivers/actuators/buzzer/buzzer.h"
#include "sound_config.h"
#include <Arduino.h>

Buzzer buzzer(BUZZER_PIN);

void sound_services_init() {
    buzzer.init();
}

void wifi_connected() {
    buzzer.buzzer_beep(1, WIFI_CONNECTED_BEEP_DELAY_ms);
}

void wifi_disconnected() {
    buzzer.buzzer_beep(2, WIFI_DISCONNECTED_BEEP_DELAY_ms);
}

void mqtt_connected() {
    buzzer.buzzer_beep(1, MQTT_CONNECTED_BEEP_DELAY_ms);
}

void mqtt_disconnected() {
    buzzer.buzzer_beep(3, MQTT_DISCONNECTED_BEEP_DELAY_ms);
}

void rfid_scanned_successfully() {
    buzzer.buzzer_beep(1, RFID_SCAN_SUCCESSFUL_BEEP_INTERVAL_ms);
}

void rfid_scanned_unsuccessfully() {
    buzzer.buzzer_beep(3, RFID_SCAN_UNSUCCESSFUL_BEEP_INTERVAL_ms);
}

void server_publish_successfully() {
    buzzer.buzzer_beep(1, SERVER_SUCCESSFUL_PUBLISH_BEEP_DELAY_ms);
}

void server_publish_unsuccessfully() {
    buzzer.buzzer_beep(3, SERVER_UNSUCCESSFUL_PUBLISH_BEEP_DELAY_ms);
}

void server_responded_successfully() {
    buzzer.buzzer_beep(1, SERVER_SUCCESSFUL_RESPONSE_BEEP_DELAY_ms);
}

void server_responded_unsuccessfully() {
    buzzer.buzzer_beep(4, SERVER_UNSUCCESSFUL_RESPONSE_BEEP_DELAY_ms);
}