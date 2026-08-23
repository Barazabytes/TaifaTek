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