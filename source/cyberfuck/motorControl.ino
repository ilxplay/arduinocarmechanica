
int in1=13; // IN1 connected to digital pin 13 
int in2=12; // IN2 connected to digital pin 12 
int in3=11; // IN3 connected to digital pin 11 
int in4=10; // IN4 connected to digital pin 10 

void motorSetup() { 
 pinMode(in1, OUTPUT); // Set IN1 as OUPUT 
 pinMode(in2, OUTPUT); // Set IN2 as OUPUT 
 pinMode(in3, OUTPUT); // Set IN3 as OUPUT 
 pinMode(in4, OUTPUT); // Set IN4 as OUPUT 
 
 digitalWrite(in1, HIGH); 
 digitalWrite(in2, HIGH); 
 digitalWrite(in3, HIGH); 
 digitalWrite(in4, HIGH); 
} 
void motorLoop() { 
 digitalWrite(in1, LOW); // Turn on motor A in direction 1 
 delay(2000); 
 digitalWrite(in1, HIGH); // Turn off motor A in direction 1 
 digitalWrite(in2, LOW); // Turn on motor A in direction 2 
 delay(2000); 
 digitalWrite(in2, HIGH); // Turn off motor A in direction 2 
 digitalWrite(in3, LOW); // Turn on motor B in direction 1 
 delay(2000); 
 digitalWrite(in3, HIGH); // Turn off motor B in direction 1 
 digitalWrite(in4, LOW); // Turn on motor B in direction 2 
 delay(2000); 
 digitalWrite(in4, HIGH); // Turn off motor B in direction 2 
 
}