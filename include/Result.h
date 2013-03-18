#ifndef BC_RESULT_H
#define BC_RESULT_H 1

#include<string>

namespace BC
{

enum ResultType
{
  ResultTypeMiss,
  ResultTypeHit,
  ResultTypeDestroy
};

enum ResultGame
{
  ResultGameOnGoing,
  ResultGameVictory,
  ResultGameDefeat,
  ResultGameDraw
};

struct Result
{
  ResultType type;
  ResultGame resultGame;
  std::string shipId;
  bool repeat;
};

}

#endif //BC_RESULT_H
