// ----- LED Setup -----
const int ledPins[] = {2, 3, 4, 5, 6};
const int numLeds = 5;
int currentIndex = 2;   // center LED

// ----- Rotary Encoder Pins -----
const int encoderCLK = 8;
const int encoderDT  = 10;
const int encoderSW  = 12;

// ----- Sequencer Control -----
int speed = 0;          // magnitude of speed
int direction = 0;      // -1 = left, +1 = right
unsigned long lastUpdate = 0;

const int baseInterval = 300;
const int minInterval  = 40;
int interval = baseInterval;

// ----- Encoder State -----
int lastCLK;
bool lastSW = HIGH;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT,  INPUT_PULLUP);
  pinMode(encoderSW,  INPUT_PULLUP);

  lastCLK = digitalRead(encoderCLK);
}

void loop() {

  // -------- ROTARY ENCODER ACCELERATION --------
  int currentCLK = digitalRead(encoderCLK);

  if (currentCLK != lastCLK) {

    // Determine direction
    if (digitalRead(encoderDT) != currentCLK) {
      direction = +1;      // accelerate right
    } else {
      direction = -1;      // accelerate left
    }

    speed++;   // EACH encoder step adds acceleration

    // Calculate new interval based on speed
    interval = max(minInterval, baseInterval - speed * 15);

    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.print("  Direction: ");
    Serial.println(direction == 1 ? "RIGHT" : "LEFT");
  }

  lastCLK = currentCLK;

  // -------- RESET (ENCODER SWITCH) --------
  bool swState = digitalRead(encoderSW);
  if (lastSW == HIGH && swState == LOW) {
    speed = 0;
    direction = 0;
    interval = baseInterval;
    currentIndex = 2;
    Serial.println("RESET");
  }
  lastSW = swState;

  // -------- LED SEQUENCER --------
  unsigned long now = millis();

  if (speed > 0 && (now - lastUpdate >= interval)) {
    lastUpdate = now;

    currentIndex += direction;

    // Hold at ends
    if (currentIndex < 0) currentIndex = 0;
    if (currentIndex >= numLeds) currentIndex = numLeds - 1;
  }

  // -------- DISPLAY LED --------
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], i == currentIndex ? HIGH : LOW);
  }
}