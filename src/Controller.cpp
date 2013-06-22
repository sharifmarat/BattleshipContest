#include <vector>
#include "Logger.h"
#include"Controller.h"
#include"Exception.h"

namespace BC
{
  Controller::Controller(Engine *firstEngine, Engine * secondEngine)
  {
    m_Engines[0] = firstEngine;
    m_Engines[1] = secondEngine;
  }
  
  void Controller::PlayGame(const Rules &rules)
  {
    Logger::GetInstance() << "Controller: game started" << std::endl;
    m_Game.NewGame(rules);
    std::vector<Ship> placement;
    std::vector<int> players;
    players.push_back(Game::FIRST_PLAYER);
    players.push_back(Game::SECOND_PLAYER);
    
    for(int i=0; i<players.size(); ++i)
    {
      Logger::GetInstance() << "Controller: sending new game to player #" << i << std::endl;
      m_Engines[i]->NewGame(rules, placement);
      if (!m_Game.SetPosition(players[i], placement))
      {
        throw Exception((std::string("unable to set positions for engine ") + m_Engines[i]->GetName()).c_str());
      }
      Logger::GetInstance() << m_Engines[i]->GetName() << " placement: " << "\n" << m_Game.GetGrid(i) << std::endl;
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
            throw Exception("Unable to do a turn");
          }
          m_Engines[i]->ReportResult(result);
          turns[i].push_back(point);
          if (result.resultGame != ResultGameOnGoing)
          {
            gameFinished = true;
            resultGame = result.resultGame;
          }
        }
        Logger::GetInstance() << m_Engines[i]->GetName() << " fired at opponent: " << "\n" << m_Game.GetGrid(m_Game.Opponent(i)) << std::endl;
      }

      // Report opponent turns to players:
      m_Engines[0]->OpponentTurns(turns[1]);
      m_Engines[1]->OpponentTurns(turns[0]);
    }

    Logger::GetInstance() << "Game finished, result = " << resultGame << std::endl;
    
    for(int i=0; i<players.size(); ++i)
    {
      m_Engines[i]->FinishedGame(resultGame);
    }
  }
}
