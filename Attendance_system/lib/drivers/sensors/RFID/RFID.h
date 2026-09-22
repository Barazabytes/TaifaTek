#pragma once

#include <stdint.h>
#include <Arduino.h>

class RFID {
public:
    void init();
    bool is_card_available();
    bool read_card();
    void sleep_card();
    String get_uid();
};