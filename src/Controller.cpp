
#include <vector>

#include"Controller.h"

namespace BC
{
  Controller::Controller(Engine *firstEngine, Engine * secondEngine)
  {
    engines[0] = firstEngine;
    engines[1] = secondEngine;
  }
  
  void Controller::PlayGame(const Rules &rules)
  {
    game.NewGame(rules);
    std::vector<Ship> placement;
    std::vector<int> players;
    players.push_back(Game::FIRST_PLAYER);
    players.push_back(Game::SECOND_PLAYER);
    
    for(int i=0; i<players.size(); ++i)
    {
      engines[i]->NewGame(rules, placement);
      if (!game.SetPosition(players[i], placement))
      {
        // throw error
      }
    }
    
    // Repeat untill game finished
    bool gameFinished = false;
    while(!gameFinished)
    {
   
      // Ask player for points:
      std::vector<Point> turns[2];
      for(int i=0; i<players.size(); ++i) 
      {
        Result result;
        result.repeat = true;
        result.gameFinished = false;
        while(result.repeat && !result.gameFinished) 
        {
          Point point;
          engines[i]->YourTurn(point);
          if (!game.Turn(players[i], point, result))
          {
            // throw error
          }
          engines[i]->ReportResult(result);
          turns[i].push_back(point);
          if (result.gameFinished) 
          {
            gameFinished = true;
          }
        }
      }
      
      // Report opponent turns to players:
      engines[0]->OpponentTurns(turns[1]);
      engines[1]->OpponentTurns(turns[0]);
    }
    
    for(int i=0; i<players.size(); ++i)
    {
      engines[i]->FinishedGame();
    }
  }
}

  
