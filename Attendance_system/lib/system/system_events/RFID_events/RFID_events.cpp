#include <Arduino.h>
#include "RFID_events.h"
#include "../../system_controller.h"
#include "../../system_states/system_states.h"
#include "../../../drivers/sensors/RFID/RFID.h"

RFID rfid;

void rfid_events_init() {
    rfid.init();
}

extern system_states_t system_state;   // declared in system_states.h

rfid_events_t rfid_events_handler() {
    if (system_state == RFID_STATE_IDLE)
        return rfid.is_card_available() ? RFID_EVENT_CARD_AVAILABLE : RFID_EVENT_NONE;
    if (system_state == RFID_STATE_SCANNING) return rfid.read_card() ? RFID_EVENT_CARD_SCANNED : RFID_EVENT_CARD_SCAN_FAILED;
    return RFID_EVENT_NONE;
}

String rfid_get_uid() {
    return rfid.get_uid();
}

void card_sleep() {
    rfid.sleep_card();
}