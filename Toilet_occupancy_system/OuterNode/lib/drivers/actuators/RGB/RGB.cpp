#include <Arduino.h>
#include "RGB_config.h"
#include "RGB.h"

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue) : RED_PIN(red), GREEN_PIN(green), BLUE_PIN(blue) {}

void RGB::init() {
    
    // Configure PWM
    ledcSetup(RED_CH, PWM_FREQ, PWM_RES);
    ledcSetup(GREEN_CH, PWM_FREQ, PWM_RES);
    ledcSetup(BLUE_CH, PWM_FREQ, PWM_RES);

    // Attach pins to the configured PWM channels
    ledcAttachPin(RED_PIN, RED_CH);
    ledcAttachPin(GREEN_PIN, GREEN_CH);
    ledcAttachPin(BLUE_PIN, BLUE_CH);

    Serial.printf("RGB Configured, R: %d G: %d, B: %d\n", RED_PIN, GREEN_PIN, BLUE_PIN);
    delay(200);
}

void RGB::show_color(uint8_t red, uint8_t green, uint8_t blue) {
    ledcWrite(RED_CH,   red);
    ledcWrite(GREEN_CH, green);
    ledcWrite(BLUE_CH,  blue);
}