/**
 * @file application.cpp
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The logic file implementation
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "application.h"
#include "application_config.h"

#include "../drivers/sensors/ultrasonic/ultrasonic.h"
#include "../drivers/actuators/lcd/lcd.h"
#include "../services/esp_now/Esp_now.h"
#include "../services/protocols/toilet_protocol.h"

#include <Arduino.h>

Ultrasonic us_sensor;
LcdDisplay lcd_display;
EspNow espNow;

static ToiletState displayed_state = ToiletState::FREE;

static uint16_t tx_sequence = 0;

static void displayToiletState(ToiletState state) {

    // Avoid clearing and rewriting the LCD continuously.
    if (state == displayed_state)
        return;

    displayed_state = state;

    if (state == ToiletState::OCCUPIED) {

        lcd_display.print(OCCUPIED_MSG);
        Serial.println("LCD: OCCUPIED");
    }

    else {

        lcd_display.print(FREE_MSG);
        Serial.println("LCD: FREE");
    }
}


static void sendOuterTrigger() {
    EspNowPacket packet {};

    packet.type =
        PacketType::OUTER_TRIGGER;

    // This field is ignored for an OUTER_TRIGGER packet.
     
    packet.state = displayed_state;

    packet.sequence = ++tx_sequence;

    espNow.send(&packet, sizeof(packet));

    Serial.print("Outer trigger sent. Sequence: ");

    Serial.println(packet.sequence);
}

void Application::setup() {
    Serial.println("Outer Node starting.");

    espNow.init();
    lcd_display.begin();
    us_sensor.UltrasonicInit();

    
    // Set a temporary different value so that
    // displayToiletState() performs the initial write.
    
    displayed_state = ToiletState::OCCUPIED;

    displayToiletState(ToiletState::FREE);
}

void Application::run() {
    
    //  Generate one event when someone enters
    //  the outer sensor's detection zone.
    
    if (us_sensor.triggered(THRESHOLD_DISTANCE_CM, RELEASE_MARGIN_CM)) {

        Serial.println("Outer ultrasonic trigger.");

        sendOuterTrigger();
    }

    
    // Receive state decisions from the Inner Node.
    
    if (espNow.available()) {

        EspNowPacket packet {};

        espNow.receive(&packet, sizeof(packet));

        if (packet.type == PacketType::STATE_UPDATE) {

            displayToiletState( packet.state );
        }
    }

    delay(LOOP_DELAY_MS);
}
