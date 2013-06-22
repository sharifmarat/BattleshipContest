#ifndef BC_CELL_H
#define BC_CELL_H 1

#include <string>


namespace BC
{

struct Logger;

struct Cell
{
  bool hasShip;
  bool wasFired;
  std::string shipId;

  Cell();

  void SetShip(const std::string &shipName);

  bool HasAliveShip() const;

  // returns true if cell has still alive ship
  bool Fire();

  friend Logger &operator<<(Logger &log, const Cell &cell);
};

}


#endif //BC_CELL_H
