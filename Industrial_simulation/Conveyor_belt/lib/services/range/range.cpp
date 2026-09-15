#include "range.h"
#include "../../drivers/sensors/ultrasonic/ultrasonic.h"
#include "range_config.h"
#include <Arduino.h>

Ultrasonic us_sensor(TRIG_PIN, ECHO_PIN);

void range_service_init() {
    us_sensor.init();
}

bool is_object_detected() {
    int distance = static_cast<int>(us_sensor.get_distance());
    if(distance > 0 && distance <= THRESHOLD_DISTANCE_cm) return true;
    else return false;
}

void print_distance() {
    Serial.print("Distance: ");
    Serial.println(us_sensor.get_distance());
}