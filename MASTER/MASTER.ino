#include <Arduino.h>
#include <SoftwareSerial.h>
#include "motorControl.h"
#include "sensors.h"
#include "myservo.h"

SoftwareSerial BTSerial(12, 13); // RX, TX

char command = 'X';

unsigned long lastCommandTime = 0;
const unsigned long commandTimeout = 3000;
void setup() {
	Serial.begin(9600);
  BTSerial.begin(9600);    // Default AT mode baud rate

	initServo();
	initMotors();
	initSensors();
	conveyor();
	delay(100);
}

void loop() {

	 if (BTSerial.available()) {
    command =  BTSerial.read();
    command.trim();
    lastCommandTime = millis();
  }

	if (millis() - lastCommandTime < commandTimeout) {
    switch (command) {
      case 'F': runMotors(255); finMotor(90); break;
      case 'B': runMotors(150); finMotor(180); break;
      case 'L': runMotors(150); finMotor(30); break;
      case 'R': runMotors(150); finMotor(150); break;
      case 'S': runMotors(0); break;
      Serial.print("Received: ");
      Serial.println(command);
    }
  } else {
		long f = frontSide();
		long b = backSide();
		long l = leftSide();
		long r = rightSide();

		Serial.print("Front: "); Serial.print(f); Serial.print(" cm\t");
		Serial.print("Back: "); Serial.print(b); Serial.print(" cm\t");
		Serial.print("Left: "); Serial.print(l); Serial.print(" cm\t");
		Serial.print("Right: "); Serial.println(r);

		if(f < 20) {
			runMotors(150);
			finMotor(120);
			Serial.println("Pass in front side");
		} else if(b < 20) {
			runMotors(50);
			Serial.println("Pass in back side");
		} else if(l < 20) {
			finMotor(30);
			runMotors(150);
			Serial.println("Pass in left side");
		} else if(r < 20) {
			finMotor(150);
			runMotors(150);
			Serial.println("Pass in right side");
		} else {
			runMotors(255);
			finMotor(90);
		}
	}

  delay(300);
}
