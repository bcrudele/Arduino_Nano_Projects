// These constants won't change. They're used to give names to the pins used:
const int in1 = 2; // A+
const int in2 = 3; // A-
const int in3 = 4; // B+
const int in4 = 5; // B-
const int pbRead = A2; // pot

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pbRead, INPUT);
}

int temp = 0;

void loop() {
  int pbRead_b = digitalRead(pbRead);
  //  //Serial.println(potRead);
  // unsigned int time = (((float)potRead / 1023) * 1000) + 1;
  switch(temp)
  {
    case 0:
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      break;

    case 1:
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
 
      break;

    case 2:
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      //Serial.println("Case 2");
      break;

    case 3:
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      //Serial.println("Case 3");
      break;
  }
  Serial.println(pbRead_b);
  if (pbRead_b) {
    if (temp == 3) temp = 0; 
    else temp++;
  }
  else {
    if (temp == 0) temp = 3;
    else temp--;
  }
  delay(10);
}