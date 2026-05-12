/*
C-4. Here is an example of an ASCII art string. Save it to a string variable 
      and print it to the serial monitor terminal.
    Find one more example and print that as well. 
    (the tricky part is that the backslash "\" is seen as a control character. 
    It has to be used as a pair "\\" to print out a single backslash.  
    {https://www.asciiart.eu/animals/catsLinks to an external site.}
    Write a program that will randomly print this example and your found 
    (or created) ASCII art strings to the terminal, one print per second, 
    repeat 3 times.        

String catPic = "  ^~^  '\n (\'Y\') )\n /   \\/ \n(\\|||/)";

*/

void setup() {
  Serial.begin(9600);
  delay(500);              // give Serial Monitor time to connect
  randomSeed(analogRead(0));
}

String catPic =
  "  ^~^  '\n"
  " ('Y') )\n"
  " /   \\/ \n"
  "(\\|||/)\n";

String owlPic =
  "  /\\_/\\\n"
  " ( o o )\n"
  " /  V  \\\n"
  "/(  _  )\\\n";

void loop() {
  for (int i = 0; i < 3; i++) {
    int choice = random(0, 2);

    if (choice == 0) {
      Serial.print(catPic);
    } else {
      Serial.print(owlPic);
    }

    Serial.println();   // blank line between prints
    delay(1000);
  }

  while (true) {
  }
}