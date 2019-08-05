#ifndef GAME_H
#define GAME_H

#include "global.h"

#define TRENCH_BACKGROUND_FRAMES 2

byte trenchBackgroundFrame = 0;

// TODO: No magic numbers
void drawTrench() {
  if(currentDistanceFromExaustPort == 0) {
    Sprites::drawOverwrite(-16 - xDisplacement / 3,
                         -14 - yDisplacement / 3,
                         TrenchBackgroundSprites, 
                         3); 
  } else {
     Sprites::drawOverwrite(-16 - xDisplacement / 3,
                           -14 - yDisplacement / 3,
                           TrenchBackgroundSprites, 
                           trenchBackgroundFrame); 
                    
    if (ab.everyXFrames(5))
    {
      (trenchBackgroundFrame == TRENCH_BACKGROUND_FRAMES) ? trenchBackgroundFrame = 0 : trenchBackgroundFrame += 1;
    }
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
      Sprites::drawPlusMask(tieX[i] - xDisplacement / 4, tieY[i] - yDisplacement / 4, tie, tieFrame[i]);
    }
  }
}

void checkForTieRespawn() {
  if(ab.everyXFrames(60) && currentDistanceFromExaustPort > 0) {
    for(byte i = 0; i < 2; i++) {
      if(i == 1 && !tie2Enabled) break;
      if(!tieAlive[i]) {
        if(tieRespawnTime[i] == 0) {
          Serial.println("isnt alive");
          tieRespawnTime[i] = random(1, 4);
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
}

void advanceTies() {
  if(ab.everyXFrames(30)) {
    for(byte i = 0; i < 2; i++) { 
      if(tieAlive[i]) {
        if(tieFrame[i] == TIE_FRAMES) {
          beep.tone(beep.freq(223.251), 5);
          tieAlive[i] = false;
          hull -= 1;
        } else {
          tieFrame[i] += 1;
        }
      }
    }
  }
}

void checkDeath() {
 
  if(hull == 0) {
    lives--;
    if (lives == 0) {
      gameState = STATE_LOSE;
    } else {
      gameState = STATE_WARMUP;
    }
  }
}

void checkFinalShot() {
  if(ab.everyXFrames(60) && currentDistanceFromExaustPort == 0) {
    hull = 0;
  }
}

void checkShoot() {
  if(shootCooldownCounter > 0) {
    shootCooldownCounter--;
  }
  if(shooting) {
    beep.tone(beep.freq(787.330), 5);
    
    byte crosshairXCenter = crosshairX + 5;
    byte crosshairYCenter = crosshairY + 5;

    if(currentDistanceFromExaustPort == 0) {
      if(crosshairXCenter >= 58 && 
             crosshairXCenter <= 70 &&
             crosshairYCenter >= 26 && 
             crosshairYCenter <= 38) {
        gameState = STATE_WIN;       
      }
    }

    for(byte i = 0; i < 2; i++) { 
      if(tieAlive[i]) {
          byte tieXCollisionStart = tieX[i] - xDisplacement / 4;
          byte tieYCollisionStart = tieY[i] - yDisplacement / 4;
          byte tieXCollisionEnd = (tieX[i] - xDisplacement / 4) + 14;
          byte tieYCollisionEnd = (tieY[i] - yDisplacement / 4) + 28;
          
          if(crosshairXCenter >= tieXCollisionStart && 
             crosshairXCenter <= tieXCollisionEnd &&
             crosshairYCenter >= tieYCollisionStart && 
             crosshairYCenter <= tieYCollisionEnd) {
            tieAlive[i] = false;
          }
       }
     }
    blinkCounter = BLINK_FRAMES;
    shooting = false;
  }
}

void drawBlink() {
  if(blinkCounter > 0) {
    if(blinkCounter % 2) {
      ab.fillRect(0, 0, 128, 64);
    }
    blinkCounter--;
  }
}

void stateGame() {
  checkShoot();
  checkFinalShot();
  checkDeath();
  calculateDisplacement();
  advanceTies();
  checkForTieRespawn();
  drawTrench();
  drawTies();
  drawBlink();
  drawCockpit();
  drawCrosshair();
  decreaseDistance();
}

#endif
