#pragma once

#include <stdint.h>

class TrafficLights {
private:
    uint8_t RED_PIN;
    uint8_t YELLOW_PIN;
    uint8_t GREEN_PIN;

public:
    TrafficLights(uint8_t red, uint8_t yellow, uint8_t green);
    void init();
    void red_on();
    void red_off();
    void yellow_on();
    void yellow_off();
    void green_on();
    void green_off();

};