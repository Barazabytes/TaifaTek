#pragma once

const int IN1 = 4;
const int IN2 = 5;
const int ENA = 23; 
const int SENSOR_PIN = 2; 

const int PWM_CHANNEL = 0;    // ESP32 has 16 hardware PWM channels (0-15)
const int PWM_FREQ = 5000;     // 5 kHz frequency works perfectly for TT motors
const int PWM_RES = 8;         // 8-bit resolution gives a speed range of 0 to 255

const int CONVEYOR_SPEED = 200; 
