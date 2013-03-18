
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
    
    // Repeat untill game finished
    bool gameFinished = false;
    Result result[2];
    while(!gameFinished)
    {
   
      // Ask player for points:
      std::vector<Point> turns[2];
      result[1].repeat = true;
      result[2].repeat = true;
      
      while(result[0].repeat || result[1].repeat)
      {
<<<<<<< HEAD
        Result result;
        result.repeat = true;
        result.resultGame = ResultGameOnGoing;
        while(result.repeat && result.resultGame == ResultGameOnGoing) 
        {
          Point point;
          engines[i]->YourTurn(point);
          if (!game.Turn(players[i], point, result))
          {
            // throw error
          }
          engines[i]->ReportResult(result);
          turns[i].push_back(point);
          if (result.resultGame != ResultGameOnGoing)
=======
        Point point[2];
        for(int i=0; i<players.size(); ++i) 
        {
          if (result[i].repeat)
>>>>>>> Implemented simple engine controller (not tested)
          {
            m_Engines[i]->YourTurn(point[i]);
          }
        
          m_Game.Turn(players[i], point[i], result[i]);          
        }
        m_Game.MakeResultsConsistent(result[0], result[1]);
      }
      
      m_Engines[0]->OpponentTurns(turns[1]);
      m_Engines[1]->OpponentTurns(turns[0]);
      
      gameFinished = (result[0].resultGame != ResultGameOnGoing);
    }   
      
    for(int i=0; i<players.size(); ++i)
    {
      m_Engines[i]->FinishedGame(result[i].resultGame);
    }
  }
}

  
