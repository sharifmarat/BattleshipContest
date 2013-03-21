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

  static const int MAX_LEN = 4;

  ShipFactory::GetInstance().Reset();
  for (int len=1; len<=MAX_LEN; ++len)
  {
    for (int i=0; i<(MAX_LEN-len+1); ++i)
    {
      Ship newShip;
      newShip.name = ShipFactory::GetInstance().CreateNewShipByLength(len);
      newShip.startPoint = Point(0, 0);
      newShip.endPoint = Point(len, 0);
      ships.push_back(newShip);
    }
  }
}

}
