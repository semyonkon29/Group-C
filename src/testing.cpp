#include <Arduino.h>

#define SENSOR 12

void setup() {
    Serial.begin(115200);
    pinMode(SENSOR, INPUT_PULLUP);
}

void loop() {
    Serial.println(digitalRead(SENSOR));
    delay(100);
}