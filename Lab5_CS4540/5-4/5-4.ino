// ----- LED Setup -----
const int ledPins[] = {2, 3, 4, 5, 6};
const int numLeds = 5;
int currentIndex = 2;

// ----- Button Pins -----
const int btnLeft  = 8;
const int btnRight = 10;
const int btnReset = 12;

// ----- Sequencer Control -----
int speed = 0;
int direction = 0;   // -1 = left, +1 = right
unsigned long lastUpdate = 0;

int baseInterval = 300;
int minInterval  = 40;
int interval = baseInterval;

// ----- Button state tracking (IMPORTANT) -----
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

  // Read current button states
  bool leftState  = digitalRead(btnLeft);
  bool rightState = digitalRead(btnRight);
  bool resetState = digitalRead(btnReset);

  // ----- LEFT BUTTON (edge-detect) -----
  if (lastLeft == HIGH && leftState == LOW) {
    Serial.println("LEFT pressed");
    direction = -1;
    speed++;
    interval = max(minInterval, baseInterval - speed * 20);
  }

  // ----- RIGHT BUTTON (edge-detect) -----
  if (lastRight == HIGH && rightState == LOW) {
    Serial.println("RIGHT pressed");
    direction = +1;
    speed++;
    interval = max(minInterval, baseInterval - speed * 20);
  }

  // ----- RESET BUTTON (edge-detect) -----
  if (lastReset == HIGH && resetState == LOW) {
    Serial.println("RESET");
    currentIndex = 2;
    speed = 0;
    direction = 0;
    interval = baseInterval;
  }

  // Save button states
  lastLeft  = leftState;
  lastRight = rightState;
  lastReset = resetState;

  // ----- LED SEQUENCER -----
  unsigned long now = millis();

  if (speed > 0 && (now - lastUpdate >= interval)) {
    lastUpdate = now;

    currentIndex += direction;

    if (currentIndex >= numLeds) currentIndex = 0;
    if (currentIndex < 0) currentIndex = numLeds - 1;
  }

  // ----- DISPLAY LED -----
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], i == currentIndex ? HIGH : LOW);
  }
}