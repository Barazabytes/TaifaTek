#include "MPU6050_config.h"
#include "MPU6050.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void MPU6050_init() {
    Wire.begin();

    if (!mpu.begin()) {
        Serial.println("MPU6050 not found");
        while (1);
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);

    Serial.println("MPU6050 ready");
}


VibrationData measureVibration() {
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    // Record start time to get precise sample period
    startTime = micros();

    for (int i = 0; i < NUM_SAMPLES; i++) {
        mpu.getEvent(&accel, &gyro, &temp);
        samples[i] = accel.acceleration.z;
        delayMicroseconds(2000);   // ~500 Hz sample rate
    }
    
    endTime = micros();
    // Calculate total time taken in seconds
    float totalTimeSec = (endTime - startTime) / 1000000.0;

    // Calculate DC/gravity level
    float mean = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        mean += samples[i];
    }
    mean /= NUM_SAMPLES;

    // Calculate RMS and Zero-Crossings
    float sumSquares = 0;
    int zeroCrossings = 0;
    
    // Normalize first sample relative to mean
    float lastVibration = samples[0] - mean;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        float vibration = samples[i] - mean;
        sumSquares += vibration * vibration;

        // Detect if signal crossed the zero line (sign changed)
        if ((vibration >= 0 && lastVibration < 0) || (vibration < 0 && lastVibration >= 0)) {
            zeroCrossings++;
        }
        lastVibration = vibration;
    }

    float rms = sqrt(sumSquares / NUM_SAMPLES);
    
    // Each full wave cycle has 2 zero crossings (going up and going down)
    float hertz = (zeroCrossings / 20) / totalTimeSec;

    VibrationData data = {rms, hertz};
    return data;
}
