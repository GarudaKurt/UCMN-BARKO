#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

// Joystick analog pins
const int joyX = A0;
const int joyY = A1;

char lastCommand = 'X';

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  Serial.println("Joystick controller ready.");
}

void loop() {
  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);
  char command = 'H'; // Default is Stop

  // Determine direction
  if (yVal < 512 - threshold) {
    command = 'L'; // Forward 
  } else if (yVal > 512 + threshold) {
    command = 'R'; // Backward
  } else if (xVal < 512 - threshold) {
    command = 'B'; // Left
  } else if (xVal > 512 + threshold) {
    command = 'T'; // Right
  } else {
    command = 'H';
  }

  // Only send command if it changed
  if (command != lastCommand) {
    BTSerial.println(command);
    Serial.print("Sent: ");
    Serial.println(command);
    lastCommand = command;
  }

  delay(200);
}
