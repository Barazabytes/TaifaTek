#include "actuators/pump/pump.h"
#include "esp_now/Esp_now.h"
#include <Arduino.h>

EspNowData sent_data;
EspNowData received_data;

void setup() {
  Serial.begin(115200);
  Pump_init();

//   Initialization of the ESP_NOW protocol.
  if (!ESPNow_Init()) {
      Serial.println("ESP-NOW startup failed");
      while (true)
        delay(1000);
  }

  if (!ESPNow_AddPeer()) {
      Serial.println("Could not register receiver");
      while (true)
          delay(1000);
  }

  delay(2000);
}

void loop() {

  // If glass available and conveyor stopped, then switch on Pump for filling a glass for 2 seconds.
  if(ESPNow_Available()) {
    received_data = ESPNow_GetData();
    Serial.print("Received: ");
    Serial.println(received_data.text);
  }

  if(received_data.text == "FILL") {
    received_data.text = "";
    Serial.println("Filling a glass for 2 seconds...");
    Pump_on();
    delay(2000);

    sent_data.text = "FULL";
    ESPNow_Send(sent_data);
    sent_data.text = "";
    Serial.println("Sent: FULL");

  } else {
    Serial.println("No glass available, stopping the pump...");
    Pump_off();
  }
    
  
  delay(100);
}
