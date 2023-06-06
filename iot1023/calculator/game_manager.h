#pragma once

#include "lcd.h"
#include "game.h"
#include "game_deck_generator.h"
#include "sounds.h"

class GameManager
{
public:
  GameManager()
  {
    InitScene();
  }

  ~GameManager()
  {
    delete _game_scene;
    delete _current_game;
    delete _game_deck_generator;
  }

  Game* GetCurrentGame()
  {
    return _current_game;
  }

  Game* CreateNewGame()
  {
    if (_current_game != NULL) {
      delete _current_game;
    }

    _game_scene->ResetScene();
    GameData* game_data = CreateGameData();
    _game_scene->SetNumbers(game_data->Cards, game_data->CarSize);
    _current_game = new Game(_game_scene, game_data);
    Serial.println("Create a new game.");
    return _current_game;
  }

  void CheckNeedStartGame(int buzzerPin)
  {
    if (_current_game->GetGameState() != GameState::Started) {
      PlaySound(buzzerPin);
      
      _current_game = CreateNewGame();
    }
  }

private:
  void PlaySound(int buzzerPin)
  {
    if (_current_game->GetGameState() == GameState::Win) {
      playWinSound(buzzerPin);
      Serial.println("Win");
    } else if (_current_game->GetGameState() == GameState::Lost) {
      playLostSound(buzzerPin);
      Serial.println("Lost");
    } else if (_current_game->GetGameState() == GameState::Failed) {
      playFailSound(buzzerPin);
      Serial.println("Fail");
    }
  }
  void InitScene()
  {
    _game_scene = new LCDMgr();
     _game_deck_generator = new GameDeckGenerator();
  }

  GameData* CreateGameData()
  {
    int* one_car_set = _game_deck_generator->RandomOneSet();
    GameData* game_data = new GameData(one_car_set, _game_deck_generator->GetCardNumber(),
      _game_id++);
    return game_data;
  }

private:
  int _game_id = 0;
  Game* _current_game = NULL;
  LCDMgr* _game_scene= NULL;
  GameDeckGenerator* _game_deck_generator = NULL;
};