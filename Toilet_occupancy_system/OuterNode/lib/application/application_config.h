/**
 * @file application_config.h
 * @author Said Baraza (barazars45@gmail.com)
 * @brief The application logic configuration file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#include <stdint.h>

static constexpr uint16_t THRESHOLD_DISTANCE_CM = 50;
static constexpr uint16_t RELEASE_MARGIN_CM = 10;

static constexpr uint32_t EVENT_TIMEOUT_MS = 4000;
static constexpr uint32_t LOOP_DELAY_MS = 60;

static constexpr const char *FREE_MSG = "FREE";
static constexpr const char *OCCUPIED_MSG = "OCCUPIED";