int ledPin = 11;  // LED connected to digital pin 10

void headlightloop() {
  int value = (1023 - analogRead(A1)) / 4;
  if (value < 50) {value = 0;}
  value = abs(value);
  analogWrite(ledPin, value);
}