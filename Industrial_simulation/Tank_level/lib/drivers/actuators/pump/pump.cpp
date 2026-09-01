#include "pump.h"
#include "pump_config.h"

#include <Arduino.h>

static bool pumpRunning = false;

void Pump_init() {

    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, HIGH);

    pumpRunning = false;

    Serial.println("Pump ready");
}


void Pump_off() {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = true;
}


void Pump_on() {
    digitalWrite(PUMP_PIN, HIGH);
    pumpRunning = false;
}


bool Pump_isRunning() {
    return pumpRunning;
}