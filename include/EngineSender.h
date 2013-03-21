/* 
 * File:   EngineSender.h
 * Author: erikbernsen
 *
 * Created on March 16, 2013, 4:30 PM
 */

#ifndef ENGINESENDER_H
#define	ENGINESENDER_H

#include<cstdio>
#include"Point.h"
#include"Result.h"
#include"Rules.h"

namespace BC
{
  
// Class for receiving data from engine.
class EngineSender
{
private:
  int m_Output;
public:
  void SetOutput(int Output);
  void SendHello();
  void SendNewGame();
  void SendRules(const Rules &rules);
  void SendYourTurn();
  void SendOpponentTurns(const std::vector<Point> &points);
  void SendResult(const Result &result);
  void SendGameFinished(ResultGame result);\
  void SendError();
  void Close();
private:
  void SendString(const std::string &str);
  
};
}
#endif	/* ENGINESENDER_H */

