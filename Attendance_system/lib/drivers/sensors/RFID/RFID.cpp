#include "RFID_config.h"
#include <Arduino.h>
#include <MFRC522.h>
#include "RFID.h"
#include <SPI.h>

MFRC522 mfrc522(CHIP_SELECT_PIN, RESET_PIN);

void RFID::init() {
    SPI.begin();
    mfrc522.PCD_Init();
    delay(200);

    Serial.println("RFID Reader Online.!");

}

bool RFID::is_card_available() {
    return mfrc522.PICC_IsNewCardPresent();
}

bool RFID::read_card() {
  return mfrc522.PICC_ReadCardSerial();                                 // managed to read card
}

void RFID::sleep_card() {
    mfrc522.PICC_HaltA();
}

String RFID::get_uid() {
    String uid = "";

    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(mfrc522.uid.uidByte[i], HEX);
    }

    uid.toUpperCase();

    return uid;
}
