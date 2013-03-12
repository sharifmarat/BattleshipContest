#ifndef BC_CELL_H
#define BC_CELL_H 1

#include <string>

namespace BC
{
struct Cell
{
  bool hasShip;
  bool wasFired;
  std::string shipId;
};

}


#endif //BC_CELL_H
