// Code for visualizing sensor input and motor command output in serial plotter

// Pin setup
const int leftSensorPin = A1;  // Phototransistor output
// const int centerSensorPin = A2;
const int rightSensorPin = A3;

// Set thresholds
const int leftThreshold = 790;
// const int centerThreshold = 875;
const int rightThreshold = 260;

// Initialize sensor on/off variable
boolean leftSensor;
// boolean centerSensor;
boolean rightSensor;

// Set initial wheel speeds
int leftWheelSpeed = 20;
int rightWheelSpeed = 20;


void setup() {
  pinMode(leftSensorPin, INPUT);   // Set sensor pins as input
  // pinMode(centerSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);

  Serial.begin(9600);          // Initialize serial communication for debugging
}

void loop() {
  bool leftRead = readSensor(leftSensorPin, leftThreshold);
  bool rightRead = readSensor(rightSensorPin, rightThreshold);

  // get analog values for plotting
  int leftAnalogRead = analogReadSensor(leftSensorPin);
  int rightAnalogRead = analogReadSensor(rightSensorPin);

  Serial.print(leftAnalogRead);
  Serial.print(" ");
  Serial.print(rightAnalogRead);
  Serial.print(" ");
  Serial.print(leftWheelSpeed);
  Serial.print(" ");
  Serial.println(rightWheelSpeed);

  motorControl(leftRead, rightRead);
  
}

int analogReadSensor(int sensorPin){

  int sensorVal = analogRead(sensorPin);

  return sensorVal;
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
    leftWheelSpeed = 20;
    rightWheelSpeed = 20;

  }
  else if (leftSense){
    leftWheelSpeed = 0;
    rightWheelSpeed = 40;

  }
  else if(rightSense){
    leftWheelSpeed = 40;
    rightWheelSpeed = 0;
  }

}
