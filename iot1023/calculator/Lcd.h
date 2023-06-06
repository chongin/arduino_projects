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
    InitOptions();
  }

  void UpdateDraw() 
  {
    lcd.clear();
    _lcd_grphic->DrawTime((millis() / 1000) - _seconds, 0);

    _flashing_value++;
    if (_formula.length() > 0)
    {
      _lcd_grphic->DrawString(_formula, 0, _current_row);
    }

    int next_pos = _formula.length();
    if (_flashing_value % 2 == 0)
    {
      Serial.println(_flashing_value);
      _lcd_grphic->DrawFlashingSymbol(next_pos, _current_row);
    } 
    else {
      if (_default_show_number)
      {
        _lcd_grphic->DrawNumber(_numberArray[_current_number_index], next_pos, _current_row);
      }
      else {
        _lcd_grphic->DrawPicture(_symbol_options[_current_option_index], next_pos, _current_row);
      }
    }
    
    // for (int i = 0; i < 7; ++i)
    // {
    //   lcd.setCursor(i, _current_row);
    //   lcd.write(byte(i));
    //   delay(1000);
    // }

    // for (int i = 7; i < 16; ++i)
    // {
    //   _lcd_grphic->DrawNumber(i - 7, i, _current_row);
  
    //   delay(1000);
    // }
}

void IncreaseOptionIndex()
{
  if (_default_show_number)
  {
    _current_number_index += 1;
    _current_number_index %= 10;
  }
  else {
    _current_option_index += 1;
    _current_option_index %= 7;
  }
}

void DecreaseOptionIndex()
{
  if (_default_show_number)
  {
    _current_number_index -= 1;
    _current_number_index %= 10;
  }
  else {
    _current_option_index -= 1;
    _current_option_index %= 7;
  }
}

void ChangeShowOption()
{
  _default_show_number = !_default_show_number;
  _current_option_index = 0;
  _current_number_index = 0;
}

void MoveForward()
{

}

void MoveBackward()
{

}

private:
  void InitOptions()
  {
    _symbol_option_size = 7;
    _symbol_options = new char[7]{'+', '-', '*', '/', '=', '{', '}'};
    _numberArray = new int[10]{0, 1,2,3,4,5,6,7,8,9};

    _formula = "3+4*5-6/3";
  }

private:
  LcdGrphic* _lcd_grphic;
  int _current_row;
  int _current_col;
  String _formula;
  
  char* _symbol_options;
  int _symbol_option_size;
  int* _numberArray;
  int _current_option_index = 0;
  int _current_number_index = 0;
  bool _default_show_number = true;
  int _flashing_value = 0;
  int _seconds = millis() / 1000;
};


