//Initializing our constant variables.
//These represent the pins that we connected to the LEDs, button, and potentiometer.
//Doing this makes it easier to see what is being affected when using functions like digitalRead.
const int led1 = 11;
const int led2 = 10;
const int led3 = 9;
const int led4 = 6;
const int led5 = 5;
const int button = 3;
const int pot = 0;

//Declaring the other variables we use in the program.
int changeMode; //This represents which mode the program is running.
int buttonState; //This represents the current state of the button.
int lastButton; //This represents the last known state of the button.
int timer; //This is used to bypass delays - explained further in function blinkie().
int time_limit; //This represents how long each function takes to run.
int bright; //This represents the resistance from the potentiometer that will determine how bright the LEDs are.

void setup() {

  //Sets up LEDs as outputs and the button as an input.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  pinMode(button, INPUT);

  //Initializes variables
  changeMode = 0;
  timer = 0;
  lastButton = digitalRead(button);

}

void loop() {

  //Checks the potentiometer value and updates bright accordingly.
  bright = analogRead(pot);

  //Calls the change function - this updates the program when the button is pressed.
  change();

  //Resets the timer to 0 for each function.
  timer = 0;

  //Checks the changeMode variable, and calls the appropriate function.
  if (changeMode == 0){
    off();
  }

  if (changeMode == 1){
    on();
  }

  if (changeMode == 2){
    blinkie();
  }

  if (changeMode == 3){
    line();
  }

  if (changeMode == 4){
    march();
  }
}

//Updates the changeMode variable when the button is pressed, in order to change modes.
void change(){

  //Updates the current button state.
  buttonState = digitalRead(button);

  //Debounces the button - this makes sure that the button press isn't read more than once.
  if (buttonState != lastButton){
    
    if (buttonState == LOW){
      //Once button is debounced, updates changeMode variable and turns all LEDs off to have a clean reset.
      changeMode ++;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
    }
    //Updates the last button state.
    lastButton = buttonState;
  }
  //Ensures that changeMode will always be in the range of 0-4.
  changeMode = changeMode % 5;
  
}

//1st mode - turns all LEDs off.
void off(){
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  
}

//2nd mode - turns all LEDs on.
void on(){
  analogWrite(led1, bright / 4);
  analogWrite(led2, bright / 4);
  analogWrite(led3, bright / 4);
  analogWrite(led4, bright / 4);
  analogWrite(led5, bright / 4);
}

//3rd mode - blinks all LEDs at the same time.
void blinkie(){

  //Using millis() rather than delays - to ensure that the button press is always registered.
  //Checks that the current time is within a certain range, then runs the needed code.
  timer = 0;
  time_limit = 200;
  if ((millis() - timer) % time_limit < 100){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  if ((millis() - timer) % time_limit > 100 && (millis() - timer) % time_limit < time_limit){
    analogWrite(led1, bright / 4);
    analogWrite(led2, bright / 4);
    analogWrite(led3, bright / 4);
    analogWrite(led4, bright / 4);
    analogWrite(led5, bright / 4);
  }
}

//4th mode - blinks each LED one at a time
//Turns on the next LED in the line when the previous one turns off.
void line(){

  //Using the same timing strategy as blinkie()
  timer = 0;
  time_limit = 3050;
  
  if ((millis() - timer) % time_limit < 50){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }

  if ((millis() - timer) % time_limit > 50 && (millis() - timer) % time_limit < 550){
      analogWrite(led1, bright / 4);
  }

  if ((millis() - timer) % time_limit > 550 && (millis() - timer) % time_limit < 1050){
    digitalWrite(led1, LOW);
    analogWrite(led2, bright / 4);
  }

  if ((millis() - timer) % time_limit > 1050 && (millis() - timer) % time_limit < 1550){
    digitalWrite(led2, LOW);
    analogWrite(led3, bright / 4);
  }

  if ((millis() - timer) % time_limit > 1550 && (millis() - timer) % time_limit < 2050){
    digitalWrite(led3, LOW);
    analogWrite(led4, bright / 4);
  }

  if ((millis() - timer) % time_limit > 2050 && (millis() - timer) % time_limit < 2550){
    digitalWrite(led4, LOW);
    analogWrite(led5, bright / 4);
  }

  if ((millis() - timer) % time_limit > 2550 && (millis() - timer) % time_limit < time_limit){
    digitalWrite(led5, LOW);
  }
}

//5th mode - turns on every LED in order (one at a time), then turns them off (one at a time) in the reverse order.
void march(){

  //Using the same timing strategy as blinkie().
  timer = 0;
  time_limit = 1050;

  if ((millis() - timer) % time_limit < 50){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }

  if ((millis() - timer) % time_limit > 50 && (millis() - timer) % time_limit < 150){
    analogWrite(led1, bright / 4);
  }

  if ((millis() - timer) % time_limit > 150 && (millis() - timer) % time_limit < 250){
    analogWrite(led2, bright / 4);
  }
  
  if ((millis() - timer) % time_limit > 250 && (millis() - timer) % time_limit < 350){
    analogWrite(led3, bright / 4);
  }

  if ((millis() - timer) % time_limit > 350 && (millis() - timer) % time_limit < 450){
    analogWrite(led4, bright / 4);
  }

  if ((millis() - timer) % time_limit > 450 && (millis() - timer) % time_limit < 550){
    analogWrite(led5, bright / 4);
  }

  if ((millis() - timer) % time_limit > 550 && (millis() - timer) % time_limit < 650){
    digitalWrite(led5, LOW);
  }

  if ((millis() - timer) % time_limit > 650 && (millis() - timer) % time_limit < 750){
    digitalWrite(led4, LOW);
  }

  if ((millis() - timer) % time_limit > 750 && (millis() - timer) % time_limit < 850){
    digitalWrite(led3, LOW);
  }

  if ((millis() - timer) % time_limit > 850 && (millis() - timer) % time_limit < 950){
    digitalWrite(led2, LOW);
  }

  if ((millis() - timer) % time_limit > 950 && (millis() - timer) % time_limit < time_limit){
    digitalWrite(led1, LOW);
  }
  
}

