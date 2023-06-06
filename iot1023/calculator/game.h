#include "Lcd.h"
#include "formula_calculator.h"

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
  }

  void Start()
  {
    _game_id++;
  }

  void Update()
  {
    lcd_Mgr->UpdateView(_formula, GetSeconds());
  }

  void UpdateFormula()
  {
    //_formula += ch;
  }

  void IsGameOver()
  {
    
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
  String _formula = "3+4*5-6/3";
  GameState _game_state;
  int _seconds = millis() / 1000;
  int _game_id = 0;
};