#pragma once

void MPU6050_init();

struct VibrationData {
    float rms;
    float hertz;
};

VibrationData measureVibration();