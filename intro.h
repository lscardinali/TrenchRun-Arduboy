#ifndef INTRO_H
#define INTRO_H

#include "global.h"
#include "assets.h"

#define INTRO_TEXT_FRAME_LIMIT 180

#define INTRO_LOGO_FRAMES 5
#define INTRO_LOGO_FRAME_UPDATE 30

#define INTRO_CRAWL_FRAME_UPDATE 3
#define INTRO_CRAWL_FRAME_LIMIT -128

byte logoFrameCount = 0;
int8_t crawlFrameCount = 64;

void stateIntroText() {
  ab.setCursor(0, 24);
  for (unsigned char i = 0; i < TEXT_INTRO_LINES; i++) {
    ab.println(strcpy_P(tBuffer, (char*)pgm_read_word(&(textIntro[i]))));
  }
  if (ab.everyXFrames(INTRO_TEXT_FRAME_LIMIT)) {
    gameState = STATE_INTRO_LOGO;
  }
}

void stateIntroLogo() {
  if (logoFrameCount == INTRO_LOGO_FRAMES) {
    gameState = STATE_INTRO_CRAWL;
  } else {
    Sprites::drawOverwrite(2, 2, StarWarsLogoSprite, logoFrameCount);
    if (ab.everyXFrames(INTRO_LOGO_FRAME_UPDATE)) {
      logoFrameCount += 1;
    }
  }
}

void stateIntroCrawl() {
  if(crawlFrameCount == INTRO_CRAWL_FRAME_LIMIT) {
    gameState = STATE_MENU;
  } else {
    ab.setCursor(20, crawlFrameCount);
    for (unsigned char i = 0; i < CRAWL_LINES; i++) {
      ab.println(strcpy_P(tBuffer, (char*)pgm_read_word(&(crawlText[i]))));
    }
    if (ab.everyXFrames(INTRO_CRAWL_FRAME_UPDATE)) {
      crawlFrameCount -= 1;
    }
  }
}

#endif
