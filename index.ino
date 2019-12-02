#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define RST_PIN         0
#define SS_PIN          2

#define RELAY D0 //relay pin
#define PUSH_BUTTON D2 //button pin
#define BUZZER D1 //Buzzer pin

MFRC522 mfrc522(SS_PIN, RST_PIN);

char ssid[] = "Oren Basecamp"; // your network SSID (name)
char pass[] = "kochengoren!@#"; // your network password


//initialize RFID
String KEY_ALDI = "8F 5A AB EC";
String KEY_PANJI = "";
String KEY_HANA = "";
String KEY_RESTU = "";
String KEY_IKHWAN = "";
String KEY_SYAHRUR = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  
  //relay
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);

  //push button
  pinMode(PUSH_BUTTON, INPUT);
  digitalWrite(PUSH_BUTTON, HIGH);

  //buzzer
  pinMode(BUZZER, OUTPUT);

  //wifi
  WiFi.begin(ssid, pass);
}

void loop() {
  if (digitalRead(PUSH_BUTTON) == LOW) {
    Serial.println("Pintu Terbuka Melalui Button");
    showBuzzer();
    openDoor();
  }

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }


  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  } else {
    validateUser();
  }
}

void validateUser() {
  String content = "";
  byte letter;
  String message;

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  
  if (content.substring(1) == KEY_ALDI || content.substring(1) == KEY_PANJI || content.substring(1) == KEY_HANA || content.substring(1) == KEY_RESTU || content.substring(1) == KEY_IKHWAN || content.substring(1) == KEY_SYAHRUR)
  {
    if (content.substring(1) == KEY_ALDI) {
      message = "Pintu Terbuka Melalui RFID KEY_ALDI";
    } else if (content.substring(1) == KEY_PANJI) {
      message = "Pintu Terbuka Melalui RFID KEY_PANJI";
    } else if (content.substring(1) == KEY_HANA) {
      message = "Pintu Terbuka Melalui RFID KEY_HANA";
    } else if (content.substring(1) == KEY_RESTU) {
      message = "Pintu Terbuka Melalui RFID KEY_RESTU";
    } else if (content.substring(1) == KEY_IKHWAN) {
      message = "Pintu Terbuka Melalui RFID KEY_IKHWAN";
    } else if (content.substring(1) == KEY_SYAHRUR) {
      message = "Pintu Terbuka Melalui RFID KEY_SYAHRUR";
    }
    
    Serial.println(message);
    showBuzzer();
    openDoor();
  } 
  else 
  {
    message = "PINTU GAGAL DIBUKA RFID TIDAK TERDAFTAR";
    Serial.println(message);
    alertBuzzer();
  }
}

void showBuzzer() {
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
}

void alertBuzzer() {
  digitalWrite(BUZZER, HIGH);
  delay(3000);
  digitalWrite(BUZZER, LOW);
}

void openDoor() {
  digitalWrite(RELAY, LOW);
  delay(5000);
  digitalWrite(RELAY, HIGH);
}
