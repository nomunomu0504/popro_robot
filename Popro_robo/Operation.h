#ifndef OPERATION_H
#define OPERATION_H

#include "Motor.h"
#include "MPU6050_DMP6.h"
#include "MPUData.h"

enum Behavior
{
  Forward = 'F',
  Back = 'B',
  LeftTurn = 'L'
};

class Operation
{
public:
  Operation(Motor *motor, MPU6050 *mpu_, MPUData *mpudata_);
  void Run(Behavior cmd);

private:
  Motor *motor;
  MPU6050 *mpu;
  MPUData *mpudata;
  void Gyro();
  float ypr[3];
};

#endif