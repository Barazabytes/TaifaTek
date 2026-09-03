#include <MPU6050_tockn.h>
#include "mpu6050_config.h"
#include <Arduino.h>
#include "mpu6050.h"
#include <Wire.h>
#include <math.h>


MPU6050 mpu6050(Wire);
unsigned long timer = 0;

void mpu6050_init() {
  Wire.begin(SDA, SCL);
  mpu6050.begin();
  
  Serial.println("=================================================");
  Serial.println("Calibrating MPU-6050... KEEP SENSOR FLAT AND STILL!");
  Serial.println("=================================================");
  
  mpu6050.calcGyroOffsets(true); 
  Serial.println("Done! Calibration complete.");
}

float tilt_angle() {
  mpu6050.update();

  float totalTiltAngle = 0.0f;

  // Update and print data every 100 milliseconds
  if (millis() - timer > 100) {
    float roll = mpu6050.getAngleX();  // Side-to-side tilt
    float pitch = mpu6050.getAngleY(); // Front-to-back tilt

    // Calculate the single overall leaning angle from the horizontal plane
    totalTiltAngle = sqrt(pow(roll, 2) + pow(pitch, 2));

    // Optional: Ignore tiny sensor noise when the object is perfectly flat
    if (totalTiltAngle < 0.5) {
      totalTiltAngle = 0.0;
    }
    
    timer = millis();
    
  }

    return totalTiltAngle;
}