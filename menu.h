#ifndef MENU_H
#define MENU_H

#include "assets.h"

#define WARMUP_FRAME_COUNT 300

void stateMenu() {
  Sprites::drawOverwrite(24, 0, StarWarsLogo, 0);
  ab.setCursor(34, 42);
  ab.print(strcpy_P(tBuffer, (char*)pgm_read_word(&(menuText[0]))));
  ab.setCursor(20, 56);
  ab.print(strcpy_P(tBuffer, (char*)pgm_read_word(&(menuText[1]))));
}

void stateWarmup() {
  ab.setCursor(8, 10);
  ab.setTextSize(2);
  ab.print("GET READY");
  ab.setTextSize(1);
  ab.setCursor(10, 40);
  ab.print("Remaining Lifes:");
  ab.print(lives);
  if (ab.everyXFrames(255))
  {
    resetLevel();
    gameState = STATE_GAME;
  }
}

void stateWin() {
  ab.setCursor(0, 0);
  ab.println("Congratulations!");
  ab.println("");
  ab.println("You've dealt a");
  ab.println("criplling blow to the ");
   ab.println("empire!");
  ab.setCursor(18, 56);
  ab.println("-Press a Button-");
}

void stateLose() {
  ab.setCursor(0, 0);
  ab.println("Hope is lost!");
  ab.println("");
  ab.println("With you dies the");
  ab.println("last hope for a ");
   ab.println("liberated galaxy...");
  ab.setCursor(18, 56);
  ab.println("-Press a Button-");
}

#endif
