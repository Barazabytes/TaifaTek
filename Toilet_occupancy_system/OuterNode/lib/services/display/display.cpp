#include "../../drivers/actuators/lcd/lcd.h"
#include "display_config.h"
#include "display.h"
#include <Arduino.h>

LcdDisplay screen;
void display_service_init() {
    screen.init();
}

void print_free() {
    screen.print(FREE);
}

void print_occupied() {
    screen.print(OCCUPIED);
}

void print_waiting() {
    screen.print(WAITING);
}