#include "ShipFactory.h"

#include <iostream>
#include <sstream>
#include <Point.h>
#include <Ship.h>

namespace BC
{

ShipFactory & ShipFactory::GetInstance()
{
  static ShipFactory instance;
  return instance;
}


ShipFactory::ShipFactory()
{
}


Ship ShipFactory::CreateNewShipByLength(unsigned newShipLength)
{
  std::pair<std::map<unsigned, unsigned>::iterator, bool> itWithStatus = m_shipLengthCount.insert(std::pair<unsigned, unsigned>(newShipLength, 0));
  std::map<unsigned, unsigned>::iterator &shipLengthWithCount = itWithStatus.first;
  (*shipLengthWithCount).second += 1;
  std::ostringstream oss;
  oss << "ship_" << newShipLength << "_" << (*shipLengthWithCount).second;
  Ship newShip;
  newShip.name = oss.str();
  newShip.startPoint = Point(0, 0);
  newShip.endPoint = Point(newShipLength-1, 0);
  return newShip;
}


void ShipFactory::Reset()
{
  m_shipLengthCount.clear();
}

}

