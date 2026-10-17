/**
 * @file ultrasonic.h
 * @author Said Baraza (instagram: @baraza_rs)
 * @brief Ultrasonic sensor driver interface.
 * @version 0.1
 * @date 2026-09-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once
#include <stdint.h>


class Ultrasonic {
private:
    uint8_t  TRIG_PIN;
    uint8_t  ECHO_PIN;
    float    DISTANCE;

public:
    Ultrasonic        (uint8_t trig, uint8_t echo);
    void  init        ();
    float get_distance();
};