#include <stdint.h>
#include "../../../services/communnication/communication.h"
#include "../../../communication/esp_now/Esp_Now.h"
#include "../../../services/detection/detection.h"
#include "../../../services/display/display.h"
#include "../../../services/visual/visual.h"
#include "../../../services/sound/sound.h"
#include "../../system_states/system_state.h"
#include "../us_events/us_sensor_events.h"
#include "esp_now_events_config.h"
#include "esp_now_events.h"
#include <Arduino.h>

extern uint8_t received_event;

extern system_states_t      system_state;
extern us_sensor_events_t   us_sensor_event;

esp_now_events_t esp_now_event_handler() {
    if(system_state == SYS_STATE_SENDING_NOTIFICATION) {
        uint32_t start_time_counting = millis();
        while(!send_state((uint8_t *)1)) {
            if((millis() - start_time_counting) >= TIMEOUT) {
                // Debugging
                Serial.println("Timeout, notification not sent!");
                return ESP_NOW_EVENT_NOTIFICATION_NOT_SENT;
            }
            // Debugging
            Serial.println("Sending the notification packet to InnerNode");
            delay(100);
        }

        // Debugging
        Serial.println("The Notification sent to InnerNode succcessfully!");
        return ESP_NOW_EVENT_NOTIFICATION_SENT;

    } else if(system_state == SYS_STATE_WAITING_RESPONCE) {
        uint32_t timer_start_count = millis();
        while(!is_data_available()) {
            if((millis() - timer_start_count) >= TIMEOUT) {
                // Debbuging
                Serial.println("Timeout, InnerNode failed to respond within 15 seconds");
                return ESP_NOW_EVENT_USER_NOT_CONFIRMED;
            }

            // Debbuging
            Serial.println("Waiting responce from InnerNode");
            delay(100);
        }

        Serial.println("The InnerNode responded succcessfully!");
        return ESP_NOW_EVENT_USER_CONFIRMED;
        
    } else if(system_state == SYS_STATE_OCCUPIED) {
        while(!is_data_available()) {
            if(is_person_detected()) sound_alert();

            Serial.println("Occupied, just waiting..");
            delay(100);
        }

        Serial.println("Person detected inside!");
        return ESP_NOW_EVENT_NOTIFICATION_AVAILABLE;
    
    } else if(system_state == SYS_STATE_WAITING_CONFIRMATION) {
        uint32_t timeout_counter_start = millis();
        while (!is_person_detected()) {
            if((millis() - timeout_counter_start) >= TIMEOUT) {
                Serial.println("Timeout, person was not detected within 15 seconds!");
                return ESP_NOW_EVENT_USER_NOT_CONFIRMED;
            }
            Serial.println("Wating for exit confirmation");
            delay(100);
        }

        Serial.println("User Exit successfully");
        return ESP_NOW_EVENT_USER_CONFIRMED;

    } else if(system_state == SYS_STATE_SENDING_CONFIRMATION) {
        uint32_t timeout_counter_start = millis(); 
        while(!send_state((uint8_t *) 1)) {
            if((millis() - timeout_counter_start) >= TIMEOUT) {
                Serial.println("Timeout! Confirmation send Failed!");
                return ESP_NOW_EVENT_NOTIFICATION_NOT_SENT;
            }
            Serial.println("Sending Exit Confirmation Notification to InnerNode!");
            delay(100);
        }

        Serial.println("Exit Notification sent Successfully, Entering FREE state!");
        return ESP_NOW_EVENT_NOTIFICATION_SENT;
    }

    return ESP_NOW_EVENT_NONE;
}