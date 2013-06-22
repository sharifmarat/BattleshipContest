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
    for (int i=0; i<this->Length(); ++i)
    {
      if (this->IsHorizontal())
      {
        points[i] = Point(startPoint.x + i * (startPoint.x > endPoint.x ? -1 : 1), startPoint.y);
      }
      else               
      {
        points[i] = Point(startPoint.x, startPoint.y + i * (startPoint.y > endPoint.y ? -1 : 1));
      }
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
