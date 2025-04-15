#include "myservo.h"
#include <stddef.h>
#include <Servo.h>
#include <Arduino.h>

Servo fin;
Servo conveyors;
const int finPin = 11;
const int conveyorPin = 10;

void initServo() {
  conveyors.attach(conveyorPin);
  conveyors.write(180);
  fin.attach(finPin);
}

void conveyor() {
  conveyors.write(180);
}

void finMotor(int angle) {
  fin.write(angle);
}
