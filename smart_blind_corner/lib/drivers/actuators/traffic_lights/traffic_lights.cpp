#include "traffic_lights.h"
#include <Arduino.h>

TrafficLights::TrafficLights(uint8_t red, uint8_t yellow, uint8_t green) {
    RED_PIN = red;
    YELLOW_PIN = yellow;
    GREEN_PIN = green;
}

void TrafficLights::init() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    Serial.println("Traffic Lights configured");
    delay(200);
}

void TrafficLights::green_on() {
    digitalWrite(GREEN_PIN, HIGH);
}

void TrafficLights::green_off() {
    digitalWrite(GREEN_PIN, LOW);
}

void TrafficLights::yellow_on() {
    digitalWrite(YELLOW_PIN, HIGH);
}

void TrafficLights::yellow_off() {
    digitalWrite(YELLOW_PIN, LOW);
}

void TrafficLights::red_on() {
    digitalWrite(RED_PIN, HIGH);
}

void TrafficLights::red_off() {
    digitalWrite(RED_PIN, LOW);
}

