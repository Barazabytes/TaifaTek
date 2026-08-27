#include <Arduino.h>
#include "actuators/pump/pump.h"
#include "sensors/IR/IR.h"


void setup() {
  IR_init();
}

void loop() {
  if(IRObjectDetected() == LOW) {
    Serial.println("Object detected");
  }

  delay(100);
}