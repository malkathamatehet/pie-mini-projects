// Take in sensor input and command motors to follow a tape line on the floor
// Can change car base speed and turn speed throught the serial monitor

//Include libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Pin setup
const int leftSensorPin = A1;  // Phototransistor output
const int centerSensorPin = A2;
const int rightSensorPin = A3;

// Set thresholds
const int leftThreshold = 790;
const int centerThreshold = 875;
const int rightThreshold = 260;

// Initialize sensor on/off variable
boolean leftSensor;
boolean centerSensor;
boolean rightSensor;

// Motor setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *left = AFMS.getMotor(1);
Adafruit_DCMotor *right = AFMS.getMotor(2);

int motorBaseSpeed = 20;
int motorTurnSpeed = 40;


void setup() {
  pinMode(leftSensorPin, INPUT);   // Set sensor pins as input
  pinMode(centerSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);

  AFMS.begin(); //start motors and set initial speed
  left->setSpeed(motorBaseSpeed);
  right->setSpeed(motorBaseSpeed);

  Serial.begin(9600);          // Initialize serial communication for debugging
}

void loop() {
  bool leftRead = readSensor(leftSensorPin, leftThreshold);
  bool rightRead = readSensor(rightSensorPin, rightThreshold);

  // Serial.print(leftRead);
  // Serial.print(" ");
  // Serial.println(rightRead);

  motorControl(leftRead, rightRead);

  listenForSpeedChange();

  // Serial.println(motorBaseSpeed);
  // Serial.println(motorTurnSpeed);
  
}

bool readSensor(int sensorPin, int threshold){
  bool reading;

  int sensorVal = analogRead(sensorPin);
  
  if (sensorVal <= threshold){
    reading = false;
  }
  else{
    reading = true;
  }

  return reading;
}


void motorControl(bool leftSense, bool rightSense){
  if (!leftSense && !rightSense){
    left->setSpeed(motorBaseSpeed); //same!
    right->setSpeed(motorBaseSpeed);
  }
  else if (leftSense){
    left->setSpeed(0);
    right->setSpeed(motorTurnSpeed);
  }
  else if(rightSense){
    left->setSpeed(motorTurnSpeed);
    right->setSpeed(0);
  }
  // else {
  //   left->setSpeed(0);
  //   right->setSpeed(0);
  // }

  left->run(BACKWARD);
  right->run(BACKWARD);

}

void listenForSpeedChange(){

  if (Serial.available() > 0) {
    // Read input from the serial port
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any leading/trailing whitespace

    int speed = input.substring(13).toInt(); // Get value after "setSpeed "

    // Parse the input string and set motor speeds
    if (input.startsWith("setBaseSpeed ")) {

      // set motor base speed to given speed
      motorBaseSpeed = speed;

      Serial.print("Motor base speed updated to: ");
      Serial.println(speed);
    }

    if (input.startsWith("setTurnSpeed ")) {

      // set motor turn speed to given speed
      motorTurnSpeed = speed;

      Serial.print("Motor turn speed updated to: ");
      Serial.println(speed);
    } 
  }

}
