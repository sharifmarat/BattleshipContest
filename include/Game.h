#ifndef BC_GAME_H
#define BC_GAME_H 1

#include "Rules.h"
#include "Result.h"
#include "Grid.h"

namespace BC
{

class Game
{
public:
  static const int FIRST_PLAYER;
  static const int SECOND_PLAYER;
public:
  bool NewGame(const Rules &rules);
  bool SetPosition(int playerID, const std::vector<Ship> &ships);
  bool Turn(int playerID, const Point &point, Result &result);
  void MakeResultsConsistent(Result &result1, Result &result2) const;
protected:
  inline int Opponent(int playerID) const { return (playerID == FIRST_PLAYER) ? SECOND_PLAYER : FIRST_PLAYER; }
private:
  Rules m_rules;
  std::vector<Grid> m_grids;
};

}

#endif //BC_GAME_H
