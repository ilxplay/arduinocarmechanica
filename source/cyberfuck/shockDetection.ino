const int shockMeter = A1;
int sensorState = 0;

void shockDetectionSetup(){
  pinMode(shockMeter, INPUT);
  buzzerSetup();
}

void shockDetectionLoop(){
  sensorState = analogRead(shockMeter);
  Serial.println(sensorState);
  if (sensorState >= 1){
    buzzerLoop();
  }
}