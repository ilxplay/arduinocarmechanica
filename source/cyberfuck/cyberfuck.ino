#include "globals.h"

void setup() {
  Serial.begin(9600);
  //buzzerSetup();
  //shockDetectionSetup();
  //lcdsetup();
  //matrixSetup();
  ultrasonicSetup();
  motorSetup();
  handleJoystickControl();
  lcdSetup();
}
void loop() {
  //shockDetectionLoop();
  //matrixLoop();
  if(obstacleAvoidanceEnabled == true){
    ultrasonicLoop();
  }
  motorLoop();
  lcdLoop();
}
