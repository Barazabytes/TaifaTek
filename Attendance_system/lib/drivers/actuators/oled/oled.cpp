#include "oled.h"
#include <Wire.h>
#include <Arduino.h>
#include "oled_config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

OLED::OLED(uint8_t sda, uint8_t scl) : SDA_PIN(sda), SCL_PIN(scl) {}

void OLED::init() {
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Clear the buffer
  display.clearDisplay();

  // Configure text properties
  display.setTextSize(1);             // Scale factor. 1 = 6x8 pixels per char
  display.setTextColor(SSD1306_WHITE); // Draw white text on a black background
  display.setCursor(0, 0);            // Start writing at the top-left corner (X=0, Y=0)
  display.clearDisplay();

}

void OLED::clear_display() {
    display.clearDisplay();
}

void OLED::print_ln(const char *statement) {
    display.println(statement);
}

void OLED::set_cursor(uint16_t row, uint16_t column) {
    display.setCursor(row, column);
}

void OLED::oled_display() {
    display.display();
}
