/*
  Stepper Motor 180-Degree Swing Test
  CS 4540 – Lab 08

  This program:
  - Rotates the stepper motor 180 degrees forward
  - Then rotates 180 degrees backward
  - Repeats forever so you can test accuracy

  Use pliers or a binder clip to stop the shaft briefly.
  Observe whether it returns to the same start point.
*/

#include <Stepper.h>

const int stepsPerRevolution = 400;   // Your motor is 400 steps for 360°
const int halfTurn = stepsPerRevolution / 2;  // 180° = 200 steps

// Stepper connected to pins 8–11
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper 180-degree swing test starting…");

  myStepper.setSpeed(60);  // RPM
}

void loop() {

  Serial.println("Forward 180 degrees...");
  myStepper.step(halfTurn);
  delay(500);

  Serial.println("Backward 180 degrees...");
  myStepper.step(-halfTurn);
  delay(500);

  // The motor should return to the exact same physical position each cycle
}