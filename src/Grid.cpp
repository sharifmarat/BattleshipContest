#include <algorithm>
#include "Grid.h"

namespace BC
{

Grid::Grid()
  : m_sizeX(-1), m_sizeY(-1)
{
}

bool Grid::Reset(int sizeX, int sizeY, bool allowAdj, const std::vector<Ship> &ships)
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
    m_shipsLeft[ship.name] = ship.Length();

    std::vector<Point> points;
    unsigned nPoints = ship.GetAllPoints(points);
    for (std::vector<Point>::const_iterator pp = points.begin(); pp != points.end() && result; ++pp)
    {
      if (!this->IsValidPoint(*pp))
      {
        result = false;
        break;
      }
      Cell & cell = this->GetCellByPoint(*pp);
      if (cell.HasAliveShip())
      {
        result = false;
        break;
      }
      if (!allowAdj)
      {
        std::vector<Cell> neighbors;
        this->GetNeighborCells(*pp, neighbors);
        for (std::vector<Cell>::const_iterator nn = neighbors.begin(); nn != neighbors.end(); ++nn)
        {
          if (nn->HasAliveShip() && nn->shipId != ship.name)
          {
            result = false;
            break;
          }
        }
      }
      cell.SetShip(ship.name);
    }
  }

  return result;
}

bool Grid::Turn(const Point &point, ResultType &resultType, std::string &shipId)
{
  if (!this->IsValidPoint(point)) return false;

  Cell &cell = this->GetCellByPoint(point);
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
  
Cell & Grid::GetCellByPoint(const Point &point)
{
  return m_cells[point.y * m_sizeX + point.x];
  //return const_cast<Cell&>(static_cast<const Grid*>(this)->GetCellByPoint());
}

const Cell & Grid::GetCellByPoint(const Point &point) const
{
  return m_cells[point.y * m_sizeX + point.x];
}

int Grid::GetNeighborCells(const Point &point, std::vector<Cell> &neighbors) const
{
  neighbors.clear();
  if (this->IsValidPoint(point.GetLeft())) neighbors.push_back(this->GetCellByPoint(point.GetLeft()));
  if (this->IsValidPoint(point.GetNorth())) neighbors.push_back(this->GetCellByPoint(point.GetNorth()));
  if (this->IsValidPoint(point.GetRight())) neighbors.push_back(this->GetCellByPoint(point.GetRight()));
  if (this->IsValidPoint(point.GetSouth())) neighbors.push_back(this->GetCellByPoint(point.GetSouth()));

  return 0;
}

bool Grid::IsValidPoint(const Point &point) const
{
  return (point.x >= 0 && point.y >= 0 && point.x < m_sizeX && point.y < m_sizeY) ? true : false;
}

}
