#include <PubSubClient.h>
#include "mqtt_service.h"
#include "mqtt_config.h"
#include "WiFi/wifi_service.h"

WiFiClient espClient;
PubSubClient client(espClient);

void MQTTService::MQTTConnect() {
    client.setServer(MQTT_SERVER, MQTT_PORT);

    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("Tanesco_Client")) {
            Serial.println("connected to broker!");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds...");
            delay(5000);
        }
    }
}

bool MQTTService::MQTTPublish(const char* payload) {
    // client.setServer(MQTT_SERVER, MQTT_PORT);
    
    if (!client.connected()) {
        MQTTConnect();
    }

    if (client.publish(MQTT_TOPIC, payload)) {
        Serial.println("Message published successfully");
        return true;
    } else {
        Serial.println("Message publishing failed");
        return false;
    }
    
}