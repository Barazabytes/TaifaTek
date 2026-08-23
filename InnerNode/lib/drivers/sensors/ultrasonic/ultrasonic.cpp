/**
 * @file ultrasonic.cpp
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The US sensor implementation file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "ultrasonic.h"
#include "ultrasonic_config.h"

#include <Arduino.h>

Ultrasonic::Ultrasonic()
    : trigger_pin(ULTRASONIC_TRIGGER_PIN),
      echo_pin(ULTRASONIC_ECHO_PIN),
      object_present(false),
      detection_count(0),
      release_count(0)
{}

void Ultrasonic::UltrasonicInit() {
    pinMode(trigger_pin, OUTPUT);
    pinMode(echo_pin, INPUT);

    digitalWrite(trigger_pin, LOW);
}

int Ultrasonic::getDistance() {
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigger_pin, LOW);

    // 30 ms timeout prevents the program from blocking for too long.
    unsigned long duration = pulseIn(echo_pin, HIGH, 30000);

    if (duration == 0) {
        return -1;
    }

    float distance_cm = duration * 0.0343f / 2.0f;

    return static_cast<int>(distance_cm);
}


// Project specific function to determine if an object is present in the detection zone.
bool Ultrasonic::triggered( uint16_t threshold_cm, uint16_t release_margin_cm) {
    int distance = getDistance();

    // Ignore failed measurements.
    if (distance < 0) {
        return false;
    }

    uint16_t release_distance =
        threshold_cm + release_margin_cm;


    // Person is currently outside the detection zone.
    if (!object_present) {

        if (distance <= threshold_cm) {
            detection_count++;
        } else {
            detection_count = 0;
        }

        // Require two consecutive valid measurements.
        // This reduces false triggers caused by sensor noise.
        if (detection_count >= 2) {
            object_present = true;

            detection_count = 0;
            release_count = 0;

            return true;
        }
    }

    // Person was previously detected.
    // Wait until they leave before allowing another event.
    else {

        if (distance > release_distance) {
            release_count++;
        } else {
            release_count = 0;
        }

        if (release_count >= 2) {
            object_present = false;

            detection_count = 0;
            release_count = 0;
        }
    }

    return false;
}


bool Ultrasonic::isObjectPresent() const {
    return object_present;
}