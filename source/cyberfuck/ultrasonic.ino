#include "globals.h"


const int TRIG_PINS[] = {2, 4, 6, 8};
const int ECHO_PINS[] = {3, 5, 7, 9};
const int NUM_SENSORS = 0;

long duration[NUM_SENSORS];
int distance[NUM_SENSORS];

void ultrasonicSetup() {
  Serial.begin(9600);
  
  for(int i = 0; i < NUM_SENSORS; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
    digitalWrite(TRIG_PINS[i], LOW);
  }
  
  Serial.println("Ultrasonic Sensor System Initialized");
}

int measureDistance(int sensorIndex) {
  digitalWrite(TRIG_PINS[sensorIndex], LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PINS[sensorIndex], HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PINS[sensorIndex], LOW);
  
  duration[sensorIndex] = pulseIn(ECHO_PINS[sensorIndex], HIGH);
  
  return duration[sensorIndex] * 0.0343 / 2;
}

void ultrasonicLoop() {
  for(int i = 0; i < NUM_SENSORS; i++) {
    distance[i] = measureDistance(i);
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(distance[i]);
    Serial.println(" cm");
  }
  
  
  
  Serial.println("---------------");
}

