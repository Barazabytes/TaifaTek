/**
 * @file lcd.h
 * @author Said Baraza (barazars45@gmail.com)
 * @brief LCD driver header file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#include <Arduino.h>
#include <stdint.h>

class LcdDisplay {
    
private:
    uint8_t sda_pin;
    uint8_t clk_pin;

public:
    void begin();
    void print(const String& text);

};