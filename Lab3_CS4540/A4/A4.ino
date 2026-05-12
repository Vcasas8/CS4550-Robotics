/*
A-4. Write a program that will slowly bring up the brightness of the 
LED from completely off to fully on (0% - 100%) 
over the span of about 2 seconds. Have it continuously repeat the 0-100 
or have it continuously cycle 0->100>0.
*/
const int ledPin = 3;  // PWM pin

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Fade from 0% to 100%
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(8);  // 256 steps × 8ms ≈ 2048ms (≈2 seconds)
  }

  // Fade from 100% back to 0%
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(8);
  }
}

