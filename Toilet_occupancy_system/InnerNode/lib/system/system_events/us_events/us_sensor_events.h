#pragma once

typedef enum {
    US_SENSOR_EVENT_PERSON_DETECTED,
    US_SENSOR_INSIDE_EVENT_PERSON_DETECTED,
    US_SENSOR_EVENT_NONE,
}us_sensor_events_t;

us_sensor_events_t us_sensor_event_handler();
