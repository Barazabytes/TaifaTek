/**
 * @file toilet_protocol.h
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The toilet system states declaration
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#pragma once

#include <stdint.h>

enum class ToiletState : uint8_t {
    FREE = 0,
    OCCUPIED
};

enum class PacketType : uint8_t {
    OUTER_TRIGGER = 0,
    STATE_UPDATE
};

struct EspNowPacket {
    PacketType type;
    ToiletState state;
    uint16_t sequence;
};