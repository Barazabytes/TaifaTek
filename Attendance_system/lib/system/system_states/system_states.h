#pragma once

typedef enum {
    // WiFi state
    WIFI_STATE_DISCONNECTED,

    // MQTT state
    MQTT_STATE_DISCONNECTED_FROM_A_SERVER,
    
    // RFID states
    RFID_STATE_IDLE,
    RFID_STATE_SCANNING,
    
    // Pub_sub_states
    PUBSUB_STATE_SUBSCRIBING_TO_A_TOPIC,
    PUBSUB_STATE_PUBLISHING_TO_A_TOPIC
}system_states_t;