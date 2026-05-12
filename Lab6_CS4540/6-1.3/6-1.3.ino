/*
Rotary Encoder LED Dimmer
Uses quadrature encoder to control PWM brightness
*/

// ----- Pin Assignments -----
const byte pinA   = 8;    // Encoder CLK
const byte pinB   = 10;   // Encoder DT
const byte pinSW  = 12;   // Encoder Switch
const byte ledPin = 5;    // PWM LED (must be PWM-capable)

// ----- Encoder State -----
int pinA_read;
int pinA_previous;
int pinB_read;
int pinB_previous;

bool lastSW = HIGH;

// ----- Brightness -----
int brightness = 128;   // start at mid brightness
boolean bCW;

void setup() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  pinA_read = digitalRead(pinA);
  pinB_read = digitalRead(pinB);
  pinA_previous = pinA_read;
  pinB_previous = pinB_read;

  Serial.begin(9600);
  analogWrite(ledPin, brightness);
}

void loop() {

  pinA_read = digitalRead(pinA);
  pinB_read = digitalRead(pinB);

  // ----- ROTATION DETECTION -----
  if (pinA_read != pinA_previous && pinB_read != pinB_previous) {
    Serial.println("Invalid input");
  }
  else if (pinA_read != pinA_previous || pinB_read != pinB_previous) {

    if (pinA_read != pinA_previous) {       // A changed
      if (pinB_read != pinA_read) {
        brightness += 5;    // CW
        bCW = true;
      } else {
        brightness -= 5;    // CCW
        bCW = false;
      }
    }
    else {                                  // B changed
      if (pinB_read == pinA_read) {
        brightness += 5;    // CW
        bCW = true;
      } else {
        brightness -= 5;    // CCW
        bCW = false;
      }
    }

    brightness = constrain(brightness, 0, 255);
    analogWrite(ledPin, brightness);

    Serial.print("Direction: ");
    Serial.print(bCW ? "CW" : "CCW");
    Serial.print(" | Brightness: ");
    Serial.println(brightness);

    pinA_previous = pinA_read;
    pinB_previous = pinB_read;
  }

  // ----- ENCODER SWITCH (RESET) -----
  bool swState = digitalRead(pinSW);
  if (lastSW == HIGH && swState == LOW) {
    brightness = 0;
    analogWrite(ledPin, brightness);
    Serial.println("RESET: Brightness = 0");
  }
  lastSW = swState;
}
