#include <SPI.h>
#include <MFRC522.h>
#include "HID-Project.h"
#define SS_PIN 10
#define RST_PIN 9

String LEFT_TAG_UID = "8DDFF378";
String UP_TAG_UID = "2DA61379";
String RIGHT_TAG_UID = "CE0BC757";
String DOWN_TAG_UID = "C3E8CF55";
String currentTagUID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);  
void setup() {                    
  Serial.begin(115200);            
  SPI.begin();                     
  mfrc522.PCD_Init();
  Keyboard.begin();
}
void loop() {
  
  while (readID()) {
    if (currentTagUID == LEFT_TAG_UID) {
      Keyboard.write(KEY_LEFT_ARROW);
      Serial.println("SOL");
    }

    if (currentTagUID == UP_TAG_UID) {
      Keyboard.write(KEY_UP_ARROW);
      Serial.println("YUKARI");
    }

    if (currentTagUID == RIGHT_TAG_UID) {
      Keyboard.write(KEY_RIGHT_ARROW);
      Serial.println("SAĞ");
    }

    if (currentTagUID == DOWN_TAG_UID) {
      Keyboard.write(KEY_DOWN_ARROW);
      Serial.println("AŞAĞI");
    }

    delay(500);
  }
}

boolean readID() {
  
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  currentTagUID = "";
  
  for (uint8_t i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      currentTagUID.concat("0");  
    }
    
    currentTagUID.concat(String(mfrc522.uid.uidByte[i], HEX));
   
    Serial.println(currentTagUID);
  }
  currentTagUID.toUpperCase();
  mfrc522.PICC_HaltA();  
  return true;
}
