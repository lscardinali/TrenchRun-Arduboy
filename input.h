#ifndef INPUT_H
#define INPUT_H

#include "global.h"

void checkInput() {
  switch (gameState) {
    case STATE_INTRO_TEXT:
      if (ab.justPressed(A_BUTTON | B_BUTTON)) {
        gameState = STATE_INTRO_LOGO;
      }
      break;
    case STATE_INTRO_LOGO:
      if (ab.justPressed(A_BUTTON | B_BUTTON)) {
        gameState = STATE_INTRO_CRAWL;
      }
      break;
    case STATE_INTRO_CRAWL:
      if (ab.justPressed(A_BUTTON | B_BUTTON)) {
        gameState = STATE_MENU;
      }
      break;
    case STATE_MENU:
      if (ab.justPressed(A_BUTTON | B_BUTTON)) {
        gameState = STATE_WARMUP;
      }
      break;
    case STATE_GAME:
      if (ab.pressed(LEFT_BUTTON) && crosshairX - 2 >= CROSSHAIR_LIMIT_LEFT) {
        crosshairX -= 2;
      }
  
      if (ab.pressed(RIGHT_BUTTON) && crosshairX + 2 <= CROSSHAIR_LIMIT_RIGHT) {
        crosshairX += 2;
      }
    
      if (ab.pressed(UP_BUTTON) && crosshairY - 2 >= CROSSHAIR_LIMIT_TOP) {
        crosshairY -= 2;
      }
  
      if (ab.pressed(DOWN_BUTTON) && crosshairY + 2 <= CROSSHAIR_LIMIT_BOTTOM) {
        crosshairY += 2;
      }
      
  }
}

#endif
