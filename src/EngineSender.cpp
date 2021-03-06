#include<string>
#include<sstream>
#include"EngineSender.h"
#include"Result.h"
#include"Exception.h"
#include"Logger.h"

namespace BC
{

static std::string ToString(const Point &point) {
  std::ostringstream convert;
  convert << "(" << point.x << "," << point.y << ")";
  return convert.str();
}

static std::string ToString(const Ship &ship)
{
  std::ostringstream convert;
  convert << "(\"" << ship.name << "\"" << ToString(ship.startPoint) << "," << ToString(ship.endPoint) << ")";
  return convert.str();
}

static std::string ToString(const Result &result)
{
  std::ostringstream convert;
  switch(result.type) 
  {
    case(ResultTypeHit):
      convert << "HIT";
      break;
    case(ResultTypeMiss):
      convert << "MISS";
      break;
    case(ResultTypeDestroy):
      convert << "DESTROY";
      break;
  }
  convert << " \"" << result.shipId << "\"";
  return convert.str();
}

static std::string ToString(bool value)
{
  return value ? "1" : "0";
}

template<class T> std::string ToString(const std::vector<T> &vec)
{
  std::ostringstream convert;
  convert << vec.size() << ":[";
  for(int i=0; i<vec.size(); ++i)
  {
    convert << ToString(vec[i]);
    if (i+1 < vec.size()) 
    {
      convert << ",";
    }
  }
  convert << "]";
  return convert.str();
}

static std::string ToString(const Rules &rules)
{
  std::stringstream convert;
  convert << "GRID_X = " << rules.sizeX << std::endl;
  convert << "GRID_Y = " << rules.sizeY << std::endl;
  convert << "SHIPS = " << ToString(rules.ships) << std::endl;
  convert << "ALLOW_ADJACENCY = " << ToString(rules.allowAdjacency) << std::endl;
  convert << "REPORT_DESTROY = " << ToString(rules.reportDestroy) << std::endl;
  convert << "REPORT_NAME_ON_HIT = " << ToString(rules.reportNameOnHit) << std::endl;
  convert << "REPEAT_ON_HIT = " << ToString(rules.repeatOnHit) << std::endl;
  return convert.str();
}

void EngineSender::SetOutput(int Output)
{
  m_Output = Output;
}

void EngineSender::SendHello()
{
  SendString("HELLO\n");
}

void EngineSender::SendHello(const std::string &name)
{
  SendString(std::string("HELLO ") + name + "\n");
}

void EngineSender::SendOK()
{
  SendString("OK\n");
}

void EngineSender::SendNewGame()
{
  SendString("NEW_GAME\n");
}

void EngineSender::SendRules(const Rules &rules)
{
  SendString("RULES\n" + ToString(rules) + "\n");
}

void EngineSender::SendPlacement(const std::vector<Ship> &placement)
{
  SendString("PLACEMENT\n" + ToString(placement) + "\n");
}

void EngineSender::SendYourTurn()
{
  SendString("YOUR_TURN\n");
}

void EngineSender::SendPoint(const Point &point)
{
  SendString(ToString(point));
}

void EngineSender::SendOpponentTurns(const std::vector<Point> &points)
{
  SendString("OPPONENT_TURNS\n" + ToString(points) + "\n");
}

void EngineSender::SendResult(const Result &result)
{
  SendString("RESULT\n" + ToString(result) + "\n");
}

void EngineSender::SendGameFinished(ResultGame result)
{
  std::string resultString;
  switch(result)
  {
    case(ResultGameVictory):
      resultString = "VICTORY";
      break;
    case(ResultGameDefeat):
      resultString = "DEFEAT";
      break;
    case(ResultGameDraw):
      resultString = "DRAW";
      break;
    default:
      throw Exception("Incorrect game result");
      break;
  }
  SendString("GAME_FINISHED " + resultString + "\n");
}

void EngineSender::SendError()
{
  SendString("ERROR\n");
}

void EngineSender::SendString(const std::string &str)
{
  Logger::GetInstance() << "EngineSender::SendString str = " << str << std::endl;
  if (dprintf(m_Output, "%s", str.c_str()) < 1)
  {
    throw Exception("Unable to send strin");
  }
  
}

void EngineSender::Close()
{
  if (close(m_Output) != 0)
  {
    throw Exception("Unable to close output");
  }
}

}
