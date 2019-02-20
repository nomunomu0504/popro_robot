#include "Arduino.h"
#include "pinmap.h"
#include "MPU6050_DMP6.h"
#include "MPUData.h"
#include "Operation.h"

Operation::Operation(Motor *motor_, MPU6050 *mpu_, MPUData *mpudata_) : motor(motor_), mpu(mpu_), mpudata(mpudata_)
{
}

void Operation::Run(Behavior cmd)
{
    switch (cmd)
    {
    case Forward:
        motor->write(200, 200);
        delay(2000);
        motor->write(0, 0);
        break;
    case Back:
        motor->write(-200, -200);
        delay(2000);
        motor->write(0, 0);
        break;
    case LeftTurn:
        Gyro();
        float y = ypr[0];
        while(ypr[0] - y < 1.57){
            Gyro();
            Serial.println(ypr[0]);
        }
        break;

    default:
        break;
    }
}

void Operation::Gyro(){
    Quaternion q;
    VectorFloat gravity;

    while (!mpudata->mpuInterrupt && mpudata->fifoCount < mpudata->packetSize)
    {

    }
    mpudata->mpuInterrupt = false;
    mpudata->mpuIntStatus = mpu->getIntStatus();
    mpudata->fifoCount = mpu->getFIFOCount();
    if ((mpudata->mpuIntStatus & 0x10) || mpudata->fifoCount == 1024)
    {
        mpu->resetFIFO();
    }
    else if (mpudata->mpuIntStatus & 0x02)
    {
        while (mpudata->fifoCount < mpudata->packetSize)
            mpudata->fifoCount = mpu->getFIFOCount();
        mpu->getFIFOBytes(mpudata->fifoBuffer, mpudata->packetSize);
        mpudata->fifoCount -= mpudata->packetSize;
        mpu->dmpGetQuaternion(&q, mpudata->fifoBuffer);
        mpu->dmpGetGravity(&gravity, &q);
        mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
    }
}