#include "sensors.h"
#include <Arduino.h>

#define trigR 6
#define echR 2
#define trigL A0
#define echL A1

void initSensors() {


  pinMode(trigL, OUTPUT);
  pinMode(echL, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echR, INPUT);
}

long rightSide() {
  long duration = 0;
  
  digitalWrite(trigR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);

  duration = pulseIn(echR, HIGH);
  return duration / 58.2;
}

long leftSide() {
  long duration = 0;
  
  digitalWrite(trigL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);

  duration = pulseIn(echL, HIGH);
  return duration / 58.2;
}