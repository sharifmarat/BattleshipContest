#include<string>
#include<vector>
#include<cstdio>
#include<sstream>
#include"EngineReceiver.h"
#include"Point.h"
#include"Ship.h"
#include"Rules.h"
#include"Result.h"
#include"Exception.h"
#include"Logger.h"

namespace BC
{
  
void EngineReceiver::SetInput(int Input)
{
  m_Input = Input;
}

void EngineReceiver::ReceiveHello()
{
  ReceiveKeyword("HELLO");
}

void EngineReceiver::ReceiveHello(std::string &name)
{
  ReceiveKeyword("HELLO");
  ReceiveAlNumString(name);
}

void EngineReceiver::ReceivePoint(Point &point)
{
  ReceiveInt(point.x);
  ReceiveInt(point.y);
}

void EngineReceiver::ReceivePlacement(std::vector<Ship> &placement)
{
  ReceiveKeyword("PLACEMENT");
  ReceiveShips(placement);
}

void EngineReceiver::ReceiveShips(std::vector<Ship> &ships)
{
  ships.clear();
  int numOfShips;
  ReceiveInt(numOfShips);
  for (int i=0; i<numOfShips; ++i)
  {
    Ship ship;
    ReceiveShip(ship);
    ships.push_back(ship);
  }
}

void EngineReceiver::ReceiveOk()
{
  ReceiveKeyword("OK");
}
  
void EngineReceiver::ReceiveNewGame()
{
  ReceiveKeyword("NEW_GAME");
}

void EngineReceiver::ReceiveShip(Ship &ship)
{
  ReceiveAlNumString(ship.name);
  ReceivePoint(ship.startPoint);
  ReceivePoint(ship.endPoint);
}

void EngineReceiver::ReceiveRules(Rules &rules)
{
  ReceiveKeyword("RULES");

  ReceiveKeyword("GRID_X");
  ReceiveInt(rules.sizeX);

  ReceiveKeyword("GRID_Y");
  ReceiveInt(rules.sizeY);

  ReceiveKeyword("SHIPS");
  ReceiveShips(rules.ships);

  ReceiveKeyword("ALLOW_ADJACENCY");
  ReceiveBool(rules.allowAdjacency);

  ReceiveKeyword("REPORT_DESTROY");
  ReceiveBool(rules.reportDestroy);

  ReceiveKeyword("REPORT_NAME_ON_HIT");
  ReceiveBool(rules.reportNameOnHit);

  ReceiveKeyword("REPEAT_ON_HIT");
  ReceiveBool(rules.repeatOnHit);
}

void EngineReceiver::ReceiveYourTurn()
{
  ReceiveKeyword("YOUR_TURN");
}

void EngineReceiver::ReceiveResult(Result &result)
{
  ReceiveKeyword("RESULT");
  std::string resultStr;
  ReceiveAlNumString(resultStr);
  if (resultStr == "HIT")
  {
    result.type = ResultTypeHit;
  }
  else if (resultStr == "MISS")
  {
    result.type = ResultTypeMiss;
  }
  else if (resultStr == "DESTROY")
  {
    result.type = ResultTypeDestroy;
  }
  else
  {
    throw Exception("Wrong result type");
  }
  ReceiveAlNumString(result.shipId);
}


void EngineReceiver::ReceiveOpponentTurns(std::vector<Point> &points)
{
  points.clear();
  ReceiveKeyword("OPPONENT_TURNS");
  int numOfPoints;
  ReceiveInt(numOfPoints);
  for (int i=0; i<numOfPoints; ++i)
  {
    Point point;
    ReceivePoint(point);
    points.push_back(point);
  }
}

void EngineReceiver::ReceiveGameFinished(ResultGame &resultGame)
{
  ReceiveKeyword("GAME_FINISHED");
  std::string resultGameStr;
  ReceiveAlNumString(resultGameStr);
  if (resultGameStr == "VICTORY")
  {
    resultGame = ResultGameVictory;
  }
  else if (resultGameStr == "DEFEAT")
  {
    resultGame = ResultGameDefeat;
  }
  else if (resultGameStr == "DRAW")
  {
    resultGame = ResultGameDraw;
  }
  else
  {
    throw Exception("Wrong game result type");
  }
}



void EngineReceiver::ReceiveBool(bool &b)
{
  int i;
  ReceiveInt(i);
  b = (bool)i;
}

void EngineReceiver::ReceiveInt(int &i)
{
  std::string str;
  this->ReceiveAlNumString(str);
  std::istringstream iss(str);
  iss >> i;
}

void EngineReceiver::ReceiveKeyword(const std::string &keyword)
{
  std::string rec;
  this->ReceiveAlNumString(rec);
  if (keyword != rec) throw Exception("Unexpected keyword");
}

void EngineReceiver::ReceiveAlNumString(std::string &value)
{
  value.clear();
  bool finished = false;
  while(!finished)
  {
    char ch = ReadChar();
    if (isalnum(ch) || ch == '_' || ch == '\'' || ch == '\"')
    {
      value.push_back(ch);
    }
    else if (value.size() > 0)
    {
      finished = true;
    }
  }
  Logger::GetInstance() << "EngineReceiver::ReceiveAlNumString str = " << value << std::endl;
}


char EngineReceiver::ReadChar()
{
  char ich;
  if (read(m_Input, &ich, 1) != 1) 
  {
    throw Exception("Unable to read char from input");
  }
  return (char)ich;
}

void EngineReceiver::Close()
{
  if (close(m_Input) != 0)
  {
    throw Exception("Unable to close input");
  }
}

}
