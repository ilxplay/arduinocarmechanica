
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
  if(buttonState.handleJoystickControl() == 1){
    ultrasonicLoop();
  }
  motorLoop();
  
}
