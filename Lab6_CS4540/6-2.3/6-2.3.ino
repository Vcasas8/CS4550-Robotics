int trigPin = 6;
int echoPin = 7;

int leds[] = {2, 3, 4, 5, 8};
int numLEDs = 5;

void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("Ultrasonic LED Bar Graph");
  Serial.println("-------------------");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH);

  float distanceCm = duration * 0.034 / 2.0;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Map distance 10cm–100cm to 0–5 LEDs
  int ledCount = map(distanceCm, 10, 100, 0, 5);

  // Clamp values
  if (distanceCm < 10) {
    ledCount = 0;
  }
  if (distanceCm > 100) {
    ledCount = 5;
  }

  // Update LEDs
  for (int i = 0; i < numLEDs; i++) {
    if (i < ledCount) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }

  delay(200);
}