#include <Arduino.h>
#include "sensors/ultrasonic/ultrasonic.h"
#include "actuators/pump/pump.h"
#include "sensors/ultrasonic/ultrasonic_config.h"

Ultrasonic ultrasonic;


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Pump_init();
  ultrasonic.UltrasonicInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  int depth = ultrasonic.getDistance();
 
  if(depth >= SHALLOW_DEPTH) {
    Serial.println(depth);
    Serial.println("Tank is nearly Empty Starting the pump.");
    Pump_on();
  } else if(depth <= FULL_DEPTH) {
    Serial.println(depth);
    Serial.println("Tank is Full. Stopping the pump.");
    Pump_off();
  } else {
    Serial.println("Error reading distance.");
  }


  delay(100);
}
