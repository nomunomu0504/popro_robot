#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;

bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

volatile bool mpuInterrupt = false;

Quaternion q;
VectorFloat gravity;
float ypr[3];

void dmpDataReady()
{
    mpuInterrupt = true;
}

void GyroSensorInit()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    Wire.setClock(400000);
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    mpu.initialize();
    pinMode(MPU_INT, INPUT);
    uint8_t devStatus = mpu.dmpInitialize();
    //[-2307,-2306] --> [-5,11]	[1201,1201] --> [0,1]	[2109,2110] --> [16377,16393]	[13,14] --> [-1,3]	[19,20] --> [0,2]	[21,22] --> [-2,1]
    mpu.setXAccelOffset(-2307);
    mpu.setYAccelOffset(1201);
    mpu.setZAccelOffset(2110);
    mpu.setXGyroOffset(14);
    mpu.setYGyroOffset(19);
    mpu.setZGyroOffset(22);
    if (devStatus == 0)
    {
        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(MPU_INT), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
}

void GyroSensorLoop(void (*loopFunc)())
{
    while (!mpuInterrupt && fifoCount < packetSize)
    {
        loopFunc();   
    }
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    if ((mpuIntStatus & 0x10) || fifoCount == 1024)
    {
        mpu.resetFIFO();
    }
    else if (mpuIntStatus & 0x02)
    {
        while (fifoCount < packetSize)
            fifoCount = mpu.getFIFOCount();
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    }
}