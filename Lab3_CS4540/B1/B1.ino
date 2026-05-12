/*
B-1.  
Write a program that will light the red, green, 
and yellow LED's so that they act like a stop light.
Green on for a medium time - yellow on for a short time 
- red on for a medium time - repeat.
    *Optional*include the white LED as the walk' signal.
*/
const int ledRed = 9;
const int ledYellow = 11;
const int ledGreen = 13;


void setup() {
  // put your setup code here, to run once:
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledYellow, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // GREEN LED set to 3 seconds
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);

  delay(3000);

  // YELLOW LED set to 1 second
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledRed, LOW);

  delay(1000);
  
  // RED LED set to 3 seconds
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, HIGH);

  delay(3000);

  // Should repeat
  
}
