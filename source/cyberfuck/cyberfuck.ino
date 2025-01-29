// Main file
void setup() {
  Serial.begin(9600);
  setupUltrasonic();  // Call setup function from ultrasonic.ino
}


void loop() {
  long distance = readUltrasonicDistance();  // Call function from ultrasonic.ino
  Serial.println(distance);
  delay(1000);
}
