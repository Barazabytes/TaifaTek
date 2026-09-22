#include "../../../drivers/actuators/oled/oled.h"
#include "screen_config.h"

#include <Arduino.h>

OLED oled(OLED_SDA, OLED_SCL);

void screen_service_init() {
    oled.init();
}

void screen_clear_display() {
    oled.clear_display();
}

void screen_print_ln(const char *statement) {
    oled.print_ln(statement);
}

void screen_set_cursor(uint16_t row, uint16_t column) {
    oled.set_cursor(row, column);
}

void screen_oled_display() {
    oled.oled_display();
}
