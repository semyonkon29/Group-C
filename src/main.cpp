#include <Arduino.h>

#define motor_a1  10 // Left Forwards
#define motor_a2  11 // Left Backwards
#define motor_b1  9 // Right Forwards
#define motor_b2  6 // Right Backwards
#define rot_sens_r1  3 // Left wheel sensor
#define rot_sens_r2  2 // Right wheel sensor

volatile unsigned long leftPulses = 0;
volatile unsigned long rightPulses = 0;

const int calibration = 27; // Calibration value for the right motor speed adjustment
const int speed = 255;

const float wheelCircumference = 6.5 * PI;
const int pulsesPerRevolution = 20;

float distancePerPulse =
    wheelCircumference / pulsesPerRevolution;

float leftDistance = leftPulses * distancePerPulse;
float rightDistance = rightPulses * distancePerPulse;

float averageDistance =
    (leftDistance + rightDistance) / 2.0;

void setup() {
  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);
  pinMode(rot_sens_r1, INPUT_PULLUP);
  pinMode(rot_sens_r2, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  analogWrite(motor_a1, speed);
  analogWrite(motor_b1, speed - calibration);
}