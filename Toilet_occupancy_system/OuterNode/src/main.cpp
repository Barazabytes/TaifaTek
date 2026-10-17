#include <Arduino.h>
#include "detection/detection.h"
#include "display/display.h"
#include "sound/sound.h"
#include "visual/visual.h"
#include "communnication/communication.h"
#include "system_events/esp_now_events/esp_now_events.h"
#include "system_events/us_events/us_sensor_events.h"
#include "system_controller.h"


void setup() {
    Serial.begin(115200);

    communication_service_init ();
    detection_service_init     ();
    display_service_init       ();
    sound_services_init        ();
    visual_services_init       ();
}

us_sensor_events_t sensor_event;
esp_now_events_t   esp_event;


void loop() {

    sensor_event = us_sensor_event_handler  ();
    esp_event    = esp_now_event_handler    ();

    system_states_controller(esp_event, sensor_event);

    update_system_outputs();
    
    delay(100);
}
