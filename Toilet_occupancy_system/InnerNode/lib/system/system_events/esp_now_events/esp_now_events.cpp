#include "../../../services/communnication/communication.h"
#include "../../../communication/esp_now/Esp_Now.h"
#include "../../../services/detection/detection.h"
#include "../../system_states/system_state.h"
#include "../us_events/us_sensor_events.h"
#include "esp_now_events_config.h"
#include "esp_now_events.h"
#include <Arduino.h>

extern system_states_t      system_state;
extern us_sensor_events_t   us_sensor_event;

esp_now_events_t esp_now_event_handler() {
    if(system_state == SYS_STATE_FREE) {
        while(!is_data_available()) {
            Serial.println("FREE just waiting..");
            delay(100);
        }

        Serial.println("Person detected outside!");
        return ESP_NOW_EVENT_NOTIFICATION_AVAILABLE;
    
    } else if(system_state == SYS_STATE_WAITING_CONFIRMATION) {
        uint32_t timeout_counter_start = millis();
        while (!is_person_detected()) {
            if((millis() - timeout_counter_start) >= TIMEOUT) {
                Serial.println("Timeout! No user entered the Toilet.");
                return ESP_NOW_EVENT_USER_NOT_CONFIRMED;
            }

            Serial.println("Wating for entrance confirmation");
            delay(100);
        }

        Serial.println("User Entered a toilet successfully");
        return ESP_NOW_EVENT_USER_CONFIRMED;

    } else if(system_state == SYS_STATE_SENDING_CONFIRMATION) {
        while(!send_state(1)) {
            uint32_t start_time_counting = millis();
            if((millis() - start_time_counting) >= TIMEOUT) {
                Serial.println("TimeOut, Sending notification to outerNode had some challenges for 15 seconds!");
                return ESP_NOW_EVENT_NOTIFICATION_NOT_SENT;
            }
            Serial.println("Sending Confirmation Notification to OuterNode");
            delay(100);
        }

        Serial.println("The confirmation notification sent succcessfully!");
        return ESP_NOW_EVENT_NOTIFICATION_SENT;
    
    } else if(system_state == SYS_STATE_SENDING_NOTIFICATION) {
        while(!send_state(1)) {
            uint32_t start_time_counting = millis();
            if((millis() - start_time_counting) >= TIMEOUT) {
                Serial.println("TimeOut");
                return ESP_NOW_EVENT_NOTIFICATION_NOT_SENT;
            }
            Serial.println("Sending the packet to OuterNode");
            delay(100);
        }

        Serial.println("The Data event sent succcessfully!");
        return ESP_NOW_EVENT_NOTIFICATION_SENT;
    
    } else if(system_state == SYS_STATE_WAITING_RESPONCE) {
        uint32_t timeout_start_count = millis();
        while(!is_data_available()) {
            if((millis() - timeout_start_count) >= TIMEOUT) {
                Serial.println("TimeOut! User did not exit the Toilet");
                return ESP_NOW_EVENT_USER_NOT_CONFIRMED;
            }

            Serial.println("Waiting responce from OuterNode");
            delay(100);
        }

        Serial.println("The Data event received succcessfully!");
        return ESP_NOW_EVENT_USER_CONFIRMED;
    
    }

    return ESP_NOW_EVENT_NONE;
}