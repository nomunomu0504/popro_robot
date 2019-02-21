#include "Arduino.h"
#include "pinmap.h"
#include "MPU6050_DMP6.h"
#include "MPUData.h"
#include "Operation.h"

Operation::Operation(Motor *motor_, MPU6050 *mpu_, MPUData *mpudata_) : motor(motor_), mpu(mpu_), mpudata(mpudata_)
{
    float y;
    do
    {
        y = ypr[0];
        for (int i = 0; i < 10; i++)
        {
            Gyro();
        }
    } while (fabs(y - ypr[0]) > 0.005);
    memcpy(mpudata->ypr, ypr, sizeof(ypr));
}

void Operation::Run(Behavior cmd)
{
    long start = millis();
    switch (cmd)
    {
    case Forward:
        while(millis() - start < 4000){
            Gyro();
            int diff = (mpudata->ypr[0] - ypr[0]) * 100;
            Serial.println(diff);
            motor->write(150 + diff, 150 - diff);
        }
        motor->write(0, 0);
        break;
    case Back:
        while(millis() - start < 4000){
            Gyro();
            int diff = (mpudata->ypr[0] - ypr[0]) * 100;
            Serial.println(diff);
            motor->write(-150 + diff, -150 - diff);
        }
        motor->write(0, 0);
        break;
    case LeftTurn:
        int i = 0;
        while (fabs(mpudata->ypr[0] - ypr[0]) < 1.56)
        {
            Gyro();
            i += (1.57 - fabs(mpudata->ypr[0] - ypr[0])) * 0.6;
            int power = (1.7 - fabs(mpudata->ypr[0] - ypr[0])) * 100 + i;
            motor->write(-power, power);
        }
        motor->write(0, 0);
        break;

    default:
        break;
    }
}

void Operation::Gyro()
{
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