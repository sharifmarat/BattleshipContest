#include <iostream>
#include "ParseCmdOptions.h"
#include "Game.h"

using namespace BC;

int main(int argc, char* argv[])
{
  bool result = EXIT_SUCCESS;

  ParseCmdOptions cmdOpt;
  cmdOpt.setProgramName("BattleshipContest");
  cmdOpt.addDescription("BattleshipContest console protocol - in progress");
  cmdOpt.addOption('h', "gives this help", "Help", false, false);
  
  std::string errMsg, helpMsg;
  cmdOpt.getInfo(helpMsg);

  if (!cmdOpt.processCmdOptions(argc, argv, errMsg))
  {
    std::cerr << "\n" << errMsg << "\n\n";
    std::cerr << helpMsg << std::endl;
    result = EXIT_FAILURE;
  }
  else if (cmdOpt.checkOption('h'))
  {
    std::cout << helpMsg << std::endl;
    result = EXIT_SUCCESS;
  }
  else
  {
    // TODO
    std::cout << helpMsg << std::endl;
    result = EXIT_SUCCESS;
  }

  return result;
}
