#pragma once

#include "lcd.h"
#include "game.h"
#include "game_deck_generator.h"

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
    _current_game = new Game(_game_scene, CreateGameData());
    return _current_game;
  }

private:
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