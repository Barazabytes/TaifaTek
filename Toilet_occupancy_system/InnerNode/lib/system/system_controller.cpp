#include <Arduino.h>
#include "system_events/esp_now_events/esp_now_events.h"
#include "system_events/us_events/us_sensor_events.h"
#include "../services/communnication/communication.h"
#include "system_states/system_state.h"
#include "system_controller.h"


system_states_t           system_state;
extern us_sensor_events_t received_event;
us_sensor_events_t        us_sensor_event;

void system_states_controller(esp_now_events_t esp_now_event, us_sensor_events_t us_sensor_event) {
    switch (system_state) { 
    case SYS_STATE_FREE:
        if(esp_now_event == ESP_NOW_EVENT_NOTIFICATION_AVAILABLE) system_state = SYS_STATE_WAITING_CONFIRMATION;
    break;
    
    case SYS_STATE_WAITING_CONFIRMATION:
        if(esp_now_event == ESP_NOW_EVENT_USER_CONFIRMED) system_state = SYS_STATE_SENDING_CONFIRMATION;
        else if(esp_now_event == ESP_NOW_EVENT_USER_NOT_CONFIRMED) system_state = SYS_STATE_FREE;
    break;

    case SYS_STATE_SENDING_CONFIRMATION:
        if(esp_now_event == ESP_NOW_EVENT_NOTIFICATION_SENT) system_state = SYS_STATE_OCCUPIED;
        else if(esp_now_event == ESP_NOW_EVENT_NOTIFICATION_NOT_SENT) system_state = SYS_STATE_SENDING_CONFIRMATION;
    break;

    case SYS_STATE_OCCUPIED:
        if(us_sensor_event == US_SENSOR_EVENT_PERSON_DETECTED) system_state = SYS_STATE_SENDING_NOTIFICATION;
    break;

    case SYS_STATE_SENDING_NOTIFICATION:
        if(esp_now_event == ESP_NOW_EVENT_NOTIFICATION_SENT) system_state = SYS_STATE_WAITING_RESPONCE;
        else if(esp_now_event == ESP_NOW_EVENT_NOTIFICATION_NOT_SENT) system_state = SYS_STATE_SENDING_NOTIFICATION;
    break;
    
    case SYS_STATE_WAITING_RESPONCE:
        if(esp_now_event == ESP_NOW_EVENT_USER_CONFIRMED) system_state = SYS_STATE_FREE;
        else if(esp_now_event == ESP_NOW_EVENT_USER_NOT_CONFIRMED) system_state = SYS_STATE_OCCUPIED;
    break;


    }
}
