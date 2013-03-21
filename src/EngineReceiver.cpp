#include<string>
#include<vector>
#include<cstdio>
#include"EngineReceiver.h"
#include"Point.h"
#include"Ship.h"

namespace BC
{
  
void EngineReceiver::SetInput(int Input)
{
  m_Input = Input;
}

void EngineReceiver::ReceiveHello(std::string &name)
{
  ReceiveKeyword("HELLO");
  ReceiveString(name);
}

void EngineReceiver::ReceivePoint(Point &point)
{
  ReceiveChar("(");
  ReceiveInt(point.x);
  ReceiveChar(",");
  ReceiveInt(point.y);
  ReceiveChar(")");
}

void EngineReceiver::ReceivePlacement(std::vector<Ship> &placement)
{
  ReceiveKeyword("PLACEMENT");
  ReceiveChar("[");
  bool lastShip = false;
  placement.clear();
  while(!lastShip)
  {
    Ship ship;
    char ch;
    ReceiveShip(ship);
    placement.push_back(ship);
    ReceiveChar(",]", ch);
    lastShip = (ch == ']');
  }
}

void EngineReceiver::ReceiveOk()
{
  ReceiveKeyword("OK");
}

void EngineReceiver::ReceiveShip(Ship &ship)
{
  ReceiveChar("(");
  ReceiveString(ship.name);
  ReceiveChar(",");
  ReceivePoint(ship.startPoint);
  ReceiveChar(",");
  ReceivePoint(ship.endPoint);
  ReceiveChar(")");
}

void EngineReceiver::ReceiveInt(int &i)
{
  bool ok = false;
  const int BUF_SIZE = 1024;
  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);
  ssize_t bytesRead = read(m_Input, &buf, BUF_SIZE);
  ok = 0 < bytesRead && bytesRead < BUF_SIZE;
  if (!ok); // throw error
  // string to i
}

void EngineReceiver::ReceiveKeyword(const std::string &keyword)
{
  for(int n=0; n < keyword.size(); ++n)
  {
    ReceiveChar(keyword.substr(n, 1));
  }
}

void EngineReceiver::ReceiveChar(const std::string &chars)
{
  char ch;
  ReceiveChar(chars, ch);
}

void EngineReceiver::ReceiveChar(const std::string &chars, char &ch)
{
  ch = ' ';
  while(isspace(ch))
  {
    ch = ReadChar();
  };
  int n = chars.find(ch);
  if (n  < 0 || n >= chars.size())
  {
    // throw error
  }
}

void EngineReceiver::ReceiveString(std::string &value)
{
  ReceiveChar("\""); 
  value.clear();
  bool finished = false;
  while(!finished)
  {
    char ch = ReadChar();
    if (ch != '"')
    {
      value.push_back(ch);
    }
    else
    {
      finished = true;
    }
  }
}

char EngineReceiver::ReadChar()
{
  char ich;
  if (read(m_Input, &ich, 1) != 1) 
  {
    // throw error
  }
  return (char)ich;
}

void EngineReceiver::Close()
{
  if (close(m_Input) != 0)
  {
    // throw error
  }
}

}
