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

  inline unsigned Length() const
  {
    return (startPoint.x != endPoint.x ? abs(startPoint.x - endPoint.x) : abs(startPoint.y - endPoint.y)) + 1;
  }

  inline bool operator<(const Ship &rhs) const
  {
    return this->Length() < rhs.Length();
  }
};

}

#endif //BC_SHIP_H
