#include "communication.h"
#include "../../communication/esp_now/Esp_Now.h"
#include "../../system/system_events/us_events/us_sensor_events.h"

uint8_t received_event;
uint8_t sent_event;
EspNow esp_now;

typedef struct {
    
}communication_service_packet_t;


void communication_service_init() {
    esp_now.init();
}

bool send_state(uint8_t *notification) {
    if(esp_now.send(&notification, sizeof(notification))) return true;
    else return false;
}

bool is_data_available() {
    if(esp_now.available()) {
        esp_now.receive(&received_event, sizeof(received_event));
        return true;
    } else return false;
}
