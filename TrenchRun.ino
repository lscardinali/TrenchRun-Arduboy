 /*
 Trench Run
 Copyright (C) 2019 Lucas Cardinali
 All rights reserved.
*/

#include <Arduboy2.h>

// block in EEPROM to save high scores
#define EE_FILE 2

Arduboy2 arduboy;
//BeepPin1 beep;

const unsigned int FRAME_RATE = 60;
const unsigned int DISTANCE_FROM_EXAUST_PORT = 65535;

boolean intro = true;
boolean menu = false;
boolean warmup = false;
boolean onGame = false;
boolean win = false;
boolean lose = false;

unsigned int currentDistanceFromExaustPort = 65535;

byte lives = 3;


void setup() {
  arduboy.begin();
  //beep.begin();
  arduboy.setFrameRate(FRAME_RATE);
}

void loop() {
  arduboy.clear();
  // put your main code here, to run repeatedly:


  arduboy.display();
}

void titleScreen() {
  arduboy.clear();
  arduboy.setCursor(16,22);
  arduboy.setTextSize(2);
  arduboy.print("A long time ago in a galaxy far,");
  arduboy.print("\n");
  arduboy.print("far away...");
  arduboy.setTextSize(1);
  //Show Logo
  //Scroll Text
  
}

void warmupScreen() {
  arduboy.clear();
  arduboy.setCursor(16,22);
  arduboy.setTextSize(2);
  arduboy.print("Red 5, you're next,");
  arduboy.print("\n");
  arduboy.print("Prepare to Enter the Trench");
  arduboy.setTextSize(1);
  //Display remaining Lives
}


void gameLoop() {
  //Loop Two bg images
  //spawn tie fighters times remaining distance
  //decrease distance counter

  //if distance counter == 0 show exaust port image

  //if tie fighter too close, destroy it and damage player
  //if health == 0 go back to the warmup screen
  //if health == 0 and lives == 0 go back to the lose screen
  //if distance counter == 0 and pressed button within 1 second, show victory screen
  //check for controls to move the crosshair
}
