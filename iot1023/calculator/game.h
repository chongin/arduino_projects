#include "Lcd.h"
#include "formula_calculator.h"
#include "game_deck_generator.h"

enum GameState
{
  Inited = 0,
  Started,
  Win,
  Lost,
  Failed
};

class Game
{
public:
  Game()
  {
    _game_state = GameState::Inited;
    lcd_Mgr = new LCDMgr();
    _game_deck_generator = new GameDeckGenerator();
  }

  void Start()
  {
    _game_id++;
    int* one_set = _game_deck_generator->RandomOneSet();
    lcd_Mgr->SetNumbers(one_set, _game_deck_generator->GetCardNumber());
  }

  void Update()
  {
    lcd_Mgr->UpdateView(_formula, GetSeconds());
  }

  void UpdateFormula()
  {
    char ch = lcd_Mgr->GetCurrentSelection();
    Serial.print("Update before: " + _formula);
    Serial.print(",Update Formula: ");
    Serial.print(ch);

    _formula += ch;
    Serial.println(",Update after: " + _formula);

    lcd_Mgr->RemoveCurrentSelection();
    lcd_Mgr->ResetSelection();
  }

  void CalculateResult()
  {
    bool res = false;
    float result = CalcFormula(_formula, res);
    if (res)
    {
      Serial.print("result: ");
      Serial.println(result);
      _formula += "=" + String(result);

      if (result - 24 < 0.0001)
      {
        _game_state = GameState::Win;
      } else {
        _game_state = GameState::Lost;
      }
    }
    else {
       _game_state = GameState::Failed;
    }

    PrintGameInfo();
  }

  void HandleCommand(CommandEnum command)
  {
    switch(command)
    {
      case CommandEnum::Left:
        lcd_Mgr->ChangeShowOption();
        break;
      case CommandEnum::Right:
        //CalculateResult();
        UpdateFormula();
        break;
      case CommandEnum::Up:
        lcd_Mgr->IncreaseOptionIndex();
        break;
      case CommandEnum::Down:
        lcd_Mgr->DecreaseOptionIndex();
        break;
    }
  }

private:
  int GetSeconds()
  {
    return (millis() / 1000) - _seconds;
  }

  String GetGameStateStr()
  {
    String state = "";
    switch(_game_state)
    {
      case GameState::Inited:
        state = "Inited";
        break;
      case GameState::Started:
        state = "Started";
        break;
      case GameState::Win:
        state = "Win";
        break;
      case GameState::Lost:
        state = "Lost";
        break;
      case GameState::Failed:
        state = "Failed";
        break;
    }
    return state;
  }

  void PrintGameInfo()
  {
    Serial.print("game_id: ");
    Serial.print(_game_id);
    Serial.print(",game_state:");
    Serial.println(GetGameStateStr());
  }
private:
  LCDMgr * lcd_Mgr = NULL;
  GameDeckGenerator * _game_deck_generator = NULL;
  //String _formula = "3+4*5-6/3";
  String _formula;
  GameState _game_state;
  int _seconds = millis() / 1000;
  int _game_id = 0;
};