#pragma once
#include <LiquidCrystal.h>
#include "lcd_display.h"

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

  void SetNumbers(int* number_array, int number_size)
  {
    if (_number_array != NULL)
    {
      delete _number_array;
    }

    _number_size = number_size;
    _number_array = new int[number_size - 1];
    for (int i = 0; i < number_size; ++i) 
    {
      _number_array[i] = number_array[i];
    }
  }

  void UpdateView(String formula, int seconds) 
  {
    lcd.clear();
    _lcd_grphic->DrawTime(seconds, 0);
    _flashing_value++;
    if (formula.length() > 0)
    {
      _lcd_grphic->DrawString(formula, 0, _current_row);
    }

    int next_pos = formula.length();
    if (_flashing_value % 2 == 0)
    {
      _lcd_grphic->DrawFlashingSymbol(next_pos, _current_row);
    } 
    else {
      if (_default_show_number)
      {
        _lcd_grphic->DrawNumber(_number_array[_current_number_index], next_pos, _current_row);
      }
      else {
        _lcd_grphic->DrawPicture(_symbol_options[_current_option_index], next_pos, _current_row);
      }
    }
  }

  void IncreaseOptionIndex()
  {
    if (_default_show_number)
    {
      _current_number_index += 1;
      _current_number_index %= _number_size;
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

  char GetCurrentSelection()
  {
    if (_default_show_number)
    {
      char ch = '0' + _number_array[_current_number_index];
      Serial.print("Current Selection: ");
      Serial.println(ch);
      return ch;
    } else 
    {
      return _symbol_options[_current_option_index];
    }
  }

  //because current number selection already add to the formula.
  void RemoveCurrentSelection()
  {
    if (!_default_show_number) {
      return;
    }
    
    if (_number_size > 1) 
    {
      int* new_array = NULL;
      if (_number_size - 1 > 1)
      {
        new_array = new int[_number_size - 1];
      } else {
        new_array = new int[1];
      }

      for (int i = 0; i < _number_size - 1; ++i) {
        if (i != _current_number_index) {
          new_array[i] = _number_array[i];
        }
      }

      _number_size -= 1;
      delete[] _number_array;
      _number_array = new_array;
    }
  }

  void ResetSelection()
  {
    _current_option_index = 0;
    _current_number_index = 0;
    _default_show_number = true;
  }

private:

private:
  LcdGrphic* _lcd_grphic = NULL;
  int _current_row;
  int _current_col;
  
  char* _symbol_options = new char[7]{'+', '-', '*', '/', '=', '{', '}'};
  int _symbol_option_size = 7;
  int* _number_array = NULL;
  int _number_size = 0;

  int _current_option_index = 0;
  int _current_number_index = 0;
  bool _default_show_number = true;
  int _flashing_value = 0; //make the last digest flashing
};


