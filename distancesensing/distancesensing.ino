const int pingPin1 = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = 6; // Echo Pin of Ultrasonic Sensor

const int pingPin2 = 51; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 53; // Echo Pin of Ultrasonic Sensor
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter filter(2, 40, 0.01);

void setup() {
  Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
  long duration, inches, cm, duration2, inches2, cm2;
//  pinMode(pingPin, OUTPUT);
//  digitalWrite(pingPin, LOW);
//  pinMode(pingPin2, OUTPUT);
//  digitalWrite(pingPin2, LOW);
//
//
//  delayMicroseconds(2);
//  //  digitalWrite(pingPin, HIGH);
//  digitalWrite(pingPin2, HIGH);
//  delayMicroseconds(10);
//  //  digitalWrite(pingPin, LOW);
//  digitalWrite(pingPin2, LOW);
//  pinMode(echoPin, INPUT);
//  pinMode(echoPin2, INPUT);
    duration =calculateDuration(pingPin1, echoPin1);
  duration2 = calculateDuration(pingPin2, echoPin2);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);
    if (inches < 200 && inches2 < 200) {
      Serial.print("Sensor 1 :  ");
      Serial.print(inches);
      Serial.print("in, ");
      Serial.print(cm);
      Serial.print("cm");
  
     Serial.println();
  Serial.print("Sensor 2 :  ");
  Serial.print(inches2);
  Serial.print("in, ");
  Serial.print(cm2);
  Serial.print("cm");

  Serial.println();
  Serial.println();
  //        Serial.print("Estimate : ");
  //
  //    float estimate = filter.updateEstimate(inches);
  //  Serial.println(estimate);
      delay(1000);
}
}

long calculateDuration(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);;


}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
