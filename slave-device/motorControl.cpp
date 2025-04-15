#include "motorControl.h"
#include <Arduino.h>
#include <Wire.h>

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

void initMotors() {
  Wire.begin();
  pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
  
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

void runMotors(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}
