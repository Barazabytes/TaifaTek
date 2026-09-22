#include "../../../communication/MQTT/mqtt_service.h"
#include "../../../communication/MQTT/mqtt_config.h"
#include "../../../services/display/screen/screen.h"
#include "../../system_states/system_states.h"
#include "../PubSub_events/PubSub_events.h"
#include "../RFID_events/RFID_events.h"
#include "../../system_controller.h"
#include "MQTT_events.h"
#include <Arduino.h>
#include <WiFi.h>
#include "cJSON.h"

#define SERVER_TIMEOUT 5000
static const char *server_response;

bool is_scan_from_server_command = false;

MQTTService mqtt;

void mqtt_events_init() {
    mqtt.init();
}

bool mqtt_done_connecting() {
    return mqtt.mqtt_connect();
}

bool is_done_publishing(const char* topic, const char* payload) {
    if(mqtt.mqtt_publish(topic, payload)) return true;
    else return false;
}

bool is_done_subscribing (const char* topic) {
    if(mqtt.mqtt_subscribe(topic)) return true;
    else return false;
}

bool is_message_received() {
    if(is_done_subscribing(MQTT_TOPIC_REGISTER_CMD) && mqtt.message_received()) return true;
    else return false;
}

void mqtt_events_loop() {
    mqtt.mqtt_loop();
}

mqtt_event_t mqtt_event_handler () {
    if(mqtt.is_mqtt_connect()) return MQTT_EVENT_CONNECTED_TO_SERVER;
    else return MQTT_EVENT_DISCONNECTED_FROM_A_SERVER;
}



/**
 * @brief Implementation of the handler, This handler is like a backbone of the system.
 * 
 */

extern system_states_t system_state;
extern String uid;   // set once, when the card is scanned
extern rfid_events_t system_rfid_event;
extern pub_sub_events_t system_pub_sub_event;

