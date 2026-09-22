#pragma once
#include <stdint.h>

class OLED{
private:
    uint8_t SDA_PIN;
    uint8_t SCL_PIN;

public:
    OLED(uint8_t SDA_PIN, uint8_t SCL_PIN);
    void init();
    void clear_display();
    void print_ln(const char *statement);
    void set_cursor(uint16_t row, uint16_t column);
    void oled_display();
};