#include "globals.h"

void setup() {
  Serial.begin(9600);
  //buzzerSetup();
  //shockDetectionSetup();
  //lcdsetup();

  ultrasonicSetup();
  motorSetup();
  handleJoystickControl();
  
}
void loop() {
  //shockDetectionLoop();
  if(obstacleAvoidanceEnabled == true){
    ultrasonicLoop();
  }
  motorLoop();
}
