#ifndef EXECUTER_H
#define EXECUTER_H

#include "Motor.h"
#include "MPU6050_DMP6.h"
#include "MPUData.h"

enum Control
{
  LOOP = 'W'
};

class Executer
{
public:
  Executer(char code[], Motor *motor);
  void Run(MPU6050 *mpu, MPUData *mpudata);

private:
  bool isControl(char cmd);
  char code[100];
  Motor *motor;
};

#endif