#include "Rules.h"
#include "Ship.h"
#include "Point.h"
#include "ShipFactory.h"

namespace BC
{

Rules::Rules()
{
  // set default rules
  sizeX = 10;
  sizeY = 10;
  allowAdjacency = false;
  reportDestroy = true;
  reportNameOnHit = false;
  repeatOnHit = true;

  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(5));
  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(4));
  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(3));
  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(3));
  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(2));
  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(2));
  ships.push_back(ShipFactory::GetInstance().CreateNewShipByLength(2));
}

}
