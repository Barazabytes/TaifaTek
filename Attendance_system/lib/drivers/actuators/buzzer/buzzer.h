/**
 * @file buzzer.h
 * @author Said Baraza (instagram: @baraza_rs)
 * @brief Buzzer driver interface.
 * @version 0.1
 * @date 2026-09-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#pragma once
#include <stdint.h>

class Buzzer {
private:
    uint8_t PIN;

public:
    Buzzer(uint8_t pin);
    void init();
    void buzzer_on();
    void buzzer_off();
    void buzzer_beep(uint16_t beep_times, uint16_t interval_ms);
};