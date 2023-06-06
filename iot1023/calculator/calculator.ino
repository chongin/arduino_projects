int i = 0;
#include "joystick.h"
#include "Lcd.h"

JoyStick * current_joy_stick = NULL;
LCDMgr * lcd_Mgr = NULL;
void setup() 
{
  Serial.begin(9600);
  current_joy_stick = new JoyStick();
  lcd_Mgr = new LCDMgr();
}

void loop() 
{
  // current_joy_stick->UpdateCommand();
  // if (current_joy_stick->CurrentCommand() != CommandEnum::None)
  // {
  //   Serial.println("DoSomething:" + current_joy_stick->GetCommandStr());
  // }
  
  lcd_Mgr->UpdateDraw();
  delay(500);
}