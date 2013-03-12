#include "Rules.h"
#include "Ship.h"
#include "Point.h"
#include "ShipFactory.h"

namespace BC
{

Rules::Rules()
{
  // set default rules
  int sizeX = 10;
  int sizeY = 10;
  bool allowAdjacency = false;
  bool reportDestroy = true;
  bool reportNameOnHit = false;
  bool repeatOnHit = true;

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

  std::vector<Ship> ships;
}

}
