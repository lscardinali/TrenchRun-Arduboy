 /*
 Trench Run
 Copyright (C) 2019 Lucas Cardinali
 All rights reserved.
*/

#include <Arduboy2.h>
//#include <ArduboyPlaytune.h>
#include "assets.h"

// block in EEPROM to save high scores
//#define EE_FILE 2

Arduboy2 arduboy;
//ArduboyPlaytune tunes(arduboy.audio.enabled);
BeepPin1 beep;

const unsigned int FRAME_RATE = 60;
const unsigned int DISTANCE_FROM_EXAUST_PORT = 10000;
const byte DEFAULT_CROSSHAIR_X = 58;
const byte DEFAULT_CROSSHAIR_Y = 24;


byte tie_x[] = {0,0,0};
byte tie_y[] = {0,0,0};
byte tie_distance[] = {0,0,0};
bool tie_spawned[] = {false, false, false};
byte tie_respawn_time[] = {0,0,0};

byte trench_bg_sprite = 0;

enum game_states: byte {
  intro_state,
  menu_state,
  warmup_state,
  game_state,
  win_state,
  lose_state
};

enum intro_states: byte {
  text_state,
  logo_state,
  crawl_state
};

byte current_state = intro_state;
byte current_intro_state = text_state;
byte introLogoFrame = 0;
int introCrawlFrame = 64;

unsigned int currentDistanceFromExaustPort = 10000;

bool isFiring = false;

byte lives = 3;
byte hull = 3;
byte crosshairx = 58;
byte crosshairy = 24;
int x_displacement = 0;
int y_displacement = 0;

byte last_cpu_load = 0;

void setup() {
  arduboy.begin();
  arduboy.writeShowBootLogoFlag(false);
  arduboy.writeShowBootLogoLEDsFlag(false);
  beep.begin();
  arduboy.initRandomSeed();
//  tunes.initChannel(PIN_SPEAKER_1);
  arduboy.setFrameRate(FRAME_RATE);
//  tunes.playScore(score);  
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;
  beep.timer();
  arduboy.clear();
  arduboy.pollButtons();
  if(current_state == intro_state) {
    titleScreen();
  } else if(current_state == menu_state) {
    menu();
  } else if(current_state == warmup_state) {
    warmup();
  } else if(current_state == game_state) {
    gameLoop();
  } else if(current_state == win_state) {
    win();
  } else if(current_state == lose_state) {
    lose();
  }
  drawCpuUsage();
  arduboy.display();
}

void drawCpuUsage() {
  if(arduboy.everyXFrames(30)) {
    last_cpu_load = arduboy.cpuLoad();
  }
  arduboy.setCursor(0,0);
  arduboy.print(last_cpu_load);
}

void titleScreen() {
  if(current_intro_state == text_state) {
    drawIntroText();
  } else if(current_intro_state == logo_state) {
    drawIntroLogo();
  } else if(current_intro_state == crawl_state) {
    drawIntroCrawl();
  }
}

void drawIntroText() {
  arduboy.setCursor(0,22);
  arduboy.print("A long time ago in a\n");
  arduboy.print("galaxy far,far away...");
  if(arduboy.everyXFrames(3000) || arduboy.justPressed(A_BUTTON)) {
    current_intro_state = logo_state;
  }
}

void drawIntroLogo() {
  Sprites::drawOverwrite(2*introLogoFrame,2*introLogoFrame,star_wars_logo,introLogoFrame);
  if(arduboy.justPressed(A_BUTTON)) {
    current_state = menu_state;
  }
  if(arduboy.everyXFrames(30)) {
    if(introLogoFrame == 5) {
      current_intro_state = crawl_state;
    } else {
      introLogoFrame = introLogoFrame + 1;
    }
  }
}

void drawIntroCrawl() {
  arduboy.setCursor(20,introCrawlFrame);
  arduboy.print("THE DEATH STAR");
  arduboy.setTextSize(1);
  arduboy.print("\n\n");
  arduboy.print("It's a dire time for\nthe Rebels, having\n");
  arduboy.print("their base on Yavin\nbeen discovered,\n");
  arduboy.print("the Death Star\napproaches and within\n");
  arduboy.print("minutes it will be\nready to fire.\n\n");
  arduboy.print("The only hope rests\non Red Squardron that\n");
  arduboy.print("now prepares to\ninitiate their final\nattack...");
  if(arduboy.justPressed(A_BUTTON)) {
    current_state = menu_state;
  }
  if(arduboy.everyXFrames(3)) {
    //This can get awry
    introCrawlFrame = introCrawlFrame -1;
    if(introCrawlFrame == -140) {
      introCrawlFrame = 64;
      current_intro_state = text_state;
      current_state = menu_state;
    }
  }
}

void warmup() {
  if(lives == 0) {
    current_state = lose_state;
  } else {
    arduboy.setCursor(16,22);
    arduboy.print("Red 5, you're next,");
    arduboy.print("\n");
    arduboy.print("Prepare to Enter the Trench");
    arduboy.print("\n\n");
    arduboy.print("Remaining Lifes:");
    arduboy.print(lives);
    if(arduboy.everyXFrames(120)) {
      for(byte i = 0; i++; i < sizeof(tie_respawn_time)) {
        tie_respawn_time[i] = random(3,10);
      }
      current_state = game_state;
    }
  }
}

