/**
 * @file main.cpp
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The main file from where the system execution begins
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#include <Arduino.h>
#include "application.h"

Application App;

void setup() {
    Serial.begin(115200);

    App.setup();
}

void loop() {
    App.run();
}

