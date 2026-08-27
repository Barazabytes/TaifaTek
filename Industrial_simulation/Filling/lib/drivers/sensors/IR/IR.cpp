#include "IR.h"
#include "IR_config.h"
#include <Arduino.h>

void IR_init() {
    Serial.begin(115200);
    pinMode(IR_SENSOR_PIN, INPUT);

    Serial.println("IR Sensor ready");
}


bool IRObjectDetected() {

    return digitalRead(IR_SENSOR_PIN);
}