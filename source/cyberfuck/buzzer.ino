const int buzzer = 9; 


void buzzerSetup(){
  pinMode(buzzer, OUTPUT);
}

void buzzerLoop(){
 
  tone(buzzer, 40000);
  delay(100);
  noTone(buzzer);
  delay(100);
  
}