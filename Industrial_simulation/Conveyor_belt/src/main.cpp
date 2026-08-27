#include "actuators/TTmotor/TTmotor.h"
#include "sensors/MPU6050/MPU6050.h"
#include "MQTT/mqtt_service.h"
#include "MQTT/mqtt_config.h"
#include <Arduino.h>

MQTTService mqttService;


void setup() {
  Serial.begin(115200);
  MPU6050_init();

  TTmotorInit();

  // WiFi connection should happen here first
  mqttService.MQTTConnect();
  mqttService.MQTTSubscribe("Filling/conveyor");


}

void loop() {

  mqttService.MQTTLoop();

  if (mqttService.MessageAvailable()) {

    String payload = mqttService.GetMessage();

    Serial.print("Application received: ");
    Serial.println(payload);
  
    if (payload == "present") {
      Serial.println("Stopping conveyor...");
      TTmotorStop();
    } else if(payload == "empty") {
      Serial.println("Running conveyor...");
      TTmotorMove();      
    }
  }

  VibrationData result = measureVibration();
  String freq = String(result.hertz);

  mqttService.MQTTPublish(MQTT_TOPIC2, freq.c_str());
  Serial.print(result.hertz);
  Serial.println(" Hz");

  delay(60);
}
