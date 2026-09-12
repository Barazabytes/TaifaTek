#include <Arduino.h>
#include "actuators/traffic_lights/traffic_lights.h"
#include "sensors/ultrasonic/ultrasonic.h"

#define DETECTION_RANGE_cm 30
#define CORNER_RAMGE_cm    15 

bool flag_us1 = false;
bool flag_us2 = false;

TrafficLights tfl1(10, 9, 8);
TrafficLights tfl2(13, 12, 11);

Ultrasonic us_sensor1(7, 6);
Ultrasonic us_sensor2(3, 2);
Ultrasonic us_sensor0(5, 4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  tfl1.init();
  tfl2.init();
  us_sensor1.init();
  us_sensor2.init();
  us_sensor0.init();
}

void loop() {

int distance1 = static_cast<int>(us_sensor1.get_distance());
int distance2 = static_cast<int>(us_sensor2.get_distance());
int distance0 = static_cast<int>(us_sensor0.get_distance());


if(distance1 > 0 && distance1 <= DETECTION_RANGE_cm) {
  Serial.println("Car1 detected, Turning Red2 ON");
  tfl2.red_on();
  tfl2.yellow_off();
  tfl2.green_off();
  flag_us1 = true;
} else {
  tfl2.green_on();
  tfl2.red_off();
  tfl2.yellow_off();
}

if(distance2 > 0 && distance2 <= DETECTION_RANGE_cm) {
  Serial.println("Car2 detected, Turning Red1 ON");
  tfl1.red_on();
  tfl1.yellow_off();
  tfl1.green_off();
  flag_us2 = true;
} else {
  tfl1.green_on();
  tfl1.red_off();
  tfl1.yellow_off();
}

if((distance0 > 0 && distance0 <= CORNER_RAMGE_cm) && flag_us1 == true) {
  tfl2.yellow_on();
  tfl2.green_off();
  tfl2.red_off();
  delay(3000);
  flag_us1 = false;
} else if((distance0 > 0 && distance0 <= CORNER_RAMGE_cm) && flag_us2 == true) {
  tfl1.yellow_on();
  tfl1.green_off();
  tfl1.red_off();
  delay(3000);
  flag_us2 = false;
}

}
