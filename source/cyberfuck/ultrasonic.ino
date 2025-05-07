#include "globals.h"


const int TRIG_PINS[] = {2, 4, 6, 8};
const int ECHO_PINS[] = {3, 5, 7, 9};
const int BUZZER_PIN = 30;
const int DISTANCE_THRESHOLD = 20;
const int BUZZER_DURATION = 1000;  

long duration[NUM_SENSORS];
int distance[NUM_SENSORS];
unsigned long buzzerStartTime = 0;
bool buzzerActive = false;

void ultrasonicSetup() {
  Serial.begin(9600);
  
  for(int i = 0; i < NUM_SENSORS; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
    digitalWrite(TRIG_PINS[i], LOW);
  }

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Ultrasonic Sensor System and advanced Buzzer Alert Distance Control System Initialized");
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
  bool thresholdReached = false;

  for(int i = 0; i < NUM_SENSORS; i++) {
    distance[i] = measureDistance(i);
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(distance[i]);
    Serial.println(" cm");

    if (distance[i] < DISTANCE_THRESHOLD && distance[i] > 0) {
      thresholdReached = true;
    }
  }


   if (thresholdReached && !buzzerActive) {

    digitalWrite(BUZZER_PIN, HIGH);
    buzzerActive = true;
    buzzerStartTime = millis();
    Serial.println("Threshold reached! Buzzer ON");

    } 
    else if (buzzerActive && (millis() - buzzerStartTime >= BUZZER_DURATION)) {
      digitalWrite(BUZZER_PIN, LOW);
      buzzerActive = false;
      Serial.println("Buzzer OFF");

    }
   Serial.println("---------------");
   delay(50);
}

