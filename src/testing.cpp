
#include <Arduino.h>

#define LEFT_SENSOR  13
#define RIGHT_SENSOR 12

void setup() {
    Serial.begin(115200);

    pinMode(LEFT_SENSOR, INPUT_PULLUP);
    pinMode(RIGHT_SENSOR, INPUT_PULLUP);
}

void loop() {
    Serial.print("Left: ");
    Serial.print(digitalRead(LEFT_SENSOR));

    Serial.print(" | Right: ");
    Serial.println(digitalRead(RIGHT_SENSOR));

    delay(50);
}
