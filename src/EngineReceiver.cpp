#include<string>
#include<vector>
#include<cstdio>
#include"EngineReceiver.h"
#include"Point.h"
#include"Ship.h"

namespace BC
{
  
void EngineReceiver::SetInput(FILE * Input)
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
  if (m_Input != NULL)
  {
    if (fscanf(m_Input, "%d", &i) == 1)
    {
      ok = true;
    }
  }
  if (!ok); // throw error
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
  while(!finished);
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
  int ich;
  if (m_Input == NULL || (ich = fgetc(m_Input) == EOF)) 
  {
    // throw error
  }
  return (char)ich;
}

void EngineReceiver::Close()
{
  if (m_Input == NULL || fclose(m_Input) != 0)
  {
    // throw error
  }
}

}
