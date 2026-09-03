#include <Arduino.h>
#include "TTmotor.h"
#include "TTmotor_config.h"

void TTmotorInit() {
  // Set control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Old ESP32 Core PWM Setup Sequence
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES); // Step 1: Configure the PWM timer properties
  ledcAttachPin(ENA, PWM_CHANNEL);        // Step 2: Tie your physical ENA pin to that channel

  Serial.println("TT motor Online");
}

void TTmotorStop() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    ledcWrite(PWM_CHANNEL, 0); 

    Serial.println("Motor has been stopped");
    delay(100);
}


void TTmotorMove() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL, CONVEYOR_SPEED);

    Serial.println("Motor is Running");
}