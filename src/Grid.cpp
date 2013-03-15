#include <algorithm>
#include "Grid.h"

namespace BC
{

bool Grid::Reset(int sizeX, int sizeY, const std::vector<Ship> &ships)
{
  bool result = true;

  m_cells.clear();
  m_shipsLeft.clear();

  if (sizeX < 1 || sizeY < 1)
  {
    result = false;
  }
  else
  {
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_cells.resize(m_sizeX * m_sizeY);
  }

  for (int i=0; result && i<ships.size(); ++i)
  {
    const Ship & ship = ships[i];
    const Point & startPoint = ship.startPoint;
    const Point & endPoint = ship.endPoint;
    int xmin = std::min(startPoint.x, endPoint.x);
    int xmax = std::max(startPoint.x, endPoint.x);
    int ymin = std::min(startPoint.y, endPoint.y);
    int ymax = std::max(startPoint.y, endPoint.y);
    if (xmin < 0 || ymin < 0 || xmax >= m_sizeX || ymax >= m_sizeY)
    {
      result = false;
      break;
    }
    for (int x=xmin; x<=xmax; ++x)
    {
      for (int y=ymin; y<=ymax; ++y)
      {
        Cell & cell = this->GetCellByPoint(x, y);
        if (cell.HasAliveShip())
        {
          result = false;
        }
        else
        {
          cell.SetShip(ship.name);
        }
      }
    }
  }
  return result;
}

bool Grid::Turn(const Point &point, ResultType &resultType, std::string &shipId)
{
  if (point.x < 0 || point.y < 0 || point.x >= m_sizeX || point.y >= m_sizeY) return false;

  Cell &cell = this->GetCellByPoint(point.x, point.y);
  if (!cell.Fire())
  {
    resultType = ResultTypeMiss;
  }
  else
  {
    shipId = cell.shipId;
    m_shipsLeft[shipId] -= 1;
    resultType = (m_shipsLeft[shipId] <= 0) ? ResultTypeDestroy : ResultTypeHit;
  }

  return true;
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
  return m_cells[y * m_sizeX + x];
}


Cell & Grid::GetCellByPoint(const Point &point)
{
  return this->GetCellByPoint(point.x, point.y);
}

}
