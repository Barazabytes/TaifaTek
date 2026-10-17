/**
 * @file buzzer.cpp
 * @author Said Baraza (instagram: @baraza_rs)
 * @brief Buzzer driver implementation.
 * @version 0.1
 * @date 2026-09-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "buzzer.h"
#include <Arduino.h>


Buzzer::Buzzer(uint8_t pin) : PIN(pin) {}

void Buzzer::init() {
    pinMode(PIN, OUTPUT);
    Serial.print("Buzzer configured: GPIO: ");
    Serial.println(PIN);
    delay(200);
}

void Buzzer::buzzer_on() {
    digitalWrite(PIN, HIGH);
    Serial.println("Buzzer ON");
}

void Buzzer::buzzer_off() {
    digitalWrite(PIN, LOW);
    Serial.println("Buzzer OFF");
}

void Buzzer::buzzer_beep(uint16_t beep_times, uint16_t interval_ms) {
    for(uint16_t i = 0; i < beep_times; i++) {
        buzzer_on();
        delay(interval_ms);
        buzzer_off();
        delay(interval_ms);
    }
    Serial.println("Buzzer Beep Complete");
}