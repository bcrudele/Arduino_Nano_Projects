// These constants won't change. They're used to give names to the pins used:
const int in1Pin = 3;
const int in2Pin = 5;
const int potPin = A2;

void setup() {
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  int potRead = analogRead(potPin);
  
  potRead = map(potRead, 0, 1023, 0, 255);
  Serial.println(potRead);
  if (potRead >= 127) {
    analogWrite(in1Pin, (potRead-127)*2);
    analogWrite(in2Pin, 0);
  }
  else {
    analogWrite(in2Pin, (127-potRead)*2);
    analogWrite(in1Pin, 0);
  }
  delay(100);
}
