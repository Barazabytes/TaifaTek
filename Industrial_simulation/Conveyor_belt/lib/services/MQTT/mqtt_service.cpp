#include <PubSubClient.h>
#include "mqtt_service.h"
#include "mqtt_config.h"
#include "WiFi/wifi_service.h"

WiFiService wifi_ser;
WiFiClient espClient;
PubSubClient client(espClient);

String MQTTService::receivedMessage = "";
String MQTTService::receivedTopic = "";
bool MQTTService::messageAvailable = false;

void MQTTService::MQTTConnect() {

    wifi_ser.WiFiBegin();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(MQTTCallback);

    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        if (client.connect("Raspberry_pi_server")) {
            Serial.println("connected to broker!");

            // Subscribe after every connection/reconnection
            client.subscribe(MQTT_TOPIC);

        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void MQTTService::MQTTPublish(const char* topic, const char* payload) {
    if (!client.connected()) {
        MQTTConnect();
    }

    if (client.publish(topic, payload)) {
        Serial.println("Message published successfully");
    } else {
        Serial.println("Message publishing failed");
    }
}

void MQTTService::MQTTSubscribe(const char* topic) {
    if (!client.connected()) {
        MQTTConnect();
    }

    if (client.subscribe(topic)) {
        Serial.print("Subscribed to: ");
        Serial.println(topic);
    } else {
        Serial.println("Subscription failed");
    }
}

void MQTTService::MQTTLoop() {
    if (!client.connected()) {
        MQTTConnect();
    }

    client.loop();
}

void MQTTService::MQTTCallback(char* topic, byte* payload, unsigned int length) {
    receivedMessage = "";

    for (unsigned int i = 0; i < length; i++)
        receivedMessage += (char)payload[i];
    
    receivedTopic = String(topic);
    messageAvailable = true;

    Serial.print("Received [");
    Serial.print(receivedTopic);
    Serial.print("]: ");
    Serial.println(receivedMessage);
}

// The getter fuctions implementation
bool MQTTService::MessageAvailable() {
    return messageAvailable;
}

String MQTTService::GetMessage() {
    messageAvailable = false;
    return receivedMessage;
}

String MQTTService::GetTopic() {
    return receivedTopic;
}