#ifndef BC_POINT_H
#define BC_POINT_H 1

namespace BC
{
struct Point
{
  int x;
  int y;

  Point() : x(0), y(0) { }
  Point(int x, int y) : x(x), y(y) { }
};
}

#endif //BC_POINT_H
