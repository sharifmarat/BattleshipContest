/* 
 * File:   EngineReceiver.h
 * Author: erikbernsen
 *
 * Created on March 16, 2013, 4:33 PM
 */

#ifndef ENGINERECEIVER_H
#define	ENGINERECEIVER_H

#include<vector>
#include<string>
#include"Point.h"
#include"Ship.h"

namespace BC 
{
  
class EngineReceiver 
{
private:
  int m_Input;
public:
  void SetInput(int Input);
  void ReceiveHello(std::string &name);
  void ReceivePoint(Point &point);
  void ReceivePlacement(std::vector<Ship> &placement);
  void ReceiveOk();
  void Close();
private:
  void ReceiveShip(Ship &ship);
  void ReceiveInt(int &i);
  void ReceiveKeyword(const std::string &keyword);
  void ReceiveString(std::string &value);
  void ReceiveChar(const std::string &ch);
  void ReceiveChar(const std::string &chars, char &ch);
  char ReadChar();
};

}

#endif	/* ENGINERECEIVER_H */

