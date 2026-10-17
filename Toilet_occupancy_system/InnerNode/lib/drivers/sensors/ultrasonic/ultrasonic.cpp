/**
 * @file ultrasonic.cpp
 * @author Said Baraza (instagram: @baraza_rs)
 * @brief Ultrasonic sensor driver implementation.
 * @version 0.1
 * @date 2026-09-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "ultrasonic_config.h"
#include "ultrasonic.h"
#include <Arduino.h>

Ultrasonic::Ultrasonic(uint8_t trig, uint8_t echo) : TRIG_PIN(trig), ECHO_PIN(echo), DISTANCE(0) {}

void Ultrasonic::init() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.printf("Ultrasonic configured: TRIG: %d ECHO: %d \n", TRIG_PIN, ECHO_PIN);
    delay(200);
}

float Ultrasonic::get_distance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2); // Ensure a clean low pulse first
    
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(ULTRASONIC_BURST_us);
    digitalWrite(TRIG_PIN, LOW);
    
    uint32_t counter_start = micros();
    while(digitalRead(ECHO_PIN) == LOW) {
        if((micros() - counter_start) >= TIMEOUT_us)
            return -1.0f;
    }

    uint32_t start_echo = micros();
    while(digitalRead(ECHO_PIN) == HIGH) {
        if((micros() - start_echo) >= TIMEOUT_us)
            return -1.0f;
    }
    
    uint32_t echo_end = micros();
    uint32_t duration = (echo_end - start_echo);

    DISTANCE = SOUND_SPEED_cm_per_us * (duration/2.0f);
           
    return DISTANCE;
    
}
