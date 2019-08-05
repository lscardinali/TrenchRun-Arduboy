/*
 Trench Run
 Copyright (C) 2019 Lucas Cardinali
 All rights reserved.
*/

#include "global.h"
#include "assets.h"
#include "intro.h"
#include "input.h"
#include "menu.h"
#include "game.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateIntroText,
  stateIntroCrawl,
  stateMenu,
  stateWarmup,
  stateGame,
  stateWin,
  stateLose,
};

void setup() {
  ab.begin();
  Serial.begin(9600);
  beep.begin();
  tunes.initChannel(PIN_SPEAKER_1);
  tunes.toneMutesScore(true);
  ab.initRandomSeed();
  ab.setFrameRate(FPS);
  ab.audio.on();
}

void loop() {
  if (!(ab.nextFrame())) return;
  beep.timer();
  ab.pollButtons();
  ((FunctionPointer) pgm_read_word(&mainGameLoop[gameState]))();
  checkInput();
//  drawCpuUsage();
  ab.display(true);
}