void menu() {
   Sprites::drawOverwrite(2,0,star_wars_logo,2);
   arduboy.setCursor(34,42);
   arduboy.print("DEATH STAR");

   arduboy.setCursor(20,56);
   arduboy.print("Press a button.");
   if(arduboy.justPressed(A_BUTTON)) {
    current_state = warmup_state;
   }
   arduboy.idle();
}

//Refactor this win and lose functions
void win() {
   arduboy.setCursor(0,0);
   arduboy.print("You Win");
   if(arduboy.justPressed(A_BUTTON)) {
    current_state = intro_state;
   }
}

void lose() {
   arduboy.setCursor(0,0);
   arduboy.print("You Lose");
   if(arduboy.justPressed(A_BUTTON)) {
    current_state = intro_state;
   }
}


void gameLoop() {
  calculateCockpitDisplacement();
  
  drawTrenchBackground();
  drawTies();
  drawShipCockpit();
  drawCrosshair();
  moveCrosshair();
  decreaseDistance();
  drawDistance();
  checkDeath();
  checkFire();
  checkTieSpawn();
  //if distance counter == 0 show exaust port image
  //if tie fighter too close, destroy it and damage player
  //if distance counter == 0 and pressed button within 1 second, show victory screen
}

void checkTieSpawn() {
  if(arduboy.everyXFrames(60)) {
    arduboy.print(sizeof(tie_respawn_time));
    for(byte i = 0; i++; i < sizeof(tie_respawn_time)) {
      arduboy.print(tie_respawn_time[i]);
      if(tie_respawn_time[i] > 0)
        tie_respawn_time[i] = tie_respawn_time[i] - 1;
    }
  }
  for(byte i = 0; i++; i < sizeof(tie_spawned)) {
  if(tie_spawned[i] == false && tie_respawn_time[i] == 0) {
    arduboy.print("time to spawn!");
    tie_spawned[i] = true;
    tie_x[i] = random(0, 100);
    tie_y[i] = random(0, 36);
    tie_distance[i] = 0;
  }

  }
  
}

void checkDeath() {
  if(hull == 0) {
    lives = lives -1;
    current_state = warmup_state;
  }
}

void drawTies() {
  for(byte i = 0; i++; i < sizeof(tie_spawned)) {
  if(tie_spawned[i] == true) {
    Sprites::drawPlusMask(tie_x[i] - x_displacement/4, tie_y[i] - y_displacement/4,tie,tie_distance[i]);
    tie_spawned[i] = true;
    tie_x[i] = random(0, 100);
    tie_y[i] = random(0, 36);
    tie_distance[i] = 0;
     if(arduboy.everyXFrames(30)) {
      tie_distance[i] = tie_distance[i] + 1;
    }
    if(tie_distance[i] == 6) {
      //damage player
      playToneTimed(175, 500);
      tie_spawned[i] = false;
    }
  }
  }
}

void checkFire() {
  if(arduboy.pressed(B_BUTTON) && arduboy.everyXFrames(10)) {
    isFiring = true;    
  }
  if(isFiring) {
    arduboy.fillRect(0,0,128,64);
    if(arduboy.everyXFrames(10)) {
    isFiring = false;
  }
  }
  
}

void decreaseDistance() {
  if(arduboy.everyXFrames(1) && currentDistanceFromExaustPort > 0) {
    currentDistanceFromExaustPort = currentDistanceFromExaustPort -1;
  }
}

void calculateCockpitDisplacement() {
   // TODO: change from int
  x_displacement = crosshairx - DEFAULT_CROSSHAIR_X;
  y_displacement = crosshairy - DEFAULT_CROSSHAIR_Y;
}

void drawDistance() {
  arduboy.setCursor(50 + x_displacement/2,54 + y_displacement/2);
  arduboy.print("0");
  arduboy.print(currentDistanceFromExaustPort);
}

void drawTrenchBackground() {
  Sprites::drawOverwrite(-16 - x_displacement/3, -14 - y_displacement/3, trench_bg, trench_bg_sprite);

  if(arduboy.everyXFrames(5)) {
    if(trench_bg_sprite == 2) {
      trench_bg_sprite = 0;
    } else {
      trench_bg_sprite = trench_bg_sprite + 1;
    }
  }
}

void drawShipCockpit() {
  Sprites::drawPlusMask(-16 + x_displacement/2, -14 + y_displacement/2,xwing_cockpit,0);
}

void drawCrosshair() {
  Sprites::drawPlusMask(crosshairx, crosshairy, crosshair, 0);
}

void moveCrosshair() {
  if (arduboy.pressed(LEFT_BUTTON) && crosshairx - 2 >= 0) {
      crosshairx = crosshairx - 2;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && crosshairx + 2 <= 117) {
      crosshairx = crosshairx + 2;
  }
  if (arduboy.pressed(UP_BUTTON) && crosshairy - 2 >= 0) {
      crosshairy = crosshairy - 2;
  }
  if (arduboy.pressed(DOWN_BUTTON) && crosshairy + 2 <= 46) {
      crosshairy = crosshairy + 2;
  }
}


// Play a tone at the specified frequency for the specified duration using
// a delay to time the tone.
// Used when beep.timer() isn't being called.
void playToneTimed(unsigned int frequency, unsigned int duration)
{
  beep.tone(beep.freq(frequency));
//  arduboy.delayShort(duration);
  beep.noTone();
}
