#ifndef MENU_H
#define MENU_H

#include "assets.h"

#define WARMUP_FRAME_COUNT 120

void stateMenu() {
  Sprites::drawOverwrite(2, 0, StarWarsLogoSprite, 2);
  ab.setCursor(34, 42);
  ab.print(strcpy_P(tBuffer, (char*)pgm_read_word(&(menuText[0]))));
  ab.setCursor(20, 56);
  ab.print(strcpy_P(tBuffer, (char*)pgm_read_word(&(menuText[1]))));
}

//TODO: Extract this strings
void stateWarmup() {
  ab.setCursor(16, 22);
  ab.print("Red 5, you're next,");
  ab.print("\n");
  ab.print("Prepare to Enter the Trench");
  ab.print("\n\n");
  ab.print("Remaining Lifes:");
  ab.print(lives);
  if (ab.everyXFrames(WARMUP_FRAME_COUNT))
  {
    tieAlive[0] = false;
    tieAlive[1] = false;
    tieRespawnTime[0] = random(3, 6);
    tieRespawnTime[1] = random(3, 6);
    
    gameState = STATE_GAME;
  }
}

#endif
