#include <Servo.h>

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {

  Serial.println("Measuring 180 degree movement...");

  unsigned long startTime = millis();

  myServo.write(180);   // move to 180

  delay(1000); // give it time to complete movement

  unsigned long endTime = millis();

  unsigned long duration = endTime - startTime;

  Serial.print("Time for 180 degrees (ms): ");
  Serial.println(duration);

  delay(3000);

  // move back to start for repeat
  myServo.write(0);
  delay(2000);
}