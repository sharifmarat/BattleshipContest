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
  this->wasFired = false;
}

bool Cell::HasAliveShip() const
{
  return this->hasShip && !this->wasFired;
}
  
bool Cell::Fire()
{
  bool result = this->HasAliveShip();
  this->wasFired = true;
  return result;
}

}
