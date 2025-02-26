
void setup() {
  
  //buzzerSetup();
  //shockDetectionSetup();
  ultrasonicSetup();
  motorSetup();
  //lcdsetup();
  joystickSetup();
}
void loop() {
  ultrasonicLoop();
  //shockDetectionLoop();
  motorLoop();
  joystickLoop();
  
}
