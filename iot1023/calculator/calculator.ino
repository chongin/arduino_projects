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
  current_joy_stick->UpdateCommand();
  if (current_joy_stick->CurrentCommand() != CommandEnum::None)
  {
    Serial.println("DoSomething:" + current_joy_stick->GetCommandStr());
    HandleCommand(current_joy_stick->CurrentCommand());
  }
  
  lcd_Mgr->UpdateDraw();
  delay(600);
}

void HandleCommand(CommandEnum command)
{
  switch(command)
  {
    case CommandEnum::Left:
      lcd_Mgr->ChangeShowOption();
      break;
    case CommandEnum::Right:
      //str = "Right";
      break;
    case CommandEnum::Up:
      lcd_Mgr->IncreaseOptionIndex();
      break;
    case CommandEnum::Down:
      lcd_Mgr->DecreaseOptionIndex();
      break;
  }
}