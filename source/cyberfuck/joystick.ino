#include <SPI.h>  //the communication interface


//define the data pins
int joyX = A8;
int joyY = A9;

//define variable values
int dataX;
int dataY;

int data[2];

void joystickSetup(void){
  Serial.begin(2400);
}

void joystickLoop(){

  dataX = analogRead(joyX);
  dataY = analogRead(joyY);
  
  data[0] = dataX;
  data[1] = dataY;

  Serial.print("Data X:"); Serial.println(dataX);
  Serial.print("Data Y:"); Serial.println(dataY);
  
  
}
