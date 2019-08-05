#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>

//Constants

#define FPS 60

#define DISTANCE_FROM_EXAUST_PORT 10000
#define DEFAULT_CROSSHAIR_X 58
#define DEFAULT_CROSSHAIR_Y 24
#define CROSSHAIR_LIMIT_LEFT 0
#define CROSSHAIR_LIMIT_TOP 0
#define CROSSHAIR_LIMIT_RIGHT 117
#define CROSSHAIR_LIMIT_BOTTOM 46
#define MAXIMUM_TIES 2

//States
#define STATE_INTRO_TEXT 0
#define STATE_INTRO_LOGO 1
#define STATE_INTRO_CRAWL 2
#define STATE_MENU 3
#define STATE_WARMUP 4
#define STATE_GAME 5
#define STATE_WIN 6
#define STATE_LOSE 7

#define TIE_FRAMES 8

Arduboy2 ab;
Sprites sprites;
char tBuffer[22];

byte gameState = STATE_INTRO_TEXT;
byte previousGameState = STATE_INTRO_TEXT;


int8_t xDisplacement = 0;
int8_t yDisplacement = 0;

byte crosshairX = DEFAULT_CROSSHAIR_X;
byte crosshairY = DEFAULT_CROSSHAIR_Y;
unsigned int currentDistanceFromExaustPort = 10000;

byte lastCpuLoad;

byte lives = 3;

bool tie2Enabled = false;

bool tieAlive[2] = { false, false };
byte tieRespawnTime[2] = {0 , 0};
byte tieX[2] = {0, 0};
byte tieY[2] = {0, 0};
byte tieFrame[2] = {0, 0};


void drawCpuUsage()
{
  if (ab.everyXFrames(15))
  {
    lastCpuLoad = ab.cpuLoad(); 
  }
  ab.setCursor(0, 0);
  ab.print(lastCpuLoad);
}


#endif