pub_sub_events_t pub_sub_event_handler() {
    if (system_state == PUBSUB_STATE_PUBLISHING_TO_A_TOPIC) {
        // Building a cJSON data
        cJSON *root = cJSON_CreateObject();

        cJSON_AddStringToObject(root, "uid", uid.c_str());
        char* uid_string = cJSON_Print(root); 
        
        cJSON_free(uid_string);
        cJSON_Delete(root);
        
        if(is_scan_from_server_command) {
            bool ok = mqtt.mqtt_publish(MQTT_TOPIC_REGISTER_SCAN, uid_string);
            if(ok) {
                // is_scan_from_server_command = false;
                return PUBSUB_EVENT_UID_SENT_SUCCESSFULLY;
            } else return PUBSUB_EVENT_UID_SENT_FAILED;
            
        } else {
            bool ok = mqtt.mqtt_publish(MQTT_TOPIC_SCAN, uid_string);
            return ok ? PUBSUB_EVENT_UID_SENT_SUCCESSFULLY : PUBSUB_EVENT_UID_SENT_FAILED;
        }
    
    }

    if (system_state == PUBSUB_STATE_SUBSCRIBING_TO_A_TOPIC) {
        uint32_t server_timer_start = millis();
        while(!mqtt.message_received()) {
            mqtt_events_loop();
            if((millis() - server_timer_start) >= SERVER_TIMEOUT) {
                Serial.println("Server timeout!");
                return PUBSUB_EVENT_SERVER_TIMEOUT;
            }

            screen_clear_display();
            screen_set_cursor(25, 30);
            screen_print_ln("WAITING..!");
            screen_oled_display();
            Serial.println("Waiting for Server Response..");
            delay(500);
        }
    
        String topic = mqtt.get_received_topic();
        String payload = mqtt.get_received_payload();

        Serial.println("Server response received!");

        Serial.print("Topic: ");
        Serial.println(topic);

        Serial.print("Payload: ");
        Serial.println(payload);

        if(topic == MQTT_TOPIC_REGISTER_CMD && is_scan_from_server_command == true) {
            is_scan_from_server_command = false;
            //   Process/save payload.
            cJSON *json = cJSON_Parse(payload.c_str());

            if (json == NULL) Serial.println("Error parsing JSON string.");

            cJSON *registration = cJSON_GetObjectItemCaseSensitive(json, "registration");
            cJSON *std_name = cJSON_GetObjectItemCaseSensitive(json, "student_name");

            // Validate REQUIRED fields
            if (cJSON_IsString(registration)) {

                // Default value for optional student_name
                const char *student_name = "Scan Failed";

                // Override default only if student_name exists and is a string
                if (cJSON_IsString(std_name) && std_name->valuestring != NULL) student_name = std_name->valuestring;

                Serial.printf(
                    "Registration: %s\nStudent: %s\n",
                    registration->valuestring,
                    student_name
                );

                screen_clear_display();

                screen_set_cursor(25, 10);
                screen_print_ln(registration->valuestring);
                screen_set_cursor(10, 25);
                screen_print_ln(student_name);
                screen_oled_display();

                delay(3000);  // A delay so a user can see the texts
            }

            cJSON_Delete(json); 

            mqtt.clear_received_message();     

            return PUBSUB_EVENT_SERVER_RESPONDED_SUCCESSFULLY;
        } else {

            //   Process/save payload.
            cJSON *json = cJSON_Parse(payload.c_str());
    
            if (json == NULL) Serial.println("Error parsing JSON string.");
    
            cJSON *status   = cJSON_GetObjectItemCaseSensitive(json, "status");
            cJSON *code     = cJSON_GetObjectItemCaseSensitive(json, "code");
            cJSON *message  = cJSON_GetObjectItemCaseSensitive(json, "message");
            cJSON *std_name = cJSON_GetObjectItemCaseSensitive(json, "student_name");
    
            // Validate REQUIRED fields
            if (cJSON_IsString(status) && cJSON_IsString(code) && cJSON_IsString(message)) {
    
                // Default value for optional student_name
                const char *student_name = "Thank you!";
    
                // Override default only if student_name exists and is a string
                if (cJSON_IsString(std_name) && std_name->valuestring != NULL) student_name = std_name->valuestring;
    
                Serial.printf(
                    "Status: %s\nCode: %s\nStudent: %s\nMessage: %s\n",
                    status->valuestring,
                    code->valuestring,
                    student_name,
                    message->valuestring
                );
    
                screen_clear_display();
    
                screen_set_cursor(5, 10);
                screen_print_ln(code->valuestring);
                screen_set_cursor(5, 25);
                screen_print_ln(student_name);
    
                screen_oled_display();
    
                delay(3000);  // A delay so a user can see the texts
            }
    
            cJSON_Delete(json); 
    
            mqtt.clear_received_message();
                
            return PUBSUB_EVENT_SERVER_RESPONDED_SUCCESSFULLY;
        }
        
    }

    if(system_state == RFID_STATE_IDLE) {
        while(!is_message_received()) {
            mqtt_events_loop();
            if(system_rfid_event == RFID_EVENT_CARD_AVAILABLE) {
                system_rfid_event == RFID_EVENT_CARD_AVAILABLE;
                break;
            } else if(system_rfid_event == RFID_EVENT_NONE) {
                system_rfid_event == RFID_EVENT_NONE;
                break;
            } else if(system_pub_sub_event == PUBSUB_EVENT_SERVER_CMD_AVAILABLE) {
                system_pub_sub_event == PUBSUB_EVENT_SERVER_CMD_AVAILABLE;
                break;
            }
        }
            String topic = mqtt.get_received_topic();
        
            if((topic == MQTT_TOPIC_REGISTER_CMD)){
                is_scan_from_server_command = true;
                return PUBSUB_EVENT_SERVER_CMD_AVAILABLE;
            }         
    }

    return PUBSUB_EVENT_NONE;
}