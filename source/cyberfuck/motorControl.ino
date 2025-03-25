#include "globals.h"


int in1 = 5;  // Motor A direction 1 (PWM)
int in2 = 6;  // Motor A direction 2 (PWM)
int in3 = 9;  // Motor B direction 1 (PWM)
int in4 = 10; // Motor B direction 2 (PWM)

unsigned long lastButtonDebounceTime = 0;
const long debounceDelay = 200;

extern bool obstacleAvoidanceEnabled = false;
float filteredDistance[NUM_SENSORS][FILTER_SIZE];
int filterIndex[NUM_SENSORS] = {0};

AutopilotState currentState = STOPPED;
unsigned long stateStartTime = 0;
int lastTurnDirection = 1; // 1 = right | -1 = left

void motorSetup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);

  for (int i = 0; i < NUM_SENSORS; i++) {
    for (int j = 0; j < FILTER_SIZE; j++) {
      filteredDistance[i][j] = 0;
    }
  }

  Serial.println("Motor and joystick setup complete");
}

void motorA(int speed) {
  if (speed > 0) { // forward
    digitalWrite(in1, LOW);
    analogWrite(in2, constrain(speed, 0, MAX_SPEED));
  } else if (speed < 0) { // backward
    digitalWrite(in2, LOW);
    analogWrite(in1, constrain(-speed, 0, MAX_SPEED));
  } else { // stop
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
  }
}

void motorB(int speed) {
  if (speed > 0) { // forward
    digitalWrite(in3, LOW);
    analogWrite(in4, constrain(speed, 0, MAX_SPEED));
  } else if (speed < 0) { // backward
    digitalWrite(in4, LOW);
    analogWrite(in3, constrain(-speed, 0, MAX_SPEED));
  } else { // stop
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  motorB(leftSpeed);  // left motor
  motorA(rightSpeed); // right motor
}

void handleJoystickControl() {
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);
  int xOffset = xValue - JOYSTICK_CENTER;
  int yOffset = yValue - JOYSTICK_CENTER;

  if (abs(xOffset) < JOYSTICK_DEADZONE && abs(yOffset) < JOYSTICK_DEADZONE) {
    setMotorSpeeds(0, 0);
    return;
  }

  int linearSpeed = map(yOffset, -512, 512, -MAX_SPEED, MAX_SPEED);
  int angularSpeed = map(xOffset, -512, 512, -MAX_SPEED, MAX_SPEED);
  int leftSpeed = linearSpeed - angularSpeed;
  int rightSpeed = linearSpeed + angularSpeed;

  leftSpeed = constrain(leftSpeed, -MAX_SPEED, MAX_SPEED);
  rightSpeed = constrain(rightSpeed, -MAX_SPEED, MAX_SPEED);
  setMotorSpeeds(leftSpeed, rightSpeed);

  Serial.print("Manual - Left: ");
  Serial.print(leftSpeed);
  Serial.print(", Right: ");
  Serial.println(rightSpeed);
}

void checkButtonPress() {
  int buttonState = digitalRead(JOYSTICK_BUTTON);
  if (buttonState == LOW) {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonDebounceTime > debounceDelay) {
      obstacleAvoidanceEnabled = !obstacleAvoidanceEnabled;
      Serial.print("Obstacle avoidance ");
      Serial.println(obstacleAvoidanceEnabled ? "ENABLED" : "DISABLED");
      if (!obstacleAvoidanceEnabled) {
        setMotorSpeeds(0, 0); // stop
        currentState = STOPPED;
      } else {
        currentState = EXPLORING;
      }
      lastButtonDebounceTime = currentTime;
    }
  }
}

float getFilteredDistance(int sensor) {
  // Update filter with latest reading
  int rawDistance = (distance[sensor] > 0) ? distance[sensor] : 1000;
  filteredDistance[sensor][filterIndex[sensor]] = rawDistance;
  filterIndex[sensor] = (filterIndex[sensor] + 1) % FILTER_SIZE;

  // Compute moving average
  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += filteredDistance[sensor][i];
  }
  return sum / FILTER_SIZE;
}

void autopilot() {
  // get filtered sensor readingss
  float front = getFilteredDistance(SENSOR_FRONT);
  float left = getFilteredDistance(SENSOR_LEFT);
  float right = getFilteredDistance(SENSOR_RIGHT);
  float back = getFilteredDistance(SENSOR_BACK);

  int speed = 0;
  float steering = 0;
  unsigned long currentTime = millis();

  switch (currentState) {
    case EXPLORING:
      if (front > MIN_DISTANCE) {
        speed = K_SPEED * (front - DESIRED_DISTANCE);
        speed = constrain(speed, 0, MAX_SPEED);
        steering = K_STEER * (left - right);
        if (front < DESIRED_DISTANCE || left < DESIRED_DISTANCE || right < DESIRED_DISTANCE) {
          currentState = AVOIDING_OBSTACLE;
          stateStartTime = currentTime;
        }
      } else {
        currentState = REVERSING;
        stateStartTime = currentTime;
      }
      break;

    case AVOIDING_OBSTACLE:
      speed = K_SPEED * (front - DESIRED_DISTANCE);
      speed = constrain(speed, 0, MAX_SPEED / 2); // slower
      steering = K_STEER * (left - right) * 1.5; // amplify/intensify steering
      if (front < MIN_DISTANCE) {
        currentState = REVERSING;
        stateStartTime = currentTime;
      } else if (front > DESIRED_DISTANCE * 2 && left > DESIRED_DISTANCE && right > DESIRED_DISTANCE) {
        currentState = EXPLORING;
      }
      break;

    case REVERSING:
      if (back > MIN_DISTANCE) {
        speed = -K_SPEED * (back - DESIRED_DISTANCE);
        speed = constrain(speed, -MAX_SPEED, 0);
        steering = K_STEER * (left - right);
        if (currentTime - stateStartTime > 2000) { // 2 seconds reversing
          currentState = ESCAPING;
          stateStartTime = currentTime;
          lastTurnDirection = (left > right) ? 1 : -1; // turns towards more space
        }
      } else {
        currentState = STOPPED;
      }
      break;

    case ESCAPING:
      speed = 0;
      steering = lastTurnDirection * MAX_SPEED; // turns in place
      if (currentTime - stateStartTime > 500) { // turns for 500 miliseconds
        currentState = (front > MIN_DISTANCE) ? EXPLORING : REVERSING;
        stateStartTime = currentTime;
      }
      break;

    case STOPPED:
      speed = 0;
      steering = 0;
      if (front > MIN_DISTANCE && back > MIN_DISTANCE) {
        currentState = EXPLORING;
      }
      break;
  }

  int leftSpeed = speed + steering;
  int rightSpeed = speed - steering;
  leftSpeed = constrain(leftSpeed, -MAX_SPEED, MAX_SPEED);
  rightSpeed = constrain(rightSpeed, -MAX_SPEED, MAX_SPEED);
  setMotorSpeeds(leftSpeed, rightSpeed);

  // debugging output
  Serial.print("State: ");
  Serial.print(currentState);
  Serial.print(", Speed: ");
  Serial.print(speed);
  Serial.print(", Steering: ");
  Serial.print(steering);
  Serial.print(", Left: ");
  Serial.print(leftSpeed);
  Serial.print(", Right: ");
  Serial.println(rightSpeed);
}

void motorLoop() {
  Serial.println("\nCurrent sensor readings:");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(distance[i]);
    Serial.println("cm");
  }

  checkButtonPress();
  if (obstacleAvoidanceEnabled) {
    autopilot();
  } else {
    handleJoystickControl();
  }
}