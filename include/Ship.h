#ifndef BC_SHIP_H
#define BC_SHIP_H 1

#include <string>
#include <vector>
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
    return (this->IsHorizontal() ? abs(startPoint.x - endPoint.x) : abs(startPoint.y - endPoint.y)) + 1;
  }

  inline bool operator<(const Ship &rhs) const
  {
    return this->Length() < rhs.Length();
  }

  inline unsigned GetAllPoints(std::vector<Point> &points) const
  {
    points.resize(this->Length());
    if (this->IsHorizontal())
    {
      for (int x=startPoint.x; x<=endPoint.x; ++x) points[startPoint.x-x] = Point(x, startPoint.y);
    }
    else
    {
      for (int y=startPoint.y; y<=endPoint.y; ++y) points[startPoint.y-y] = Point(startPoint.x, y);
    }
    return points.size();
  }

private:
  inline bool IsHorizontal() const
  {
    return (startPoint.x != endPoint.x) ? true : false;
  }
};

}

#endif //BC_SHIP_H
