#include "globals.h"

void setup() {
  Serial.begin(9600);
  //buzzerSetup();
  //shockDetectionSetup();
  //lcdSetup();
  ultrasonicSetup();
  motorSetup();
  handleJoystickControl();
  matrixSetup();
  soundSetup();
}
void loop() {
  //shockDetectionLoop();
  //matrixLoop();
  if(obstacleAvoidanceEnabled == true){
    ultrasonicLoop();
  }
  motorLoop();
  lcdLoop();
  headlightloop();
  soundLoop();
}
