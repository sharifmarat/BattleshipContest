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
#include"Result.h"

namespace BC 
{
class Rules;

class EngineReceiver 
{
private:
  int m_Input;
public:
  void SetInput(int Input);
  void ReceiveHello();
  void ReceiveHello(std::string &name);
  void ReceivePoint(Point &point);
  void ReceivePlacement(std::vector<Ship> &placement);
  void ReceiveRules(Rules &rules);
  void ReceiveOk();
  void ReceiveNewGame();
  void ReceiveYourTurn();
  void ReceiveResult(Result &result);
  void ReceiveOpponentTurns(std::vector<Point> &points);
  void ReceiveGameFinished(ResultGame &resultGame);
  void Close();
private:
  void ReceiveShip(Ship &ship);
  void ReceiveShips(std::vector<Ship> &ships);
  void ReceiveInt(int &i);
  void ReceiveBool(bool &b);
  void ReceiveKeyword(const std::string &keyword);
  void ReceiveAlNumString(std::string &value);
  char ReadChar();
};

}

#endif	/* ENGINERECEIVER_H */

