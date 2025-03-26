#ifndef GLOBALS_H
#define GLOBALS_H

// Sensor indices
const int SENSOR_BACK = 0;
const int SENSOR_FRONT = 1;
const int SENSOR_LEFT = 2;
const int SENSOR_RIGHT = 3;

// Ultrasonic
extern const int NUM_SENSORS = 4;
extern int distance[];

// Joystick
extern bool obstacleAvoidanceEnabled = false;
extern int dataX;
extern int dataY;

// Motor control constants
const int JOYSTICK_X = A8;
const int JOYSTICK_Y = A9;
const int JOYSTICK_BUTTON = 14;
const int JOYSTICK_DEADZONE = 100;
const int JOYSTICK_CENTER = 512;
const int MAX_SPEED = 255;
const int MIN_DISTANCE = 10; // minimum safe distance in cm
const int DESIRED_DISTANCE = 20; // preferred distance from obstacles in cm

// Autopilot parameters
const float K_SPEED = 10.0; // speed gain
const float K_STEER = 5.0;  // steering increase
const int FILTER_SIZE = 3;  // number of readings for moving average

// State states         -- "state states" lmao
enum AutopilotState {
  EXPLORING,
  AVOIDING_OBSTACLE,
  REVERSING,
  ESCAPING,
  STOPPED
};

#endif