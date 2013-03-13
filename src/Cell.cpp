#include "Cell.h"

namespace BC
{

Cell::Cell()
  : hasShip(false), wasFired(false), shipId("")
{
}

void Cell::SetShip(const std::string &shipName)
{
  this->shipId = shipName;
  this->hasShip = true;
}

}
