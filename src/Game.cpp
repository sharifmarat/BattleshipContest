#include <algorithm>
#include "Game.h"
#include "Rules.h"
#include "Logger.h"

namespace BC
{

const int Game::FIRST_PLAYER = 0;
const int Game::SECOND_PLAYER = 1;


bool Game::NewGame(const Rules &rules)
{
  m_rules = rules;
  m_grids.resize(2);
  return true;
}

bool Game::SetPosition(int playerID, const std::vector<Ship> &ships)
{
  if (m_rules.ships.size() != ships.size()) 
  {
    Logger::GetInstance() << "Error in Game::SetPosition, size of ships <> rules" << "\n";
    return false;
  }
  std::vector<Ship> sortedShipsRules(m_rules.ships), sortedShipsPlacement(ships);
  std::sort(sortedShipsRules.begin(), sortedShipsRules.end());
  std::sort(sortedShipsPlacement.begin(), sortedShipsPlacement.end());
  if (!std::includes(sortedShipsRules.begin(), sortedShipsRules.end(),
       sortedShipsPlacement.begin(), sortedShipsPlacement.end()))
  {
    Logger::GetInstance() << "Error in Game::SetPosition, lengths of ships <> rules" << "\n";
    return false;
  }
  return m_grids[playerID].Reset(m_rules.sizeX, m_rules.sizeY, m_rules.allowAdjacency, ships);
}

bool Game::Turn(int playerID, const Point &point, Result &result)
{
  ResultType resultType;
  std::string shipId;
  if (!m_grids[this->Opponent(playerID)].Turn(point, resultType, shipId)) return false;

  switch(resultType)
  {
    case ResultTypeMiss:
      result.type = ResultTypeMiss;
      result.shipId = "";
      result.repeat = false;
      break;
    case ResultTypeHit:
      result.type = ResultTypeHit;
      result.shipId = (m_rules.reportNameOnHit) ? shipId : "";
      result.repeat = m_rules.repeatOnHit;
      break;
    case ResultTypeDestroy:
      result.type = (m_rules.reportDestroy) ? ResultTypeDestroy : ResultTypeHit;
      result.shipId = (m_rules.reportNameOnHit) ? shipId : "";
      result.repeat = m_rules.repeatOnHit;
      break;
    default:
      return false;
  }
  result.resultGame = m_grids[this->Opponent(playerID)].AllShipsAreDestroyed() ? ResultGameVictory : ResultGameOnGoing;
  return true;
}

ResultGame Game::GetResultGame(int playerID) const
{
  const Grid &playerGrid = this->GetGrid(playerID);
  const Grid &opponentGrid = this->GetGrid(this->Opponent(playerID));
  ResultGame resultGame = ResultGameDraw;
  if (playerGrid.AllShipsAreDestroyed() && !opponentGrid.AllShipsAreDestroyed())
  {
    resultGame = ResultGameDefeat;
  }
  else if (!playerGrid.AllShipsAreDestroyed() && opponentGrid.AllShipsAreDestroyed())
  {
    resultGame = ResultGameVictory;
  }
  return resultGame;
}

}
