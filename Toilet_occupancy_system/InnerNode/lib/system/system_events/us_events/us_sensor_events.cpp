#include "../../../services/detection/detection.h"
#include "../../system_states/system_state.h"
#include "us_sensor_events_config.h"
#include "us_sensor_events.h"
#include <Arduino.h>


extern system_states_t system_state;

us_sensor_events_t us_sensor_event_handler() {
    if(system_state == SYS_STATE_OCCUPIED) {
        delay(COOL_DOWN_DELAY_ms);
        while (!is_person_detected()) {
            Serial.println("OCCUPIED, just waiting..");
            delay(100);            
        }

        Serial.println("Person Detected..");
        return US_SENSOR_EVENT_PERSON_DETECTED;      
    
    }

    return US_SENSOR_EVENT_NONE;
}