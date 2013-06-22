/* 
 * File:   Controller.h
 * Author: erikbernsen
 *
 * Created on March 18, 2013, 9:41 PM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <fstream>
#include"Engine.h"
#include"Game.h"

namespace BC
{
  
class Controller
{
public:
  Controller(Engine *firstEngine, Engine * secondEngine, std::ofstream *log);
  void PlayGame(const Rules &rules);
private:
  Game m_Game;
  Engine * m_Engines[2];
  std::ofstream *m_log;
};

}

#endif	/* CONTROLLER_H */

