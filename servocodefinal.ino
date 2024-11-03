//Need to use the servo library 
#include <Servo.h>

//Setting up servos
Servo servoPan;
Servo servoTilt;

//Setting pin numbers for both servos and sensor 
const int panPin = 9; 
const int tiltPin = 10; 
const int sensorPin = 0;

//Setting initial and final angles for tilt and pan
const int tiltIn = 69; 
const int panIn = 73; 
const int tiltEnd = 102; 
const int panEnd = 107; 

//Initializing variable to stop mechanism - will get set to true when the scan is completed
bool done = false; 

//Declaring variable for the distance read by sensor
int dist;

void setup() {
  //Attaching servos to the correct pins
  servoPan.attach(panPin);
  servoTilt.attach(tiltPin);

  //Setting the servos to initial angles
  servoPan.write(panIn);
  servoTilt.write(tiltIn);

  //Setting the sensor to be an input
  pinMode(sensorPin, INPUT);

  //Starting serial communication
  Serial.begin(9600);

}

void loop() {
  //Delays start in order to be able to run MATLAB script
  delay(8000);

  //Checks if done is false - if not, skips to end of loop
  if (!done){
    //Loops through all tilt angles
    for (int i = tiltIn; i < tiltEnd; i++){
      //Loops through all pan angles
      for (int j = panIn; j < panEnd; j++){
        //Pans 1 degree and transmits data
        pan(j);
        transmit(i, j);
      }
      //Tilts 1 degree every time the pan is completed
      tilt(i);
    }
    //Once scan is complete, set done to true so it doesn't repeat
    done = true;
  }

}

//Function to pan the servo - takes in angle and writes it to the servo
void pan(int panAngle){
  servoPan.write(panAngle);
  delay(100);
}

//Function to tilt the servo - takes in angle and writes it to the servo
void tilt(int tiltAngle){
  servoTilt.write(tiltAngle);
  delay(100);
}

//Function to transmit information to MATLAB via serial communication
void transmit(int tiltAngle, int panAngle){
  
  //Finds sensor reading
  dist = analogRead(sensorPin);
  
  //Transmits sensor reading and both servo angles, separated by commas for easy splitting later
  Serial.print(dist);
  Serial.print(",");
  Serial.print(tiltAngle);
  Serial.print(",");
  Serial.println(panAngle);
}



