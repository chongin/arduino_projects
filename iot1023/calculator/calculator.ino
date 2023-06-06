#include "joystick.h"
#include "game.h"

JoyStick * current_joy_stick = NULL;
Game* game = NULL;

void setup() 
{
  Serial.begin(9600);
  current_joy_stick = new JoyStick();
  game = new Game();
  game->Start();
}

void loop() 
{
  current_joy_stick->UpdateCommand();
  if (current_joy_stick->CurrentCommand() != CommandEnum::None)
  {
    Serial.println("Detect Operation:" + current_joy_stick->GetCommandStr());
    game->HandleCommand(current_joy_stick->CurrentCommand());
  }
  
  game->Update();
  delay(600);
}

