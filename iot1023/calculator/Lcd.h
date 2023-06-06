#include <LiquidCrystal.h>

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

    initializeGraphics();
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
      lcd.setCursor(i, _current_row);
      lcd.print(i - 7);
      delay(1000);
    }
}
private:
  void initializeGraphics() 
  {
    _addition_graphic = new byte[8]{
      B00000,   
      B00100,
      B00100,
      B11111,
      B11111,
      B00100,
      B00100,
      B00000
    };
    
    _subtraction_graphic = new byte[8]{
      B00000,   
      B00000,
      B00000,
      B11111,
      B11111,
      B00000,
      B00000,
      B00000
    };

    _multiplication_graphic = new byte[8]{
      B00000,
      B00000,
      B10001,
      B01010,
      B00100,
      B01010,
      B10001,
      B00000
    };

    _division_graphic = new byte[8]{
      B00000,
      B01100,
      B00000,
      B11111,
      B00000,
      B00000,
      B01100,
      B00000
    };

    _equal_graphic = new byte[8]{
      B00000,
      B00000,
      B01110,
      B00000,
      B01110,
      B00000,
      B00000,
      B00000
    };

    _left_bracket_graphic = new byte[8]{
      B00010,
      B00100,
      B01000,
      B01000,
      B01000,
      B00100,
      B00010,
      B00000
    };

    _right_bracket_graphic = new byte[8]{
      B01000,
      B00100,
      B00010,
      B00010,
      B00010,
      B00100,
      B01000,
      B00000
    };

    lcd.createChar(0, _addition_graphic);
    lcd.createChar(1, _subtraction_graphic);
    lcd.createChar(2, _multiplication_graphic);
    lcd.createChar(3, _division_graphic);
    lcd.createChar(4, _equal_graphic);
    lcd.createChar(5, _left_bracket_graphic);
    lcd.createChar(6, _right_bracket_graphic);
  }
private:
  byte* _addition_graphic;
  byte* _subtraction_graphic;
  byte* _multiplication_graphic;
  byte* _division_graphic;
  byte* _equal_graphic;
  byte* _left_bracket_graphic;
  byte* _right_bracket_graphic;

  int _current_row;
  int _current_col;
};


