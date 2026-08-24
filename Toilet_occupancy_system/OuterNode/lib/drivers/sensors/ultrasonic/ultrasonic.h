/**
 * @file ultrasonic.h
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The US implementation file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#include <stdint.h>

class Ultrasonic {

private:
    uint8_t trigger_pin;
    uint8_t echo_pin;

    bool object_present;

    uint8_t detection_count;
    uint8_t release_count;

public:
    Ultrasonic();

    void UltrasonicInit();

    int getDistance();

    bool triggered(
        uint16_t threshold_cm,
        uint16_t release_margin_cm = 10
    );

    bool isObjectPresent() const;
};