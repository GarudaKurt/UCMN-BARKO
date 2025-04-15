#include <Arduino.h>
#include <SoftwareSerial.h>
#include "motorControl.h"
#include "sensors.h"
#include <Servo.h>

Servo fin;
Servo conveyors;
const int finPin = 11;
const int conveyorPin = 10;

void initServo() {
  conveyors.attach(conveyorPin);
  fin.attach(finPin);
}

void runConveyor() {
  conveyors.write(180);
  Serial.println("Conveyor is running");
}

void finMotor(int angle) {
  fin.write(angle);
  Serial.print("Fin motor: ");
  Serial.println(angle);
}
SoftwareSerial BTSerial(12, 13); // RX, TX

char command = 'X';
unsigned long lastCommandTime = 0;
unsigned long prevTime = 0;
const unsigned long commandTimeout = 3000;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);  // Match both HC-05 devices at same rate

  initServo();
  initMotors();
  initSensors();
  runConveyor();
  delay(100);
}

void loop() {
  runConveyor();
 // Receive Bluetooth command
  if (BTSerial.available()) {
    char incoming = BTSerial.read();

    if (incoming != '\n' && incoming != '\r' && incoming != 'H') {
      command = incoming;
      lastCommandTime = millis();

      Serial.print("Received: ");
      Serial.println(command);
    }
  }

  // Execute command if within timeout
  if (millis() - lastCommandTime < commandTimeout) {
    switch (command) {
      case 'F': runMotors(255); finMotor(90); break;
      case 'B': runMotors(150); finMotor(180); break;
      case 'L': runMotors(150); finMotor(30); break;
      case 'R': runMotors(150); finMotor(150); break;
      case 'S': runMotors(0); break;
      delay(5000);
      default: break;
    }
  } else {
    // Fallback to obstacle avoidance
    long l = leftSide();
    long r = rightSide();
    Serial.print("Left: "); Serial.print(l); Serial.print(" cm\t");
    Serial.print("Right: "); Serial.println(r);
    if (l < 20) {
      finMotor(30);
      runMotors(150);
      Serial.println("Pass in left side");
      delay(5000);
    } else if (r  < 20) {
      finMotor(150);
      runMotors(150);
      Serial.println("Pass in right side");
      delay(5000);
    } else {
      runMotors(255);
      finMotor(90);
    }

    // Optional: reset command if needed
    command = 'X';
  }
}
