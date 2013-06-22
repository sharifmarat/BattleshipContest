/* 
 * File:   Controller.h
 * Author: erikbernsen
 *
 * Created on March 18, 2013, 9:41 PM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include"Engine.h"
#include"Game.h"

namespace BC
{
  
class Controller
{
public:
  Controller(Engine *firstEngine, Engine * secondEngine);
  void PlayGame(const Rules &rules);
private:
  Game m_Game;
  Engine * m_Engines[2];
};

}

#endif	/* CONTROLLER_H */

