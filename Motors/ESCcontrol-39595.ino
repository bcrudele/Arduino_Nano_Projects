# include <Servo.h>

Servo ESC;                                  // declare ESC

const int potPin = A2;
const int escPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(escPin, OUTPUT);
  ESC.attach(escPin);                           // attach ESC input to pin 6 (PWM)
  //ESC.write(180);                           // initialize ESC
  //delay(100);
  //ESC.write(0);                           // initialize ESC
}

void loop() {
  // put your main code here, to run repeatedly:
  int potRead = analogRead(potPin);
  potRead = (float)potRead / 1023 * 125 + 45;
  Serial.println(potRead);
  ESC.write(potRead);
  delay(10);
}