#include <Servo.h>
// These constants won't change. They're used to give names to the pins used:
const int potPin = A2;
Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  myservo.attach(3);  // attaches the servo on pin 9 to the Servo object
  myservo.write(0);
}

void loop() {
  int potRead = analogRead(potPin);
  
  potRead = map(potRead, 0, 1023, 0, 180);
  myservo.write(potRead);
  Serial.println(potRead);
  delay(10);
}