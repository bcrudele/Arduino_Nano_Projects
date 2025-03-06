#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pinout: (reference README)
const int modeSelectPin = 2; // Mode Select Pin for Push Button
const int continuityPin = 6; // connect one probe to D6 and the other to GND to test for continuity
const int buzzer = 12;       // output to continuity test, can be replaced with an LED
const int VCCreadPin = 14;   // A0 reads the analog voltage on the VCC rail
const int ohmmeterPin = 15;  // A1 reads the analog voltage after the voltage drop of the known resistor and before the unknown resistor.

// important for Ohmmeter:
const int ohmmeter_resistor = 1000;   // 1k Ohm known resistor; in a real DMM, this value switches between the ranges. ie. 100ohm, 1k ohm, 10k ohm, 100k ohm, 1m ohm, etc...
const int ammeter_resistor = 47;

// initial states:
int pressed = LOW;
int state = 0;       // 0-> DMM OFF, 1->voltmeter, 2-> Ammeter, 3->ohmmeter, 4->continuity
int sensorValue = 0; // reads analog value
float voltage = 0;
float ohms = 0;

// for debouncing:
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200; 

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  //Serial.begin(9600);
  //Serial.print("Click button to select DMM mode\n");

  // LCD Setup:
  lcd.begin(16,2);
  lcd.backlight();

  // Pinout:
  pinMode(modeSelectPin, INPUT);
  pinMode(VCCreadPin, INPUT);
  pinMode(ohmmeterPin, INPUT);
  pinMode(continuityPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  // LCD initial print:
  lcd.setCursor(0,0);
  lcd.print("Hit Button");
  lcd.setCursor(0,1);
  lcd.print("to Select Mode");
}

void loop() {

  pressed = digitalRead(modeSelectPin);
  
  // If the switch changed, due to noise or pressing:
  if (pressed == HIGH) {

    if ((millis() - lastDebounceTime) > debounceDelay) { // compare last change with current request

      // state machine
      if (state != 4) {
        state++;
      }
      else {
        state = 1;
      }

      lastDebounceTime = millis(); // record last change
      lcd.clear();
      // switch (state) {
      //   case 1: Serial.print("Voltmeter Mode\n"); break;
      //   case 2: Serial.print("Ammeter Mode\n"); break;
      //   case 3: Serial.print("Ohmmeter Mode\n"); break;
      //   case 4: Serial.print("Continuity Mode\n"); break;
      // }
      switch (state) {
        case 1: lcd.setCursor(0,0); lcd.print("Voltmeter Mode"); break;
        case 2: lcd.setCursor(0,0); lcd.print("Ammeter Mode"); break;
        case 3: lcd.setCursor(0,0); lcd.print("Ohmmeter Mode"); break;
        case 4: lcd.setCursor(0,0); lcd.print("Continuity Mode"); break;
      }
    }
  }
  
  switch (state) {
    case 1: 
      sensorValue = analogRead(VCCreadPin);
      voltage = sensorValue * (5.0 / 1023.0);
      // Serial.print(voltage, 2);
      // Serial.println(" V");
      lcd.setCursor(0,1);
      lcd.print(voltage,2);
      delay(100);
      break;
    case 2:
      sensorValue = analogRead(VCCreadPin);
      voltage = sensorValue * (5.0 / 1023.0);
      // Serial.print(voltage/ammeter_resistor, 2);
      // Serial.println(" Amps");
      lcd.setCursor(0,1);
      lcd.print(voltage/ammeter_resistor,2);
      delay(100);
      break;
    case 3:
      sensorValue = analogRead(ohmmeterPin);
      voltage = sensorValue * (5.0 / 1023.0);
      ohms = voltage/(((analogRead(VCCreadPin) * (5.0 / 1023.0)) - voltage)/ohmmeter_resistor);
      // Serial.print(ohms, 2);
      // Serial.println(" Ohms");
      lcd.setCursor(0,1);
      lcd.print(ohms);
      delay(100);
      break;
    case 4:
      int continuity = digitalRead(continuityPin);
      if (continuity == LOW) {  
          digitalWrite(buzzer, HIGH); // Turn buzzer ON
          lcd.setCursor(0,1);
          lcd.print("!!CONDUCTIVE!!");
      } 
      else {
          digitalWrite(buzzer, LOW); // Turn buzzer OFF
          lcd.setCursor(0,1);
          lcd.print("..............");
      }
      delay(100);
      break;
  }
}