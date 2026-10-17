#include <Arduino.h>
#include "system_controller.h"
#include "system_states/system_state.h"
#include "../services/display/display.h"
#include "../services/visual/visual.h"
#include "../services/sound/sound.h"

extern system_states_t system_state;

void update_system_outputs() {
    static bool initialized = false;
    static system_states_t last_state;

    if (initialized && system_state == last_state)  return;

    switch (system_state) {
        case SYS_STATE_FREE:
            print_free();
            color_free();
        break;

        case SYS_STATE_SENDING_NOTIFICATION:
        case SYS_STATE_WAITING_RESPONCE:
        case SYS_STATE_WAITING_CONFIRMATION:
        case SYS_STATE_SENDING_CONFIRMATION:
            print_waiting();
            color_waiting();
        break;

        case SYS_STATE_OCCUPIED:
            print_occupied();
            color_occupied();
            sound_alert();
        break;
    }

    last_state = system_state;
    initialized = true;
}