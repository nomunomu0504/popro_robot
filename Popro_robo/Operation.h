#ifndef OPERATION_H
#define OPERATION_H

enum Behavior {
  Forward   = 'F',
  Back      = 'B',
  LeftTurn  = 'L'
};

class Operation
{
public:
  Operation();
  void Run(Behavior cmd);

private:
};

#endif