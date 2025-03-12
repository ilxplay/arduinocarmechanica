#include "globals.h"

int in1 = 13; // IN1 connected to digital pin 13 
int in2 = 12; // IN2 connected to digital pin 12 
int in3 = 11; // IN3 connected to digital pin 11 
int in4 = 10; // IN4 connected to digital pin 10 

const int JOYSTICK_X = A8;  // X-axis analog pin
const int JOYSTICK_Y = A9;  // Y-axis analog pin
const int JOYSTICK_BUTTON = 2;  // Optional button pin

const int JOYSTICK_DEADZONE = 100;
const int JOYSTICK_CENTER = 512; 
const int OBSTACLE_THRESHOLD = 8; 
const bool OBSTACLE_AVOIDANCE_ENABLED = false; 

void motorSetup() { 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
  
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, HIGH); 
  
  // Setup joystick pins
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);  // Using internal pullup resistor
  
  Serial.println("Motor and joystick setup complete");
}

void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(in1, LOW);  // Motor A forward
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  // Motor B forward
  digitalWrite(in4, HIGH);
}

void moveBackward() {
  Serial.println("Moving Backward");
  digitalWrite(in1, HIGH);  // Motor A backward
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  // Motor B backward
  digitalWrite(in4, LOW);
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(in2, LOW);   // Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);  // Motor B backward
  digitalWrite(in3, LOW);
}

void turnLeft() {
  Serial.println("Turning Left");
  digitalWrite(in2, HIGH);  // Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in4, LOW);   // Motor B forward
  digitalWrite(in3, HIGH);
}

void stopMotors() {
  Serial.println("Stopping Motors");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void moveRightForward() {
  Serial.println("Moving Right-Forward");
  digitalWrite(in1, LOW);   // Motor A forward (full speed)
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);   // Motor B forward (reduced speed - implemented via PWM in advanced version)
  digitalWrite(in4, HIGH);
}

void moveLeftForward() {
  Serial.println("Moving Left-Forward");
  digitalWrite(in1, LOW);   // Motor A forward (reduced speed - implemented via PWM in advanced version)
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);   // Motor B forward (full speed)
  digitalWrite(in4, HIGH);
}

bool isObstacleDetected() {
  for(int i = 0; i < NUM_SENSORS; i++) {
    if(distance[i] < OBSTACLE_THRESHOLD && distance[i] > 0) {
      return true;
    }
  }
  return false;
}

void handleJoystickControl() {
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);
  int buttonState = digitalRead(JOYSTICK_BUTTON);
  
  int xOffset = xValue - JOYSTICK_CENTER;
  int yOffset = yValue - JOYSTICK_CENTER;
  
  /*
  Serial.print("Joystick X: ");
  Serial.print(xValue);
  Serial.print(" (");
  Serial.print(xOffset);
  Serial.print("), Y: ");
  Serial.print(yValue);
  Serial.print(" (");
  Serial.print(yOffset);
  Serial.print("), Button: ");
  Serial.println(buttonState);
  */
  
  if (abs(xOffset) < JOYSTICK_DEADZONE && abs(yOffset) < JOYSTICK_DEADZONE) {
    stopMotors();
    return;
  }
  
 
  if (abs(yOffset) > abs(xOffset)) {
    if (yOffset < 0) {
      moveForward();
    } else {
      moveBackward();
    }
  } else {
    if (xOffset > 0) {
      turnRight();
    } else {
      turnLeft();
    }
  }
  
}

void motorLoop() {
  Serial.println("\nCurrent sensor readings:");
  for(int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(distance[i]);
    Serial.println("cm");
  }

  handleJoystickControl();

  if (OBSTACLE_AVOIDANCE_ENABLED && isObstacleDetected()) {
    Serial.println("Obstacle detected! Stopping and turning...");
    stopMotors();
    delay(50);
    turnRight();
    delay(1000);
  } else {
    
  }
  
  delay(10);
}

