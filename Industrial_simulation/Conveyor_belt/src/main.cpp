#include "actuators/TTmotor/TTmotor.h"
#include "esp_now/Esp_now.h"
#include "range/range.h"
#include <Arduino.h>

EspNowData received_data;
EspNowData sent_data;

// bool was

void setup() {
  Serial.begin(115200);

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

// Initialization of Range and TT motor.
    TTmotorInit();
    range_service_init();

    delay(2000);

}


void loop() {

    if (ESPNow_Available()) {
        received_data = ESPNow_GetData();
        Serial.println();
        Serial.println("Packet received:");

        Serial.print("Value: ");
        Serial.println(received_data.text);
    } 
    if(is_object_detected() == true) {
        if(received_data.text == "FULL") {
            received_data.text = "";
            TTmotorMove();
            delay(1000); // Waiting the glass to pass the US sensor.
        } else {
            TTmotorStop();
            sent_data.text = "FILL";
            ESPNow_Send(sent_data);
            sent_data.text = "";
            delay(5000);
        }
    
    } else if(is_object_detected() == false)
        TTmotorMove();

    print_distance();


  delay(200);

}
