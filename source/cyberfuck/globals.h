#ifndef GLOBALS_H
#define GLOBALS_H


// sensor 0 back
// sensor 1 forward
// sensor 2 left
// sensor 3 right

const int SENSOR_BACK = 0;
const int SENSOR_FRONT = 1;
const int SENSOR_LEFT = 2;
const int SENSOR_RIGHT = 3;

//ultrasonic
extern const int NUM_SENSORS;
extern int distance[];

//joystick
extern int dataX;
extern int dataY;
#endif