/**
 * @file ultrasonic_config.h
 * @author Said Baraza (instagram: @baraza_rs)
 * @brief Ultrasonic sensor driver configuration.
 * @version 0.1
 * @date 2026-09-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#pragma once
#include <stdint.h>

constexpr float    SOUND_SPEED_cm_per_us = 0.0343f;
constexpr uint32_t ULTRASONIC_BURST_us   = 10;
constexpr uint32_t TIMEOUT_us            = 30000;