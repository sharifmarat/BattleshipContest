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

  inline Point GetNorth() const { return Point(this->x, this->y + 1); }
  inline Point GetSouth() const { return Point(this->x, this->y - 1); }
  inline Point GetLeft() const  { return Point(this->x - 1, this->y); }
  inline Point GetRight() const { return Point(this->x + 1, this->y); }

  inline bool operator==(const Point &point) const { return this->x == point.x && this->y == point.y; }
  inline bool operator!=(const Point &point) const { return !this->operator==(point); }
};
}

#endif //BC_POINT_H
