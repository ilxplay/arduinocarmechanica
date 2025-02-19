#include "globals.h"

int in1 = 13; // IN1 connected to digital pin 13 
int in2 = 12; // IN2 connected to digital pin 12 
int in3 = 11; // IN3 connected to digital pin 11 
int in4 = 10; // IN4 connected to digital pin 10 

const int OBSTACLE_THRESHOLD = 10; // Distance threshold in cm

void motorSetup() { 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
  
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, HIGH); 
} 

void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(in1, LOW);  // Motor A forward
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  // Motor B forward
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  Serial.println("Stopping Motors");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(in1, LOW);   // Motor A forward
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);  // Motor B backward
  digitalWrite(in4, LOW);
}

bool isObstacleDetected() {
  for(int i = 0; i < NUM_SENSORS; i++) {
    if(distance[i] < OBSTACLE_THRESHOLD && distance[i] > 0) {
      return true;
    }
  }
  return false;
}

void motorLoop() {
  // Print all sensor distances
  Serial.println("\nCurrent sensor readings:");
  for(int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(distance[i]);
    Serial.println("cm");
  }

  // Print current motor states
  Serial.print("Motor pins state - IN1: ");
  Serial.print(digitalRead(in1));
  Serial.print(" IN2: ");
  Serial.print(digitalRead(in2));
  Serial.print(" IN3: ");
  Serial.print(digitalRead(in3));
  Serial.print(" IN4: ");
  Serial.println(digitalRead(in4));

  if(isObstacleDetected()) {
    Serial.println("Obstacle detected! Stopping and turning...");
    stopMotors();
    delay(50);  // Brief pause
    turnRight();
    delay(1000); // Turn for 1 second
  } else {
    moveForward();
    delay(50);
  }
  
  delay(100); // Short delay to make the debug output readable
}