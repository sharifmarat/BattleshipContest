
#include <vector>
#include <cstdio>
#include <cstddef>
#include "Result.h"
#include "Grid.h"
#include "Ship.h"
#include "Rules.h"
#include "Engine.h"

namespace BC
{
 
  static pid_t runExecutable(const std::string &workdir, const std::string &path, FILE * &parentToChild, FILE * &childToParent)
  {
    const int pipeRead = 0;
    const int pipeWrite = 1;
    const int fdStdIn = 0;
    const int fdStdOut = 1;
    
    int fdParentToChild[2];
    int fdChildToParent[2];
    int fdOldStdIn;
    int fdOldStdOut;

    pid_t childPid;
    
    // Create pipes for communication between parent and child:
    pipe(fdParentToChild); 
    pipe(fdChildToParent); 

    // Save current stdin and stdout:
    fdOldStdIn = dup(fdStdIn); 
    fdOldStdOut = dup(fdStdOut); 

    close(fdStdIn);
    close(fdStdOut);

    // Make read end of pipe as stdin and write end as stdout
    dup2(fdParentToChild[pipeRead], fdStdIn); 
    dup2(fdChildToParent[pipeWrite],fdStdOut); 

    childPid = fork();
    
    if(childPid == 0)
    {
      // In child process.
      
      // No longer need pipes in child since stdin and stdout are already connected.
      close(fdParentToChild[pipeRead]); 
      close(fdParentToChild[pipeWrite]);
      close(fdChildToParent[pipeRead]);
      close(fdChildToParent[pipeWrite]);

      chdir(workdir.c_str());
      execv(path.c_str(), NULL);
    }
    else
    {
      // In parent process
      
      // Restore the original STDIN/STDOUT of parent
      close(fdStdIn); 
      close(fdStdOut);
      dup2(fdOldStdIn, fdStdIn);
      dup2(fdOldStdOut, fdStdOut);

      // These are used by the child:
      close(fdParentToChild[pipeRead]);
      close(fdChildToParent[pipeWrite]);

      parentToChild = fdopen(fdParentToChild[pipeWrite], "w");
      childToParent = fdopen(fdChildToParent[pipeRead], "r");
    }
    return childPid;
  }
  
  Engine::Engine(const std::string &path, const std::string &workdir)
  {
    m_path = path;
    m_workdir = workdir;
  }
  
  void Engine::Start()
  {
    
    {
      FILE * pipeToEngine;
      FILE * pipeFromEngine;
    
      m_childPid = runExecutable(m_workdir, m_path, pipeToEngine, pipeFromEngine);
      
      m_toEngine.SetOutput(pipeToEngine);
      m_fromEngine.SetInput(pipeFromEngine);
    }
    
    m_toEngine.SendHello();
    m_fromEngine.ReceiveHello(m_name);
  }
  
  void Engine::Kill()
  {
    m_toEngine.SendError();
    m_toEngine.Close();
    m_fromEngine.Close();
  }
  
  void Engine::NewGame(const Rules &rules, std::vector<Ship> placement)
  {
    m_toEngine.SendRules(rules);
    m_toEngine.SendNewGame();
    m_fromEngine.ReceivePlacement(placement);
  }
  
  void Engine::YourTurn(Point &point)
  {
    m_toEngine.SendYourTurn();
    m_fromEngine.ReceivePoint(point);
  }
  
  void Engine::ReportResult(const Result &result)
  {
    m_toEngine.SendResult(result);
    m_fromEngine.ReceiveOk();
  }
  
  void Engine::OpponentTurns(std::vector<Point> &points)
  {
    m_toEngine.SendOpponentTurns(points);
    m_fromEngine.ReceiveOk();
  }
    
  
  void Engine::FinishedGame()
  {
    m_toEngine.SendGameFinished();
    m_fromEngine.ReceiveOk();
  }
  
  std::string Engine::GetName()
  {
    return m_name;
  }
    


};

