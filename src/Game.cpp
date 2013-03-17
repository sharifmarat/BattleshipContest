#include "Game.h"
#include "Rules.h"

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
  return m_grids[playerID].Reset(m_rules.sizeX, m_rules.sizeY, ships);
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

}
