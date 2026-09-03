#include <Arduino.h>
#include "sensors/mpu6050/mpu6050.h"
#include "MQTT/mqtt_service.h"
#include "sensors/mpu6050/mpu6050_config.h"
#include "WiFi/wifi_service.h"

WiFiService wifiService;
MQTTService mqttService;

bool alertSent = false;

const float TILT_THRESHOLD = 50.0;

void setup() {
    Serial.begin(115200);
    wifiService.WiFiBegin();
    delay(1000);

    mqttService.MQTTConnect();
    delay(1000);

    mpu6050_init();
}

void loop() {

  float angle = tilt_angle();

  Serial.print("Tilt Angle: ");
  Serial.println(angle);

  if (angle >= TILT_THRESHOLD && !alertSent) {

    delay(3000);

      // Confirm that the pole is still tilted
      angle = tilt_angle();

      if (angle >= TILT_THRESHOLD) {
        const char payload[] = MAP_URL;

          if (mqttService.MQTTPublish(payload)) {
            Serial.println("Pole fall alert published.");
            alertSent = true;
          }
      }
  }

  delay(5000);
}