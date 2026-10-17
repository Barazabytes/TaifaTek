#include <Arduino.h>
#include "detection/detection.h"
#include "communnication/communication.h"
#include "system_events/esp_now_events/esp_now_events.h"
#include "system_events/us_events/us_sensor_events.h"
#include "system_controller.h"

extern uint8_t received_event;

void setup() {
    Serial.begin(115200);
    detection_service_init();
    communication_service_init();
}

us_sensor_events_t ultrsonic_sensor_event;
esp_now_events_t   esp_now_protocol_event;

void loop() {

    ultrsonic_sensor_event = us_sensor_event_handler();
    esp_now_protocol_event = esp_now_event_handler();

    system_states_controller(esp_now_protocol_event, ultrsonic_sensor_event);

    delay(100);

}
