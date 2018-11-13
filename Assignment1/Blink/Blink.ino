/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  This example code is in the public domain.
 */
int led = 13;
void setup() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(led, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
