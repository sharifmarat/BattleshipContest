#include <iostream>
#include <fstream>
#include <string>
#include "EngineReceiver.h"
#include "EngineSender.h"
#include "Rules.h"


using namespace BC;

int main(int argc, char **argv)
{
  Rules rules;
  Result result;

  EngineReceiver receiver;
  receiver.SetInput(STDIN_FILENO);
  EngineSender sender;
  sender.SetOutput(STDOUT_FILENO);
  
  receiver.ReceiveHello();
  sender.SendHello("maratAlgo");

  receiver.ReceiveRules(rules);
  sender.SendOK();

  receiver.ReceiveNewGame();
  sender.SendPlacement(rules.ships);

  receiver.ReceiveYourTurn();
  sender.SendPoint(Point());
  receiver.ReceiveResult(result);
  sender.SendOK();

  std::vector<Point> points;
  receiver.ReceiveOpponentTurns(points);
  sender.SendOK();

  ResultGame resultGame;
  receiver.ReceiveGameFinished(resultGame);
  sender.SendOK();

  status = EXIT_SUCCESS;

  return status;
}

