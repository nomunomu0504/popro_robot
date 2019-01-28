#ifndef OPERATION_H
#define OPERATION_H

#include "Motor.h"

enum Behavior {
  Forward   = 'F',
  Back      = 'B',
  LeftTurn  = 'L'
};

class Operation
{
public:
  Operation(Motor *motor);
  void Run(Behavior cmd);

private:
Motor motor;
};

#endif