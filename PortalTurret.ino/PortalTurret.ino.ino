#include <Servo.h> //import library for servo to run
#include <SoftwareSerial.h>  //import library for setting receiver and tranceiver software serial
#include <DFPlayerMini_Fast.h>  //import library for playing mp3 files

SoftwareSerial playerSerial(2, 3); //RX and TX
DFPlayerMini_Fast turretSounds;  //set the mp3 player to an object named turretSounds
Servo arms; //sets the servo to an object
Servo base;
int armRot = 0; //creates variable for servo rotation (int = var)
int baseRot = 0;  //creates variable for servo rotation in base
int bullets = 0;  //creates variable for bullet LED fire
int targetAcquired;  //creates variable to set if the PIR sensor is active
int turretStatus;  //0 = closed   1 = open
int sound;  //creates variable to determine randomizer for sound effects

void setup() {
  base.attach(4);  //attach the base servo to pin 2
  arms.attach(5);  //attach the arms servo to pin 3
  pinMode(7, INPUT);  //attach the motion sensor to pin and set it to an input
  pinMode(8, OUTPUT); //attach the laser to pin and set it to an output
  pinMode(9, OUTPUT);  //attach set of red eye LEDs to pin and set it to an output
  pinMode(10, OUTPUT);  //attach a set of bullet LEDs to pin and set it to an output
  pinMode(11, OUTPUT);  //attach a set of bullet LEDs to pin and set it to an output
  //sets baud for the mp3 player, overall wire connection, and the reciever and transciever
  Serial.begin(115200);
  playerSerial.begin(9600);
  turretSounds.begin(playerSerial);
  turretSounds.volume(30);  //sets mp3 volume  0 - 30
  delay(200);  //prevents from breaking down
  //INTIALIZATION SEQUENCE
  Serial.println("Initializing...");
  digitalWrite(9, HIGH);  //turn on eye
  turretSounds.play(3);  //play 0003  Activation
  delay(3000);  //wait 3 seconds
  digitalWrite(9, LOW); //turn off eye
  digitalWrite(8, HIGH);  //Turns laser on
  Serial.println("Ready");
}

void loop() {  
  targetAcquired = digitalRead(5);
    if (targetAcquired == LOW) {
      delay(1000);
      if (turretStatus == 1) {
        //SEARCHING
        sound == random(1, 6);
        if (sound == 1) { 
          turretSounds.play(10);  //Hellooooo
        }
        else if (sound == 2) {
          turretSounds.play(11);  //Searching
        }
        else if (sound == 3) {
          turretSounds.play(13);  //Is Anyone There?
        }
        else if (sound == 4) {
          turretSounds.play(19);  //Are You Still There?
        }
        else if (sound == 5) {
          turretSounds.play(20);  //Target Lost
        }
        for (baseRot = 0; baseRot < 60; baseRot++) {
          base.write(baseRot);
          delay(5);
        }
        for (baseRot = 60; baseRot > -60; baseRot--) {
          base.write(baseRot);
          delay(5);
        }
        for (baseRot = -60; baseRot < 0; baseRot++) {
          base.write(baseRot);
          delay(5);
        }
        delay(2000);
        //CLOSE ARMS
        sound == random(1, 5);
        if (sound == 1) {
          turretSounds.play(15);  //Sleep mode activated
        }
        else if (sound == 2) {
          turretSounds.play(16);  //Goodnight
        }
        else if (sound == 3) {
          turretSounds.play(17);  //Resting
        }
        else if (sound == 4) {
          turretSounds.play(18);  //Naptime
        }
        for (armRot = 180; armRot > 0; armRot--) { //goes from 180 degress to 0, changes rotation by -1
           arms.write(armRot);  //servo goes to position rotation
           delay(5);
        }
        turretStatus = 0;
      }
    }
  else {
    //OPEN ARMS
    if (turretStatus == 0) {
      digitalWrite(9, HIGH);  //turns on eye
      sound == random(1, 9);
      if (sound == 1) {
        turretSounds.play(4); //Hi
      }
      else if (sound == 2) {
        turretSounds.play(5);  //Target Acquired
      }
      else if (sound == 3) {
        turretSounds.play(6);  //firing
      }
      else if (sound == 4) {
        turretSounds.play(7);  //gptcha
      }
      else if (sound == 5) {
        turretSounds.play(8);  //There you are
      }
      else if (sound == 6) {
        turretSounds.play(9);  //I see you
      }
      else if (sound == 7) {
        turretSounds.play(12);  //Sentry mode activated
      }
      else if (sound == 8) {
        turretSounds.play(14);  //Hello
      }
      for (armRot = 0; armRot < 180; armRot++) { //goes from 0 degrees to 180, changes rotation by 1
         arms.write(armRot);
         delay(5); //waits 5 miliseconds
      }
      turretStatus = 1;
      //FIRE BULLET LEDs
      for (bullets = 0; bullets < 4; bullets++) {
        turretSounds.play(2); //play 0002 gunshots
        digitalWrite(10, HIGH);  //turn on upper LEDs
        delay(50);
        digitalWrite(10, LOW);  //turn off upper LEDs
        delay(15);
        digitalWrite(11, HIGH); //turn on lower LEDs
        delay(50);
        digitalWrite(11, LOW);  //turn off lower LEDs
        delay(15);
        digitalWrite(10, HIGH);  //turn on upper LEDs
        delay(50);
        digitalWrite(10, LOW);  //turn off upper LEDs
        delay(100);
        turretSounds.play(2);
        digitalWrite(11, HIGH); //turn on lower LEDs
        delay(50);
        digitalWrite(11, LOW);  //turn off lower LEDs
        delay(15);
        digitalWrite(10, HIGH);  //turn on upper LEDs
        delay(50);
        digitalWrite(10, LOW);  //turn off upper LEDs
        delay(15);
        digitalWrite(11, HIGH); //turn on lower LEDs 
        delay(50);
        digitalWrite(11, LOW);  //turn off lower LEDs
        delay(100);
      }
    }
  }
}
