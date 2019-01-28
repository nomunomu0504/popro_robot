#ifndef EXECUTER_H
#define EXECUTER_H

#include "Motor.h"

enum Control {
  LOOP = 'W'
};

class Executer
{
public:
  Executer(char code[], Motor *motor);
  void Run();

private:
  bool isControl(char cmd);
  char code[100];
  Motor *motor;
};

#endif