#ifndef MENU_H
#define MENU_H

#include "assets.h"

#define WARMUP_FRAME_COUNT 200

void stateMenu() {
  Sprites::drawOverwrite(22, 0, StarWarsLogo, 0);
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
    resetLevel();
    gameState = STATE_GAME;
  }
}

void stateWin() {
  ab.setCursor(0, 0);
  ab.println("Congratulations");
  ab.println("You WON!");
  ab.println("Press a Button");
}

void stateLose() {
  ab.setCursor(0, 0);
  ab.println("Too bad");
  ab.println("You Lose!");
  ab.println("Press a Button");
}

#endif
