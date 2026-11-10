#include <Arduino.h>

#define motor_a1 = 11
#define motor_a2 = 10
#define motor_b1 = 9
#define motor_b2 = 6
#define rot_sens_r1 = 13
#define rot_sens_r2 = 12

const int speed = 200;

void setup() {
  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);
  pinMode(rot_sens_r1, INPUT);
  pinMode(rot_sens_r2, INPUT);
}

void loop() {
  analogWrite(motor_a1, speed);
}
