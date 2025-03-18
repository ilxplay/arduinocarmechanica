#include "globals.h"

int in1 = 13; // IN1 connected to digital pin 13 
int in2 = 12; // IN2 connected to digital pin 12 
int in3 = 11; // IN3 connected to digital pin 11 
int in4 = 10; // IN4 connected to digital pin 10 

const int JOYSTICK_X = A8;  // X-axis analog pin
const int JOYSTICK_Y = A9;  // Y-axis analog pin
const int JOYSTICK_BUTTON = 9;  // Optional button pin

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
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
  
  Serial.println("Motor and joystick setup complete");
}

void motorA(int speed) {
  if (speed < 0) {
    speed = abs(speed);
    analogWrite(in1, speed);
  }
  else if (speed == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  else if (speed > 0) {
    analogWrite(in2, speed);
  }
}

void motorB(int speed) {
  if (speed < 0) {
    speed = abs(speed);
    analogWrite(in3, speed);
  }
  else if (speed == 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else if (speed > 0) {
    analogWrite(in4, speed);
  }
}

void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(in1, LOW);  // Motor A(rechts) backwards
  digitalWrite(in2, HIGH); // Motor A(rechts) forward
  digitalWrite(in3, LOW);  // Motor B(links) backwards
  digitalWrite(in4, HIGH); // Motor B(links) forwards
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


void autopilot() {
  if (!OBSTACLE_AVOIDANCE_ENABLED) return;
  
  bool frontBlocked = (distance[SENSOR_FRONT] < OBSTACLE_THRESHOLD && distance[SENSOR_FRONT] > 0);
  bool leftBlocked = (distance[SENSOR_LEFT] < OBSTACLE_THRESHOLD && distance[SENSOR_LEFT] > 0);
  bool rightBlocked = (distance[SENSOR_RIGHT] < OBSTACLE_THRESHOLD && distance[SENSOR_RIGHT] > 0);
  bool backBlocked = (distance[SENSOR_BACK] < OBSTACLE_THRESHOLD && distance[SENSOR_BACK] > 0);
  
  /*
  Serial.println("Autopilot Status:");
  Serial.print("Front: "); Serial.print(frontBlocked ? "BLOCKED" : "CLEAR");
  Serial.print(" ("); Serial.print(distance[SENSOR_FRONT]); Serial.println("cm)");
  Serial.print("Left: "); Serial.print(leftBlocked ? "BLOCKED" : "CLEAR");
  Serial.print(" ("); Serial.print(distance[SENSOR_LEFT]); Serial.println("cm)");
  Serial.print("Right: "); Serial.print(rightBlocked ? "BLOCKED" : "CLEAR");
  Serial.print(" ("); Serial.print(distance[SENSOR_RIGHT]); Serial.println("cm)");
  Serial.print("Back: "); Serial.print(backBlocked ? "BLOCKED" : "CLEAR");
  Serial.print(" ("); Serial.print(distance[SENSOR_BACK]); Serial.println("cm)");
  */


  if (!frontBlocked && !leftBlocked && !rightBlocked) {
    moveForward();
    return;
  }
  
  if (frontBlocked) {
    if (!leftBlocked && !rightBlocked) {
      if (distance[SENSOR_LEFT] > distance[SENSOR_RIGHT]) {
        Serial.println("Front blocked, turning left (more space)");
        turnLeft();
      } else {
        Serial.println("Front blocked, turning right (more space)");
        turnRight();
      }
    } else if (!leftBlocked) {
      Serial.println("Front blocked, right blocked, turning left");
      turnLeft();
    } else if (!rightBlocked) {
      Serial.println("Front blocked, left blocked, turning right");
      turnRight();
    } else if (!backBlocked) {
      Serial.println("Front, left, and right blocked, moving backward");
      moveBackward();
    } else {
      Serial.println("All directions blocked, stopping");
      stopMotors();
    }
    return;
  }
  
  if (leftBlocked && !rightBlocked) {
    Serial.println("Left blocked, moving right-forward");
    moveRightForward();
  } else if (rightBlocked && !leftBlocked) {
    Serial.println("Right blocked, moving left-forward");
    moveLeftForward();
  } else {
    Serial.println("Sides blocked, moving forward carefully");
    moveForward();
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

  if (OBSTACLE_AVOIDANCE_ENABLED) {
    autopilot();
  } else {
    handleJoystickControl();
  }
  
  delay(10);
}

