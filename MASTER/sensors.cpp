#include "sensors.h"
#include <Arduino.h>

#define trigF 6
#define echF 2
#define trigB A4
#define echB A5
#define trigL A0
#define echL A1
#define trigR A2
#define echR A3

void initSensors() {
  pinMode(trigF, OUTPUT);
  pinMode(echF, INPUT);
  pinMode(trigB, OUTPUT);
  pinMode(echB, INPUT);
  pinMode(trigL, OUTPUT);
  pinMode(echL, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echR, INPUT);
}

long backSide() {
  long duration = 0;
  
  digitalWrite(trigB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB, LOW);

  duration = pulseIn(echB, HIGH);
  return duration / 58.2;
}

long frontSide() {
  long duration = 0;
  
  digitalWrite(trigF, LOW);
  delayMicroseconds(2);
  digitalWrite(trigF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigF, LOW);

  duration = pulseIn(echF, HIGH);
  return duration / 58.2;
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