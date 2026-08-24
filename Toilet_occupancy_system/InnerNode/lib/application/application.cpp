/**
 * @file application.cpp
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The system logic implementation file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#include "application.h"
#include "application_config.h"

#include "../drivers/sensors/ultrasonic/ultrasonic.h"
#include "../services/esp_now/Esp_now.h"
#include "../services/protocols/toilet_protocol.h"

#include <Arduino.h>

Ultrasonic us_sensor;
EspNow espNow;

enum class OccupancyFsmState : uint8_t {
    FREE,
    WAIT_FOR_INNER,
    OCCUPIED,
    WAIT_FOR_OUTER
};

static OccupancyFsmState fsm_state =
    OccupancyFsmState::FREE;

static unsigned long wait_started_at = 0;

static uint16_t tx_sequence = 0;

static void sendStateUpdate(ToiletState state) {
    EspNowPacket packet {};

    packet.type = PacketType::STATE_UPDATE;
    packet.state = state;
    packet.sequence = ++tx_sequence;

    espNow.send(&packet, sizeof(packet));

    Serial.print("State update sent: ");

    if (state == ToiletState::OCCUPIED)
        Serial.println("OCCUPIED");
     else 
        Serial.println("FREE");
    
}

static void handleOuterTrigger() {
    switch (fsm_state) {

        case OccupancyFsmState::FREE:

            Serial.println(
                "Outer trigger received. Waiting for inner sensor."
            );

            fsm_state =
                OccupancyFsmState::WAIT_FOR_INNER;

            wait_started_at = millis();

            break;

        case OccupancyFsmState::WAIT_FOR_OUTER:

            Serial.println(
                "Outer trigger confirmed exit."
            );

            fsm_state =
                OccupancyFsmState::FREE;

            sendStateUpdate(ToiletState::FREE);

            break;

        case OccupancyFsmState::WAIT_FOR_INNER:

            // Duplicate outer event. Ignore it.
            Serial.println(
                "Duplicate outer trigger ignored."
            );

            break;

        case OccupancyFsmState::OCCUPIED:

            // An outside trigger while occupied does not prove
            // that the current user has exited.
            Serial.println(
                "Outer trigger ignored while occupied."
            );

            break;
    }
}

static void handleInnerTrigger() {
    switch (fsm_state) {

        case OccupancyFsmState::WAIT_FOR_INNER:

            Serial.println(
                "Inner trigger confirmed entrance."
            );

            fsm_state =
                OccupancyFsmState::OCCUPIED;

            sendStateUpdate(ToiletState::OCCUPIED);

            break;

        case OccupancyFsmState::OCCUPIED:

            Serial.println(
                "Inner trigger detected. Waiting for outer sensor."
            );

            fsm_state =
                OccupancyFsmState::WAIT_FOR_OUTER;

            wait_started_at = millis();

            break;

        case OccupancyFsmState::FREE:
            // An inner trigger without a preceding outer trigger
            // is not considered a valid entrance.
            Serial.println(
                "Unexpected inner trigger ignored while free."
            );

            break;

        case OccupancyFsmState::WAIT_FOR_OUTER:

            // Duplicate inner event. Ignore it.
            Serial.println(
                "Duplicate inner trigger ignored."
            );

            break;
    }
}

static void processTimeout() {
    unsigned long elapsed =
        millis() - wait_started_at;

    if (fsm_state ==
            OccupancyFsmState::WAIT_FOR_INNER &&
        elapsed >= EVENT_TIMEOUT_MS) {

        Serial.println(
            "Entrance sequence timed out. Returning to FREE."
        );

        fsm_state =
            OccupancyFsmState::FREE;
    }

    else if (
        fsm_state ==
            OccupancyFsmState::WAIT_FOR_OUTER &&
        elapsed >= EVENT_TIMEOUT_MS) {

        Serial.println(
            "Exit sequence timed out. Returning to OCCUPIED."
        );

        fsm_state =
            OccupancyFsmState::OCCUPIED;
    }
}

void Application::setup() {
    Serial.println("Inner Node starting.");

    espNow.init();
    us_sensor.UltrasonicInit();

    fsm_state =
        OccupancyFsmState::FREE;

    // Send the initial state to the Outer Node.
    sendStateUpdate(ToiletState::FREE);
}

void Application::run() {

    // Process incoming Outer Node events first.

    if (espNow.available()) {

        EspNowPacket packet {};

        espNow.receive( &packet, sizeof(packet));

        if (packet.type == PacketType::OUTER_TRIGGER)
            handleOuterTrigger();
    }


    // Detect one local inner-sensor event.

    if (us_sensor.triggered(THRESHOLD_DISTANCE_CM, RELEASE_MARGIN_CM)) {
        Serial.println("Inner ultrasonic trigger.");
        handleInnerTrigger();
    }

    processTimeout();

    delay(LOOP_DELAY_MS);
}