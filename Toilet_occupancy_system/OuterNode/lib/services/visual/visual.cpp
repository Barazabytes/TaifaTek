#include "visual.h"
#include "visual_config.h"
#include "../../drivers/actuators/RGB/RGB.h"

RGB rgb(RED_GPIO, GREEN_GPIO, BLUE_GPIO);

void visual_services_init() {
    rgb.init();
}


void color_free() {
    rgb.show_color(gRED_VALUE, gGREEN_VALUE, gBLUE_VALUE);
}

void color_occupied() {
    rgb.show_color(rRED_VALUE, rGREEN_VALUE, rBLUE_VALUE);
}

void color_waiting() {
    rgb.show_color(yRED_VALUE, yGREEN_VALUE, yBLUE_VALUE);
}