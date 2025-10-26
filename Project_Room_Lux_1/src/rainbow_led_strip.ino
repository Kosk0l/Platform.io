#include <Arduino.h>
#include <String>

//============================================================================================

// горутина настройки
TaskHandle_t AutoT = NULL;
void Auto(void *pvParameters);
// bool flag = false;

// Реле
const int relay = 15;

// Светильник
const int led = 2;

// Датчик света
const int lux = 26;
const int sun = 2000; // Флаг освещенности

// Кнопки
const int b1P = 27;
const int b2P = 14;
const int b3P = 12;
const int b4P = 13;

// Пароль
String reader = "";
const String x = "2314";
bool flag = false;
int counter = 0;

//============================================================================================

void setup() {
    Serial.begin(115200);

    pinMode(relay, OUTPUT);
    digitalWrite(relay, LOW);

    pinMode(led, OUTPUT);

    pinMode(b1P, INPUT_PULLDOWN);
    pinMode(b2P, INPUT_PULLDOWN);
    pinMode(b3P, INPUT_PULLDOWN);
    pinMode(b4P, INPUT_PULLDOWN);

    digitalWrite(led, HIGH);
}

// горутина
void Auto(void *pvParameters) {
  while (true) {
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
}

//============================================================================================

void loop() {
    int ligth = analogRead(lux);
    int b1 = digitalRead(b1P);
    int b2 = digitalRead(b2P);
    int b3 = digitalRead(b3P);
    int b4 = digitalRead(b4P);
    
    // Нажатие
    if (b1 == HIGH) {
        reader += "1";
        counter++;
        delay(600);
        Serial.println("1");
    }
    if (b2 == HIGH) {
        reader += "2";
        counter++;
        delay(600);
        Serial.println("2");
    }
    if (b3 == HIGH) {
        reader += "3";
        counter++;
        delay(600);
        Serial.println("3");
    }
    if (b4 == HIGH) {
        reader += "4";
        counter++;
        delay(600);
        Serial.println("4");
    }

    // Проверка счетчика
    if (counter == 4) {
        // Проверка кода доступа
        if (reader == x) {
            Serial.println("Good password");
            counter = 0;
            reader = "";
            if (ligth < sun) {
                Serial.println("Good ligth");
                digitalWrite(relay, HIGH);
                digitalWrite(led, LOW);
                xTaskCreatePinnedToCore(Auto, "auto", 4096, NULL, 1, &AutoT, 0); // запуск горутины
                delay(10000); // ожидание
                if (AutoT != NULL) { // откл горутины
                    vTaskDelete(AutoT);
                    AutoT = NULL;
                }
                digitalWrite(relay, LOW);
                digitalWrite(led, HIGH);
            }
            else {
                Serial.println("Bad ligth");
            }
        }
        else {
            Serial.println("Bad password");
            counter = 0;
            reader = "";
        }
    }

}