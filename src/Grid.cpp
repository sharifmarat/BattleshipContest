#include <algorithm>
#include "Grid.h"

namespace BC
{

bool Grid::Reset(int sizeX, int sizeY, const std::vector<Ship> &ships)
{
  m_cells.clear();
  m_shipsLeft.clear();

  m_sizeX = sizeX;
  m_sizeY = sizeY;

  m_cells.resize(m_sizeX * m_sizeY);
  for (int i=0; i<ships.size(); ++i)
  {
    const Ship & ship = ships[i];
    const Point & startPoint = ship.startPoint;
    const Point & endPoint = ship.endPoint;
    int xmin = std::min(startPoint.x, endPoint.x);
    int xmax = std::max(startPoint.x, endPoint.x);
    int ymin = std::min(startPoint.y, endPoint.y);
    int ymax = std::max(startPoint.y, endPoint.y);
    for (int x=xmin; x<=xmax; ++x)
    {
      for (int y=ymin; y<=ymax; ++y)
      {
        Cell & cell = this->GetCellByPoint(x, y);
        cell.SetShip(ship.name);
      }
    }
  }
}

bool Grid::AllShipsAreDestroyed() const
{
  std::map<std::string, int>::const_iterator itbeg = m_shipsLeft.begin();
  std::map<std::string, int>::const_iterator itend = m_shipsLeft.end();

  for (std::map<std::string, int>::const_iterator it = itbeg; it != itend; ++it)
  {
    if ((*it).second > 0) return false;
  }
  return true;
}
  
Cell & Grid::GetCellByPoint(int x, int y)
{
  return m_cells[x * m_sizeX + y];
}


Cell & Grid::GetCellByPoint(const Point &point)
{
  return this->GetCellByPoint(point.x, point.y);
}

}
