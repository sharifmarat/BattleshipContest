#include "ShipFactory.h"

#include <iostream>
#include <sstream>

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


std::string ShipFactory::CreateNewShipByLength(unsigned newShipLength)
{
  std::pair<std::map<unsigned, unsigned>::iterator, bool> itWithStatus = m_shipLengthCount.insert(std::pair<unsigned, unsigned>(newShipLength, 0));
  std::map<unsigned, unsigned>::iterator &shipLengthWithCount = itWithStatus.first;
  (*shipLengthWithCount).second += 1;
  std::ostringstream oss;
  oss << "ship_" << newShipLength << "_" << (*shipLengthWithCount).second;
  return oss.str();
}


void ShipFactory::Reset()
{
  m_shipLengthCount.clear();
}

}

