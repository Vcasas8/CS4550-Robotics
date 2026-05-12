void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("Brighten / Dim LED");
  Serial.println("-------------------");

  pinMode(4, OUTPUT);   // extra LED stays connected
  pinMode(6, OUTPUT);   // PWM LED used for brightness
  pinMode(10, INPUT);   // brighten switch
  pinMode(8, INPUT);    // dim switch
}

int brightness = 0;

void loop() {
  // brighten button
  if (digitalRead(10) == HIGH) {
    brightness += 26;
    if (brightness > 255) {
      brightness = 255;
    }

    analogWrite(6, brightness);

    Serial.print("Brightness: ");
    Serial.println(brightness);

    while (digitalRead(10) == HIGH) {
    }
    delay(50);
  }

  // dim button
  if (digitalRead(8) == HIGH) {
    brightness -= 26;
    if (brightness < 0) {
      brightness = 0;
    }

    analogWrite(6, brightness);

    Serial.print("Brightness: ");
    Serial.println(brightness);

    while (digitalRead(8) == HIGH) {
    }
    delay(50);
  }
}