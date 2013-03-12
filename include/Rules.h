#ifndef BC_RULES_H
#define BC_RULES_H 1

#include <vector>
#include "Ship.h"

namespace BC
{
struct Rules
{
  Rules();

  int sizeX;
  int sizeY;
  std::vector<Ship> ships;
  bool allowAdjacency;
  bool reportDestroy;
  bool reportNameOnHit;
  bool repeatOnHit;
};
}

#endif //BC_RULES_H
