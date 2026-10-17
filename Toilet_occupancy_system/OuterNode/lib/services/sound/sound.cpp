#include "sound.h"
#include "sound_config.h"
#include "../../drivers/actuators/buzzer/buzzer.h"

Buzzer sound(BUZZER_PIN);

void sound_services_init() {
    sound.init();
}


void sound_alert() {
    sound.buzzer_beep(BEEP_TIMES, BEEP_INTERVAL);
}