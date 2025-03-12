
void setup() {
  Serial.begin(9600);
  //buzzerSetup();
  //shockDetectionSetup();
  //lcdsetup();

  ultrasonicSetup();
  motorSetup();
  
}
void loop() {
  //shockDetectionLoop();
  if(buttonState == 1){
    ultrasonicLoop();
  }
  motorLoop();
  
}
