#pragma once

#include <LiquidCrystal.h>
#include "sounds.h"

class GameBannerGrphic
{
public:
  GameBannerGrphic(LiquidCrystal* lcd)
  {
    _lcd = lcd;
  }

  void DrawBanner()
  {
    _lcd->clear();
    char text1[] = "IoT 1023";
    char text2[] = "Chong In";
    for (int i = 0; i < 8; ++i)
    {
      _lcd->setCursor(4 + i, 0);
      _lcd->write(text1[i]);
      _lcd->setCursor(4 + i, 1);
      _lcd->write(text2[i]);
      playTone(17, _welcome_tones[i], _good_luck_durations[i]);
    }
   
    delay(1000);
     _lcd->clear();
    // _lcd->setCursor(3, 0);
    // _lcd->print("24 Solver");
    // _lcd->setCursor(3, 1);
    // _lcd->print("Good Luck");
    // delay(2000);
    //  _lcd->clear();
  }  
private:
  int _row0 = 0;
  int _row1 = 1;
  LiquidCrystal* _lcd = NULL;
  int _welcome_tones[8] = {659, 698, 784, 698, 659, 587, 659, 523};
  int _good_luck_durations[8] = {200, 200, 300, 300, 200, 200, 300, 400};
};