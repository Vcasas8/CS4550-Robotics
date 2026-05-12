// Analog input pin that the potentiometer is attached to
const int analogInPin = A3;

// PWM output pin that the LED is attached to
const int ledPin = 6;

int sensorValue = 0;   // value read from the potentiometer (0–1023)
int outputValue = 0;   // PWM value sent to the LED (0–255)

void setup() {
  // Initialize serial communications at 9600 bps
  Serial.begin(9600);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the analog value from the potentiometer
  sensorValue = analogRead(analogInPin);

  // Map the potentiometer range (0–1023) to PWM range (0–255)
  outputValue = map(sensorValue, 0, 1023, 0, 255);

  // Set LED brightness using PWM
  analogWrite(ledPin, outputValue);

  // Print values to Serial Monitor (for debugging)
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print("\t LED Brightness: ");
  Serial.println(outputValue);

  // Short delay for ADC stability
  delay(2);
}
