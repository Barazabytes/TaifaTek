#pragma once
#include <stdint.h>

class RGB {
private:
    uint8_t RED_PIN;
    uint8_t GREEN_PIN;
    uint8_t BLUE_PIN;

public:
    RGB(uint8_t red, uint8_t green, uint8_t blue);
    void init();
    void show_color(uint8_t red, uint8_t green, uint8_t blue);
};
