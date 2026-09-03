#pragma once

class MQTTService {
public:
    void MQTTConnect();
    bool MQTTPublish(const char* payload);
};