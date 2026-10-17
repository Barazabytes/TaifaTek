#pragma once

#include "system_events/esp_now_events/esp_now_events.h"
#include "system_events/us_events/us_sensor_events.h"

void system_states_controller(esp_now_events_t esp_now_event, us_sensor_events_t us_sensor_event);
