#include "joystick.h"
#include "game_manager.h"

JoyStick * current_joy_stick = NULL;
Game* game = NULL;
GameManager* game_mgr = NULL;

const int LED_PIN = 9;
const int BUTTON_PIN = 8;
const int BUZZER_PIN = 7;

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);

  current_joy_stick = new JoyStick();
  game_mgr = new GameManager();
  game_mgr->Init(BUZZER_PIN);
  game_mgr->CreateNewGame();
}

void loop() 
{
  current_joy_stick->UpdateCommand();
  if (current_joy_stick->CurrentCommand() != CommandEnum::None)
  {
    Serial.println("Detect Operation:" + current_joy_stick->GetCommandStr());

    game_mgr->GetCurrentGame()->HandleCommand(current_joy_stick->CurrentCommand());
    playClickButtonSound(BUZZER_PIN);
  }

  CheckAndCalculateResult();
  game_mgr->GetCurrentGame()->Update();
  game_mgr->CheckNeedStartGame(BUZZER_PIN);
  
  delay(600);
}

void CheckAndCalculateResult()
{
  int val = digitalRead(BUTTON_PIN);
  if (val == HIGH) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
    game_mgr->GetCurrentGame()->CalculateResult();
  }
}


