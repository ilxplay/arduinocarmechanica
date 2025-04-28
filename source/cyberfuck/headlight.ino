int ledPin = 11;  // LED connected to digital pin 10

void headlightloop() {
  int value = (analogRead(A1)) / 4;
  if (value < 99) {value = 0;}
  value = abs(value);
  analogWrite(ledPin, value);
}