// Ultrasonic pins
int trigPin = 6;
int echoPin = 7;

// Button pin
int buttonPin = 8;

// Unit toggle
bool useMetric = true;

// Button tracking
int lastButtonState = LOW;

void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("Ultrasonic Distance Reader");
  Serial.println("-------------------");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {

  // Button logic
  int currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == HIGH && lastButtonState == LOW) {
    useMetric = !useMetric;

    if (useMetric) {
      Serial.println("Metric (cm)");
    } else {
      Serial.println("English (inches)");
    }

    delay(200); // debounce
  }

  lastButtonState = currentButtonState;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH);

  // Convert
  float distanceCm = duration * 0.034 / 2;
  float distanceIn = distanceCm * 0.3937;

  // Output
  if (useMetric) {
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  } else {
    Serial.print("Distance: ");
    Serial.print(distanceIn);
    Serial.println(" in");
  }

  delay(500);
}
