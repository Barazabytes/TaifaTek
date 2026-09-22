#include <PubSubClient.h>
#include "mqtt_service.h"
#include "mqtt_config.h"
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

MQTTService* MQTTService::instance = nullptr;
void MQTTService::init() {
  is_connected    = false;
  done_connecting = false;
  published       = false;
  client.setServer(MQTT_DOMAIN, MQTT_PORT);

  response_received = false;

  received_payload = "";
  received_topic   = "";
  instance = this;

  client.setCallback(mqtt_callback);
}

bool MQTTService::is_mqtt_connect() {
  if(client.connected()) is_connected = true;
  else is_connected = false;

  return is_connected;
}

bool MQTTService::mqtt_connect() {
  if(client.connect(CLIENT_ID, MQTT_USER, MQTT_PASS)) done_connecting = true;
  else done_connecting = false;
  
  return done_connecting;
}


bool MQTTService::mqtt_publish(const char* topic, const char* payload) {
  if(!is_mqtt_connect()) return false;
  else return client.publish(topic, payload);
}

bool MQTTService::mqtt_subscribe(const char* topic) {
  if(!is_mqtt_connect()) return false;
  response_received = false;
  return client.subscribe(topic);
}

void MQTTService::mqtt_loop() {
  if(is_mqtt_connect()) client.loop();
  
}

void MQTTService::mqtt_callback(char* topic, byte* payload, unsigned int length) {
  if(instance == nullptr) return;

  instance->received_topic = String(topic);
  instance->received_payload = "";

  for(unsigned int i = 0; i < length; i++)
    instance->received_payload += static_cast<char>(payload[i]);

  instance->response_received = true;

  Serial.print("MQTT message received [");
  Serial.print(instance->received_topic);
  Serial.print("]: ");

  Serial.println(instance->received_payload);
}

bool MQTTService::message_received() {
  return response_received;
}


String MQTTService::get_received_payload() {
  return received_payload;
}


String MQTTService::get_received_topic() {
  return received_topic;
}


void MQTTService::clear_received_message() {
  response_received = false;
  received_payload = "";
  received_topic = "";
}