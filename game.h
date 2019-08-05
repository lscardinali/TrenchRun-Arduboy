#ifndef GAME_H
#define GAME_H

#include "global.h"

#define TRENCH_BACKGROUND_FRAMES 2


byte trenchBackgroundFrame = 0;

// TODO: No magic numbers
void drawTrench() {
   Sprites::drawOverwrite(-16 - xDisplacement / 3,
                         -14 - yDisplacement / 3,
                         trenchBackgroundSprites, 
                         trenchBackgroundFrame); 
                  
  if (ab.everyXFrames(5))
  {
    (trenchBackgroundFrame == TRENCH_BACKGROUND_FRAMES) ? trenchBackgroundFrame = 0 : trenchBackgroundFrame += 1;
  }
}

void drawCockpit() {
  //TODO: No Magic Numbers
  Sprites::drawPlusMask(-16 + xDisplacement / 2, -14 + yDisplacement / 2, cockpit, 0);
  ab.setCursor(50 + xDisplacement / 2, 50 + yDisplacement / 2);
  ab.print("0");
  ab.print(currentDistanceFromExaustPort);
}

void drawCrosshair() {
  Sprites::drawPlusMask(crosshairX, crosshairY, crosshair, 0);
}

void decreaseDistance() {
    if (ab.everyXFrames(1) && currentDistanceFromExaustPort > 0) {
    currentDistanceFromExaustPort = currentDistanceFromExaustPort - 1;
  }
}

void calculateDisplacement() {
  xDisplacement = crosshairX - DEFAULT_CROSSHAIR_X;
  yDisplacement = crosshairY - DEFAULT_CROSSHAIR_Y;
}

void drawTies() {
  for(byte i = 0; i < 2; i++) {
    if(tieAlive[i]) {
      if(tieFrame[i] == TIE_FRAMES) {
        //Damage Player
        tieAlive[i] = false;
      }
      Sprites::drawPlusMask(tieX[i] - xDisplacement / 4, tieY[i] - yDisplacement / 4, tie, tieFrame[i]);
    }
  }
}

void checkForTieRespawn() {
  if(ab.everyXFrames(60)) {
    for(byte i = 0; i < 2; i++) {
      if(i == 1 && !tie2Enabled) break;
      if(tieRespawnTime[i] == 0 && !tieAlive[i]) {
        tieRespawnTime[i] = random(3, 6);
        tieAlive[i] = true;
        tieX[i] = random(0, 100);
        tieY[i] = random(0, 36);
        tieFrame[i] = 0;
      } else {
        tieRespawnTime[i] -= 1;
      }
    }
  }
}

void advanceTies() {
  if(ab.everyXFrames(30)) {
    for(byte i = 0; i < 2; i++) { 
      if(tieAlive[i]) {
        if(tieFrame[i] == TIE_FRAMES) {
          tieAlive[i] = false;
        } else {
          tieFrame[i] += 1;
        }
      }
    }
  }
}

void stateGame() {
  calculateDisplacement();
  advanceTies();
  checkForTieRespawn();
  drawTrench();
  drawTies();
  drawCockpit();
  drawCrosshair();
  decreaseDistance();
}

#endif
