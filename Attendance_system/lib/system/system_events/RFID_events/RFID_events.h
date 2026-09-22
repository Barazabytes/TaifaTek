#pragma once

#include <Arduino.h>
typedef enum {
    RFID_EVENT_CARD_SCAN_FAILED,
    RFID_EVENT_CARD_AVAILABLE,
    RFID_EVENT_CARD_SCANNED,
    RFID_EVENT_NONE
} rfid_events_t;


void          rfid_events_init();
void          card_sleep();
String        rfid_get_uid();
rfid_events_t rfid_events_handler();
String        read_card();
