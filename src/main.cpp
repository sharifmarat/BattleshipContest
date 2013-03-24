#include <iostream>
#include <fstream>
#include "ParseCmdOptions.h"
#include "Engine.h"
#include "Controller.h"
#include "Exception.h"

using namespace BC;

int main(int argc, char* argv[])
{
  const char pathFirstEngineOption = 'f';
  const char pathSecondEngineOption = 's';
  const char workdirFirstEngineOption = 'w';
  const char workdirSecondEngineOption = 'x';
  const char logOption = 'l';
  
  bool result = EXIT_SUCCESS;

  ParseCmdOptions cmdOpt;
  cmdOpt.setProgramName("BattleshipContest");
  cmdOpt.addDescription("BattleshipContest console protocol - in progress");
  cmdOpt.addOption('h', "gives this help", "Help", false, false);
  cmdOpt.addOption(pathFirstEngineOption, "Path for first engine", "firstEngine", true, true);
  cmdOpt.addOption(pathSecondEngineOption, "Path to second engine", "secondEngine", true, true);
  cmdOpt.addOption(workdirFirstEngineOption, "Path for workdir of first engine", "pathWorkdirFirstEngine", false, true);
  cmdOpt.addOption(workdirSecondEngineOption, "Path for workdir of second engine", "pathWorkdirSecondEngine", false, true);
  cmdOpt.addOption(logOption, "Path for log file", "logFile", false, true);
  
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
    std::string pathFirstEngine;
    std::string pathSecondEngine;
    std::string workdirFirstEngine;
    std::string workdirSecondEngine;
    std::string logFile;
    
    cmdOpt.get(pathFirstEngineOption, pathFirstEngine);
    cmdOpt.get(pathSecondEngineOption, pathSecondEngine);
    
    if (!cmdOpt.get(workdirFirstEngineOption, workdirFirstEngine))
    {
      workdirFirstEngine = "./";
    }
    
    if (!cmdOpt.get(workdirSecondEngineOption, workdirSecondEngine))
    {
      workdirSecondEngine = "./";
    }

    std::ofstream log;
    if (cmdOpt.get(logOption, logFile))
    {
      log.open(logFile.c_str());
    }

    if (log.is_open()) log << "log started" << std::endl;
    
    try
    {
      Engine firstEngine(pathFirstEngine, workdirFirstEngine);
      Engine secondEngine(pathSecondEngine, workdirSecondEngine);
      firstEngine.Start();
      secondEngine.Start();
      
      Controller controller(&firstEngine, &secondEngine);
      controller.PlayGame(Rules());
      result = EXIT_SUCCESS;
    }
    catch (const std::exception &exc)
    {
      if (log.is_open()) log << "catched exception: " << exc.what() << std::endl;
      result = EXIT_FAILURE;
    }

    log.close();
  }

  return result;
}
