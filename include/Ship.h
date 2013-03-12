#ifndef BC_SHIP_H
#define BC_SHIP_H 1

#include <string>
#include "Point.h"

namespace BC
{
struct Ship
{
  std::string name;
  Point startPoint;
  Point endPoint;
};

}

#endif //BC_SHIP_H
