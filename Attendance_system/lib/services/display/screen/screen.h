#pragma once

#include <stdint.h>
void screen_service_init();
void screen_clear_display();
void screen_print_ln(const char *statement);
void screen_set_cursor(uint16_t row, uint16_t column);
void screen_oled_display();