#include <Arduino.h>

#define LEFT_SENSOR  2
#define RIGHT_SENSOR 3

volatile unsigned long leftPulses = 0;
volatile unsigned long rightPulses = 0;

void leftISR() {
    leftPulses++;
}

void rightISR() {
    rightPulses++;
}

void setup() {
    Serial.begin(115200);

    pinMode(LEFT_SENSOR, INPUT_PULLUP);
    pinMode(RIGHT_SENSOR, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR),
                    leftISR, FALLING);

    attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR),
                    rightISR, FALLING);
}

void loop() {
    unsigned long left, right;

    noInterrupts();
    left = leftPulses;
    right = rightPulses;
    interrupts();

    Serial.print("Left pulses: ");
    Serial.print(left);
    Serial.print(" | Right pulses: ");
    Serial.println(right);

    delay(200);
}
