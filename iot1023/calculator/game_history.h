#pragma once
#include "game.h"

class GameHistory 
{
public:
  GameHistory(): _win(0), _lost(0), _fail(0)
  {
  }
  int GetWinCount() {
    return _win;
  }

  int GetLostCount() {
    return _lost;
  }

  int GetFailCound() {
    return _fail;
  }

  void UpdateHistory(Game* game) {
    if (game->GetGameState() == GameState::Win) {
      AddWin(game);
    } else if (game->GetGameState() == GameState::Lost) {
      AddLost(game);
    } else if (game->GetGameState() == GameState::Failed) {
      AddFail(game);
    }
  }

private:
  //Can save more detail infomation of the game here
  void AddWin(Game* game) {
    _win += 1;
    SaveGameData(game);
  }

  void AddLost(Game* game) {
    _lost += 1;
    SaveGameData(game);
  }

  void AddFail(Game* game) {
    _fail += 1;
    SaveGameData(game);
  }

  void SaveGameData(Game* game) {
    //TBD
  }
private:
  int _win;
  int _lost;
  int _fail;
};