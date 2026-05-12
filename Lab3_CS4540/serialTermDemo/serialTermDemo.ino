/*
C-1.  Make an Arduino sketch named serialTermDemo.ino using this code:
C-2. Run the code and screenshot the output.
*/

void setup() {
   // initialize both serial ports:
   Serial.begin(9600);
   Serial.print("-------------------\n");
   Serial.print("Hello Arduino Land");
   Serial.print("-------------------\n");
   pinMode(LED_BUILTIN, OUTPUT);
}

int count = 0;
int ledState = HIGH;
String countString = String(count);

void loop() {
   if(ledState == HIGH) {
      ledState = LOW;
   } else {
      ledState = HIGH;
   }

   digitalWrite(LED_BUILTIN, ledState);
   digitalWrite(LED_BUILTIN, ledState);

   Serial.println(count);
   count ++;
   delay(500);
}