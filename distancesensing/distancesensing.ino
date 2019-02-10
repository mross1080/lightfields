const int pingPin1 = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = 6; // Echo Pin of Ultrasonic Sensor

const int pingPin2 = 51; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 53; // Echo Pin of Ultrasonic Sensor
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter filter(2, 40, 0.01);

void setup() {
  Serial.begin(9600); // Starting Serial Terminal
}

int SHORT_DISTANCE_MAX = 25;
int MEDIUM_DISTANCE_MAX = 50;
int FAR_DISTANCE_MAX = 150;

// Calculate Range for close by
// Calculate Range for close by
int previousInchesValue1 = -999;
long distanceChangeTimer = millis();
boolean stateInFlux1 = false;
int occurencesOfNewValues = 0;
int possibleNewValue1 = -999;
long printTimer = millis();

void loop() {
  long currentMillis = millis();
  long duration, inches, cm, duration2, inches2, cm2;

  duration = calculateDuration(pingPin1, echoPin1);
  duration2 = calculateDuration(pingPin2, echoPin2);
  inches = microsecondsToInches(duration);
  // If we see a new value that is above the current accetable buffer and we're not currently in a checking state
  // then set a new timer
  if (abs(inches - previousInchesValue1) > 5 && !stateInFlux1) {
    Serial.print(" Detected a new value, checking to see if it comes again : " );
    Serial.println(inches);
    distanceChangeTimer = currentMillis;
    stateInFlux1 = true;
    possibleNewValue1 = inches;
  }


  // We've seen a new value so over the next 1000ms lets see if we see it again
  if (currentMillis - distanceChangeTimer < 2000) {
    if ( (abs(inches - previousInchesValue1)) > 5 ) {
      occurencesOfNewValues++;
//      Serial.println("Saw it again " );
      


    }
  } else if (stateInFlux1 && occurencesOfNewValues > 30) {
    // it's been over a second, either register the new value or reset the cycle
     Serial.println("Setting new value " );
     Serial.println(occurencesOfNewValues);
    previousInchesValue1 = possibleNewValue1;
    stateInFlux1 = false;
    occurencesOfNewValues =0;


  } else {
     stateInFlux1 = false;
    
    }


  inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);
  //  if (inches < 200 && inches2 < 200) {

  if (currentMillis - printTimer > 1000) {
  if (previousInchesValue1 <= SHORT_DISTANCE_MAX) {
    Serial.println("Sensor 1 Detected Movement :  Close by ");
    //      Serial.print(inches);

  } else if  (previousInchesValue1 >= SHORT_DISTANCE_MAX && previousInchesValue1 <= MEDIUM_DISTANCE_MAX ) {
    Serial.println("Sensor 1 Detected Movement :  Medium Distance ");



  } else if  (previousInchesValue1 >= MEDIUM_DISTANCE_MAX && previousInchesValue1 <= FAR_DISTANCE_MAX ) {
    Serial.println("Sensor 1 Detected Movement :  Far Distance ");



  } else {
    Serial.print("Current value  :  ");
    Serial.print(previousInchesValue1);
  }

//  Serial.println();
//  Serial.print("Actual Sensor 1 :  ");
//  Serial.print(inches);
//  Serial.print("in, ");
//   Serial.print("Smoothed Sensor 1 :  ");
//  Serial.print(previousInchesValue1);
//  Serial.print("in, ");
//
//     Serial.print("Occurences of diference :  ");
//  Serial.println(occurencesOfNewValues);
//  
//     Serial.print("state in flux?  :  ");
//  Serial.println(stateInFlux1);


  //    Serial.println();
  //    Serial.print("Sensor 2 :  ");
  //    Serial.print(inches2);
  //    Serial.print("in, ");


  Serial.println();
  Serial.println();
  printTimer = currentMillis;
  }
  //        Serial.print("Estimate : ");
  //
  //    float estimate = filter.updateEstimate(inches);
  //  Serial.println(estimate);
//  delay(1000);

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
