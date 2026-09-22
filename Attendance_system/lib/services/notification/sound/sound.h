#pragma once

#include "../drivers/actuators/buzzer/buzzer.h"

void sound_services_init            ();
void wifi_connected                 ();
void wifi_disconnected              ();
void mqtt_connected                 ();
void mqtt_disconnected              ();
void rfid_scanned_successfully      ();
void rfid_scanned_unsuccessfully    ();
void server_publish_successfully    ();
void server_publish_unsuccessfully  ();
void server_responded_successfully  ();
void server_responded_unsuccessfully();
