#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         0
#define SS_PIN          2

#define RELAY D0 //relay pin
#define PUSH_BUTTON D2 //button pin
#define BUZZER D1 //Buzzer pin

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));


  //relay
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);

  //push button
  pinMode(PUSH_BUTTON, INPUT);
  digitalWrite(PUSH_BUTTON, HIGH);

  //buzzer
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {

    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  } else {
    Serial.println("cek bisa");
    showBuzzer();
    showSelenoid();
  }

  if(digitalRead(PUSH_BUTTON) == LOW) {
    showBuzzer();
    showSelenoid();
    delay(200);
    digitalWrite(PUSH_BUTTON, HIGH);
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  //	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  //  if (mfrc522.PICC_DumpToSerial(&(mfrc522.uid))== true) {
  //    Serial.print("cek bisa");
  //  }
  //
}

void showBuzzer() {
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
}

void showSelenoid() {
  digitalWrite(RELAY, LOW);
  delay(5000);
  digitalWrite(RELAY, HIGH);
}
