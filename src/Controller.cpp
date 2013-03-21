#include <vector>
#include"Controller.h"

namespace BC
{
  Controller::Controller(Engine *firstEngine, Engine * secondEngine)
  {
    m_Engines[0] = firstEngine;
    m_Engines[1] = secondEngine;
  }
  
  void Controller::PlayGame(const Rules &rules)
  {
    m_Game.NewGame(rules);
    std::vector<Ship> placement;
    std::vector<int> players;
    players.push_back(Game::FIRST_PLAYER);
    players.push_back(Game::SECOND_PLAYER);
    
    for(int i=0; i<players.size(); ++i)
    {
      m_Engines[i]->NewGame(rules, placement);
      if (!m_Game.SetPosition(players[i], placement))
      {
        // throw error
      }
    }
    
    // Repeat untill m_Game finished
    bool gameFinished = false;
    ResultGame resultGame;
    while(!gameFinished)
    {
   
      // Ask player for points:
      std::vector<Point> turns[2];
      for(int i=0; i<players.size(); ++i) 
      {
        Result result;
        result.repeat = true;
        result.resultGame = ResultGameOnGoing;
        while(result.repeat && result.resultGame == ResultGameOnGoing) 
        {
          Point point;
          m_Engines[i]->YourTurn(point);
          if (!m_Game.Turn(players[i], point, result))
          {
            // throw error
          }
          m_Engines[i]->ReportResult(result);
          turns[i].push_back(point);
          if (result.resultGame != ResultGameOnGoing)
          {
            gameFinished = true;
            resultGame = result.resultGame;
          }
        }
      }
      
      // Report opponent turns to players:
      m_Engines[0]->OpponentTurns(turns[1]);
      m_Engines[1]->OpponentTurns(turns[0]);
    }
    
    for(int i=0; i<players.size(); ++i)
    {
      m_Engines[i]->FinishedGame(resultGame);
    }
  }
}