/**
 * @file lcd.cpp
 * @author Said Baraza (barazars45@gmail.com)
 * @brief LCD driver implementation file
 * @version 0.1
 * @date 2026-08-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "lcd.h"
#include "lcd_config.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void LcdDisplay::begin() {
    Wire.begin(SDA_PIN, CLK_PIN);

    lcd.init();                  // Initialize the LCD
    lcd.backlight();             // Turn on backlight
}


void LcdDisplay::print(const String& msg) {
    lcd.clear();                
    lcd.setCursor(0, 0);
    lcd.print(msg.c_str());

    lcd.setCursor(8, 1);
    lcd.print(MAKER);
}