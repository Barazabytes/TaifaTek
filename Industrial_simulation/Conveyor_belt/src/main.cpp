#include "actuators/TTmotor/TTmotor.h"
#include "sensors/IR/IR.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  TTmotorInit();
  IR_init();

}

void loop() {
  if(IRObjectDetected() == LOW)
    TTmotorStop();
  else 
      TTmotorMove();

// Implementing already full Logic (esp_now) part.


  delay(100);



}
