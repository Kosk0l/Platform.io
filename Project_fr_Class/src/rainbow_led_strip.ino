#include <Arduino.h>

// Реле
const int relay = 5;

// Светильник
const int led = 17;

// Кнопки
const int b1P = 32;
const int b2P = 25;
const int b3P = 26;
const int b4P = 27;

// Пароль
String reader = "";
const String x = "2314";
bool flag = false;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  pinMode(b1P, INPUT);
  pinMode(b2P, INPUT);
  pinMode(b3P, INPUT);
  pinMode(b4P, INPUT);
}

void loop() {
  int b1 = digitalRead(b1P);
  int b2 = digitalRead(b2P);
  int b3 = digitalRead(b3P);
  int b4 = digitalRead(b4P);
  int counter = 0;

  if ((b1 == LOW) || (b2 == LOW) || (b3 == LOW) || (b4 == LOW)){
    reader += "2";
    counter++;
    delay(600);
    Serial.println("1");
    
    while (counter != 3) {
      if (b1 == LOW) {
        reader += "1";
        counter++;
        delay(600);
        Serial.println("1");
      }
      if (b3 == LOW) {
        reader += "3";
        counter++;
        delay(600);
        Serial.println("3");
      }
      if (b4 == LOW) {
        reader += "4";
        counter++;
        delay(600);
        Serial.println("4");
      }

    }

    if (reader == x) {
      Serial1.println("Good");
    }

  }

}