#include <SPI.h>  //the communication interface with the modem


//define the data pins
int joyX = A8;
int joyY = A9;

//define variable values
int dataX;
int dataY;

int data[2];


void joystickSetup(void){
  Serial.begin(1200);
  radio.begin();                      //it activates the modem
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data
}

void joystickLoop(){

  dataX = analogRead(joyX);
  dataY = analogRead(joyY);
  
  data[0] = dataX;
  data[1] = dataY;

  Serial.print("Data X:"); Serial.println(dataX);
  Serial.print("Data Y:"); Serial.println(dataY);
  radio.write(data, sizeof(data));
  
}
