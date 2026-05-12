// ----- LED Setup -----
const int ledPins[] = {2, 3, 4, 5, 6};
const int numLeds = 5;

// ----- Button Pins -----
const int btnLeft  = 8;   // Count DOWN
const int btnRight = 10;  // Count UP
const int btnReset = 12;  // Reset to 0

// ----- Counter -----
int count = 0;            // 0–31 (5 bits)

// ----- Button State Tracking -----
bool lastLeft  = HIGH;
bool lastRight = HIGH;
bool lastReset = HIGH;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(btnLeft,  INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);
  pinMode(btnReset, INPUT_PULLUP);
}

void loop() {

  // Read button states
  bool leftState  = digitalRead(btnLeft);
  bool rightState = digitalRead(btnRight);
  bool resetState = digitalRead(btnReset);

  // ----- COUNT UP -----
  if (lastRight == HIGH && rightState == LOW) {
    count++;
    if (count > 31) count = 31;   // clamp
    Serial.print("Count UP: ");
    Serial.println(count);
  }

  // ----- COUNT DOWN -----
  if (lastLeft == HIGH && leftState == LOW) {
    count--;
    if (count < 0) count = 0;     // clamp
    Serial.print("Count DOWN: ");
    Serial.println(count);
  }

  // ----- RESET -----
  if (lastReset == HIGH && resetState == LOW) {
    count = 0;
    Serial.println("RESET to 0");
  }

  // Save button states
  lastLeft  = leftState;
  lastRight = rightState;
  lastReset = resetState;

  // ----- DISPLAY BINARY ON LEDs -----
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], (count >> i) & 1);
  }
}