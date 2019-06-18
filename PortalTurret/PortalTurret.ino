#include <Servo.h> //import library for servo to run
Servo armLeft; //sets the left servo to an object
int rotation = 0; //creates variable for servo rotation (int = var)
Servo armRight; //sets the right servo to an object

void setup() {
  armLeft.attach(2);  //attach the left servo to pin 2
  armRight.attach(3);  //attach the right servo to pin 3
  Serial.begin(9600); //sets the amount of data that can do through the cables (called baud)
}

void loop() {
  for (rotation = 0; rotation < 180; rotation++) { //goes from 0 degrees to 180, changes rotation by 1
     armLeft.write(rotation);  //servo goes to position armLeftRot
     delay(5); //waits 5 miliseconds
     armRight.write(rotation);
     delay(5);
  }
  for (rotation = 180; rotation > 0; rotation--) { //goes from 180 degress to 0, changes rotation by -1
     armLeft.write(rotation);  //servo goes to position armLeftRot
     delay(5);
     armRight.write(rotation);
     delay(5);
  }
}
