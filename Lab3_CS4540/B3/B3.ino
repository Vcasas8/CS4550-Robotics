/*
B-3. Program five LED's to act as random disco party lights
*/
const int ledPins[] = {5, 7, 9, 11, 13}; // Pins connected to LEDs
const int numLeds = 5;

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Initialize random seed for randomness
  randomSeed(analogRead(0));
}

void loop() {
  // Pick a random LED
  int activeLed = random(0, numLeds);
  
  // Turn it on for a random time
  digitalWrite(ledPins[activeLed], HIGH);
  delay(random(50, 200)); // Short flash
  
  // Turn it off
  digitalWrite(ledPins[activeLed], LOW);
  delay(random(10, 100)); // Short pause
}