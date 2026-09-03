#include "actuators/TTmotor/TTmotor.h"
#include "esp_now/Esp_now.h"
#include "sensors/IR/IR.h"
#include <Arduino.h>

EspNowData received_data;
EspNowData sent_data;

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

// Initialization of IR and TT motor.
    TTmotorInit();
    IR_init();

    delay(3000);

}


void loop() {

    if (ESPNow_Available()) {
        received_data = ESPNow_GetData();
        Serial.println();
        Serial.println("Packet received:");

        Serial.print("Value: ");
        Serial.println(received_data.text);
    }

    if(IRObjectDetected() == LOW) {
        TTmotorStop();
        sent_data.text = "FILL";
        ESPNow_Send(sent_data);
        sent_data.text = "";
        delay(3500);
    
    } else if(IRObjectDetected() == HIGH)
        TTmotorMove();
    else if(received_data.text == "FULL") {
        received_data.text = "";
        TTmotorMove();
    }

  delay(50);

}
