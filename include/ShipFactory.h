#ifndef BC_SHIP_FACTORY_H
#define BC_SHIP_FACTORY_H 1

#include <string>
#include <map>

namespace BC
{

class ShipFactory
{
public:
  static ShipFactory & GetInstance();
  std::string CreateNewShipByLength(unsigned length);
  void Reset();
private:
  ShipFactory();
  ShipFactory(ShipFactory const &);
  ShipFactory & operator=(ShipFactory const &);
private:
  std::map<unsigned, unsigned> m_shipLengthCount; // keeps track how many ships have been created with certain length
};

}

#endif //BC_SHIP_FACTORY_H
