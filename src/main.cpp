#include <Arduino.h>

#define motor_a1  10 // Left Forwards actually a2
#define motor_a2  11 // Left Backwards actually a1
#define motor_b1  9 // Right Forwards
#define motor_b2  6 // Right Backwards
#define rot_sens_r1  3 // Left wheel sensor
#define rot_sens_r2  2 // Right wheel sensor

volatile unsigned long leftPulses = 0;
volatile unsigned long rightPulses = 0;

void leftISR() {
    leftPulses++;
}

void rightISR() {
    rightPulses++;
}

const int calibration = 0; // Calibration value for the right motor speed adjustment
const int speed = 255;

const float wheelCircumference = 6.5 * PI;
const int pulsesPerRevolution = 20;

float distancePerPulse =
    wheelCircumference / pulsesPerRevolution;

bool run = true;

void goForward(int speed) {
  analogWrite(motor_a1, speed);
  analogWrite(motor_b1, speed - calibration);
  analogWrite(motor_a2, 0);
  analogWrite(motor_b2, 0);
}
void goBackward(int speed) {
  analogWrite(motor_a1, 0);
  analogWrite(motor_b1, 0);
  analogWrite(motor_a2, speed);
  analogWrite(motor_b2, speed - calibration);
}
void stopMotors() {
  analogWrite(motor_a1, 0);
  analogWrite(motor_b1, 0);
  analogWrite(motor_a2, 0);
  analogWrite(motor_b2, 0);
  leftPulses = 0;
  rightPulses = 0;
}

void mb() {
    goBackward(speed);
  unsigned long left;
  unsigned long right;

  noInterrupts();
  left = leftPulses;
  right = rightPulses;
  interrupts();

  float leftDistance = leftPulses * distancePerPulse;
  float rightDistance = rightPulses * distancePerPulse;

  float averageDistance =
      (leftDistance + rightDistance) / 2.0;

  Serial.print("Left distance: ");
  Serial.print(leftDistance);
  Serial.print(" | Right distance: ");
  Serial.print(rightDistance);
  Serial.print(" | Average distance: ");
  Serial.print(averageDistance);
  Serial.println("cm");
  delay(200);
}

void mf() {

  goForward(speed);

  unsigned long left;
  unsigned long right;

  noInterrupts();
  left = leftPulses;
  right = rightPulses;
  interrupts();

  float leftDistance = leftPulses * distancePerPulse;
  float rightDistance = rightPulses * distancePerPulse;

  float averageDistance =
      (leftDistance + rightDistance) / 2.0;

  Serial.print("Left distance: ");
  Serial.print(leftDistance);
  Serial.print(" | Right distance: ");
  Serial.print(rightDistance);
  Serial.print(" | Average distance: ");
  Serial.print(averageDistance);
  Serial.println("cm");
  delay(200);
  if (averageDistance >= 100) {
    while (averageDistance < 200){
      mb(); 
    }
    run = false;
  }
}

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
    if (run) {
        mf();
    }
    else {
        stopMotors();
    }
}
