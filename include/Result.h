#ifndef BC_RESULT_H
#define BC_RESULT_H 1

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
  std::string shipId;
  bool repeat;
  bool gameFinished;
};

}

#endif //BC_RESULT_H
