
void setup() {
  Serial.begin(9600); 
  //buzzerSetup();
  //shockDetectionSetup();
  //ultrasonicSetup();
  motorSetup();
}
void loop() {
  //ultrasonicLoop();
  //shockDetectionLoop();
  motorLoop();
}
