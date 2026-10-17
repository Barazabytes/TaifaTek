#include "../../drivers/sensors/ultrasonic/ultrasonic.h"
#include "detection_config.h"
#include "detection.h"
#include <Arduino.h>

Ultrasonic us_sensor(US_TRIG, US_ECHO);

void detection_service_init() {
    us_sensor.init();
}

bool is_person_detected() {
    if(us_sensor.get_distance() <= DETECTION_RANGE) return true;
    else return false;
}