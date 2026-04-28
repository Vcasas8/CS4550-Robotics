/*
  Stepper Motor Speed Test
  CS 4540 - Lab 08

  This program:
  - Spins the stepper continuously in one direction
  - Lets you time how long one full revolution takes
  - Gradually increases speed to find the maximum usable RPM
*/

#include <Stepper.h>

const int stepsPerRevolution = 400;   // 400 steps = 360 degrees

// Stepper connected to pins 8-11
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Starting speed (RPM)
int speedRPM = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Speed Test Starting...");
}

void loop() {

  // 1. Set speed and run one revolution
  myStepper.setSpeed(speedRPM);

  Serial.print("Speed: ");
  Serial.print(speedRPM);
  Serial.println(" RPM");

  Serial.println("Stepping one full revolution...");
  myStepper.step(stepsPerRevolution);   // 360 degrees

  // 2. Increase speed gradually
  speedRPM += 5;   // Increase speed by 5 RPM each cycle
  if (speedRPM > 200) {
    speedRPM = 10; // Reset if too fast
    Serial.println("Resetting speed back to 10 RPM");
  }

  delay(300);  // Short pause so you can observe behavior
}

