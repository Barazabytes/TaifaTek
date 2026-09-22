#include "system_events/PubSub_events/PubSub_events.h"
#include "system_events/WiFi_events/WiFi_events.h"
#include "system_events/MQTT_events/MQTT_events.h"
#include "system_events/RFID_events/RFID_events.h"
#include "../services/notification/sound/sound.h"
#include "../services/display/screen/screen.h"
#include "../drivers/actuators/oled/oled.h"
#include "system_states/system_states.h"
#include "system_controller.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  WiFi_events_init();
  mqtt_events_init();
  rfid_events_init();
  sound_services_init();
  screen_service_init();
}

  WiFi_event_t      system_wifi_events;
  mqtt_event_t      system_mqtt_events;
  rfid_events_t     system_rfid_events;
  pub_sub_events_t  system_pub_sub_events;

void loop() {

  mqtt_events_loop();
  system_wifi_events = WiFi_event_handler();
  system_mqtt_events = mqtt_event_handler();
  system_rfid_events = rfid_events_handler();
  system_pub_sub_events = pub_sub_event_handler();

  system_state_controller(system_wifi_events, system_mqtt_events, system_rfid_events, system_pub_sub_events);

  delay(100);
}

