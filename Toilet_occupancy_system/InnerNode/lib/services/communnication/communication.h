#pragma once

#include <stdint.h>
#include "../../system/system_events/us_events/us_sensor_events.h"

void communication_service_init();
bool send_state(uint8_t notification);
bool is_data_available();
