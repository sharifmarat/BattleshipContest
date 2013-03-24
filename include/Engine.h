
#ifndef ENGINE_H
#define	ENGINE_H

#include<vector>
#include<string>
#include<iostream>
#include"Ship.h"
#include"Point.h"
#include"Rules.h"
#include"Result.h"
#include"EngineReceiver.h"
#include"EngineSender.h"

namespace BC
{
    
class Engine
{
private:
  std::string m_path;
  std::string m_workdir;
  std::string m_name;
  EngineReceiver m_fromEngine;
  EngineSender m_toEngine;
  pid_t m_childPid;
  
public:
  Engine(const std::string &path, const std::string &workdir);
  ~Engine() { this->Kill(); }
  void Start();
  void Kill();
  void NewGame(const Rules &rules, std::vector<Ship> &positions);
  void YourTurn(Point &point);
  void ReportResult(const Result &result);
  void OpponentTurns(std::vector<Point> &point);
  void FinishedGame(ResultGame result);
  std::string GetName();
  
};

}

#endif	/* ENGINE_H */

