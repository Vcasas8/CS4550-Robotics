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
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  long duration = pulseIn(echoPin, HIGH);

  // Convert to distance in cm
  float distanceCm = duration * 0.034 / 2.0;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Determine how many LEDs should turn on
  int ledCount = map(distanceCm, 0, 20, 0, 5);

  // Keep value within range
  if (ledCount < 0) {
    ledCount = 0;
  }
  if (ledCount > 5) {
    ledCount = 5;
  }

  // Update bar graph
  for (int i = 0; i < numLEDs; i++) {
    if (i < ledCount) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }

  delay(200);
}