#include <LiquidCrystal.h>
#include "LcdDisplay.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int ContrastValue = 100;

class LCDMgr
{
public:
  LCDMgr()
  {
    analogWrite(6,ContrastValue);
    lcd.begin(16, 2);
    
    _current_row = 1;
    _current_col = 0;
    _lcd_grphic = new LcdGrphic(&lcd);
  }

  void UpdateDraw() 
  {
    lcd.clear();

    // for (int i = 0; i < 7; ++i)
    // {
    //   lcd.setCursor(i, _current_row);
    //   lcd.write(byte(i));
    //   delay(1000);
    // }

    for (int i = 7; i < 16; ++i)
    {
      _lcd_grphic->DrawNumber(i - 7, i, _current_row);
  
      delay(1000);
    }
}

private:
  void InitOptions()
  {
    _symbol_option_size = 7;
    _symbol_options = new char[7]{'+', '-', '*', '/', '=', '{', '}'};
  }
private:
  char* _symbol_options;
  int _symbol_option_size;
  LcdGrphic* _lcd_grphic;
  int _current_row;
  int _current_col;
};


