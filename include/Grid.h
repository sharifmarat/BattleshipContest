#ifndef BC_GRID_H
#define BC_GRID_H 1

#include <map>
#include <string>
#include <vector>

#include "Cell.h"
#include "Ship.h"
#include "Result.h"

namespace BC
{

class Grid
{
public:
  Grid();

  bool Reset(int sizeX, int sizeY, const std::vector<Ship> &ships);
  bool Turn(const Point &point, Result &result);
  bool AllShipsAreDestroyed() const;
private:
  std::vector<Cell> m_cells;
  std::map<std::string, int> m_shipsLeft;
  int m_sizeX;
  int m_sizeY;
};

}

#endif //BC_GRID_H
