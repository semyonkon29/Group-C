#include <Arduino.h>

#define SENSOR 12

void testSetup() {
    Serial.begin(115200);
    pinMode(SENSOR, INPUT_PULLUP);
}

void testLoop() {
    Serial.println(digitalRead(SENSOR));
    delay(100);
}