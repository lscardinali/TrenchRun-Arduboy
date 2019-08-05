#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
//Constants

#define FPS 60

#define DISTANCE_FROM_EXAUST_PORT 7350
#define DEFAULT_CROSSHAIR_X 58
#define DEFAULT_CROSSHAIR_Y 24
#define CROSSHAIR_LIMIT_LEFT 8
#define CROSSHAIR_LIMIT_TOP 0
#define CROSSHAIR_LIMIT_RIGHT 110
#define CROSSHAIR_LIMIT_BOTTOM 46
#define MAXIMUM_TIES 2

//States
#define STATE_INTRO_TEXT 0
#define STATE_INTRO_CRAWL 1
#define STATE_MENU 2
#define STATE_WARMUP 3
#define STATE_GAME 4
#define STATE_PAUSE 5
#define STATE_DEATH 6
#define STATE_WIN 7
#define STATE_LOSE 8

#define TIE_FRAMES 7
#define BLINK_FRAMES 6
#define SHOOT_COOLDOWN 30;
#define EXPLOSION_COOLDOWN 30;
#define EXPLOSION_BLINK_FRAMES 60;

Arduboy2 ab;
Sprites sprites;
BeepPin1 beep;
ArduboyPlaytune tunes(ab.audio.enabled);

char tBuffer[22];

byte gameState = STATE_INTRO_TEXT;

byte logoFrameCount = 0;
int crawlFrameCount = 64;

bool shooting = false;

byte blinkCounter = 0;
byte explosionBlinkCounter = 0;
byte shootCooldownCounter = 0;

int8_t xDisplacement = 0;
int8_t yDisplacement = 0;

byte crosshairX = DEFAULT_CROSSHAIR_X;
byte crosshairY = DEFAULT_CROSSHAIR_Y;
unsigned int currentDistanceFromExaustPort = DISTANCE_FROM_EXAUST_PORT;

byte lastCpuLoad;

byte lives = 3;
byte hull = 3;

bool tie2Enabled = false;

bool tieAlive[2] = { false, false };
byte tieRespawnTime[2] = {0 , 0};
byte tieX[2] = {0, 0};
byte tieY[2] = {0, 0};
byte tieFrame[2] = {0, 0};
byte tieExplosionCooldown[2] = {0, 0};

void resetLevel() {
    tieAlive[0] = false;
    tieAlive[1] = false;
    tieRespawnTime[0] = random(2, 4);
    tieRespawnTime[1] = random(2, 4);
    tie2Enabled = false;
    hull = 3;
    crosshairX = DEFAULT_CROSSHAIR_X;
    crosshairY = DEFAULT_CROSSHAIR_Y;
    currentDistanceFromExaustPort = DISTANCE_FROM_EXAUST_PORT;
}

void resetGame() {
  lives = 3;
  logoFrameCount = 0;
  crawlFrameCount = 64;
}

#endif
