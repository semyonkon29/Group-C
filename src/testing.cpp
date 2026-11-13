#include <Arduino.h>

#define motor_a1  10 // Left Forwards
#define motor_a2  11 // Left Backwards
#define motor_b1  9 // Right Forwards
#define motor_b2  6 // Right Backwards
#define rot_sens_r1  3 // Left wheel sensor
#define rot_sens_r2  2 // Right wheel sensor

volatile unsigned long leftPulses = 0;
volatile unsigned long rightPulses = 0;

void calibrateMotors(float leftDistance, float rightDistance);

void leftISR() {
    leftPulses++;
}

void rightISR() {
    rightPulses++;
}

int rSpeed = 200;
int lSpeed = 200;

const float wheelCircumference = 6.5 * PI;
const int pulsesPerRevolution = 20;

float distancePerPulse =
    wheelCircumference / pulsesPerRevolution;

void setup() {
  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);

  pinMode(rot_sens_r1, INPUT_PULLUP);
  pinMode(rot_sens_r2, INPUT_PULLUP);
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(rot_sens_r1), leftISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(rot_sens_r2), rightISR, FALLING);
}

void loop() {
  analogWrite(motor_a1, lSpeed);
  analogWrite(motor_b1, rSpeed);

  unsigned long left;
  unsigned long right;

  noInterrupts();
  left = leftPulses;
  right = rightPulses;
  interrupts();

  float leftDistance = left * distancePerPulse;
  float rightDistance = right * distancePerPulse;

  float averageDistance = (leftDistance + rightDistance) / 2.0;

  Serial.print(" | Left distance: ");
  Serial.print(leftDistance);
  Serial.print(" | Right distance: ");
  Serial.print(rightDistance);
  Serial.print(" | Average distance: ");
  Serial.print(averageDistance);
  Serial.println("cm");
  delay(200);
  calibrateMotors(leftDistance, rightDistance);
}

void calibrateMotors(float leftDistance, float rightDistance) {
    if (leftDistance > rightDistance) {
        lSpeed = 200 * rSpeed / lSpeed;
    }
    else if (rightDistance > leftDistance) {
        rSpeed = 200 * lSpeed / rSpeed;
    }
    Serial.print("Left speed: ");
    Serial.print(lSpeed);
    Serial.print(" | Right speed: ");
    Serial.println(rSpeed);
}