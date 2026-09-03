#include <Arduino.h>
#include "sensors/ultrasonic/ultrasonic.h"
#include "actuators/pump/pump.h"
#include "sensors/ultrasonic/ultrasonic_config.h"
#include "MQTT/mqtt_service.h"
#include "WiFi/wifi_service.h"

Ultrasonic ultrasonic;
MQTTService mqttService;
WiFiService wifiService;

void setup() {
  Serial.begin(115200);

  // Initializing Wifi
  wifiService.WiFiBegin();

  // Initializing MQTT
  mqttService.MQTTConnect();

  // put your setup code here, to run once:
  Pump_init();
  ultrasonic.UltrasonicInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  int depth = ultrasonic.getDistance();
 
  if(depth >= SHALLOW_DEPTH) {
    Serial.println(depth);
    Serial.println("Tank is nearly Empty Starting the pump.");
    Pump_on();
  } else if(depth <= FULL_DEPTH) {
    Serial.println(depth);
    Serial.println("Tank is Full. Stopping the pump.");
    Pump_off();
  } else {
    Serial.println("Error reading distance.");
  }

  mqttService.MQTTPublish(String(depth).c_str());
  delay(100);
}
