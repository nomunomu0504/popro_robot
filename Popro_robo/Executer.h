#ifndef EXECUTER_H
#define EXECUTER_H

enum Control {
  LOOP = 'W'
};

class Executer
{
public:
  Executer(char code[]);
  void Run();

private:
  bool isControl(char cmd);
};

#endif