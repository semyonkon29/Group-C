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

int calibration = 0; // Calibration value for the right motor speed adjustment
const int speed = 200;

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
  analogWrite(motor_a1, speed);
  analogWrite(motor_b1, speed - calibration);

  unsigned long left;
  unsigned long right;

  noInterrupts();
  left = leftPulses;
  right = rightPulses;
  interrupts();

  float leftDistance = left * distancePerPulse;
  float rightDistance = right * distancePerPulse;

  float averageDistance = (leftDistance + rightDistance) / 2.0;

  Serial.print("Calibration: ");
  Serial.print(calibration);
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
    float difference = leftDistance - rightDistance;

    if (difference > 1.0) {
        calibration -= 1;
    }
    else if (difference < -1.0) {
        calibration += 1;
    }

    calibration = constrain(calibration, -100, 100);
}