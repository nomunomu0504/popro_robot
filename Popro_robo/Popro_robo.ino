#include "pinmap.h"
#include "BLE.h"
#include "Executer.h"
#include "Operation.h"
#include "motor.h"
#include "MPU6050_DMP6.h"
#include "MPUData.h"

MPU6050 mpu;
BLE ble;
Motor motor;
MPUData mpudata;

void dmpDataReady()
{
  mpudata.mpuInterrupt = true;
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
    mpudata.mpuIntStatus = mpu.getIntStatus();
    mpudata.dmpReady = true;
    mpudata.packetSize = mpu.dmpGetFIFOPacketSize();
  }
}

void Receive()
{
  Executer ex(ble.mes, &motor);
  ex.Run(&mpu, &mpudata);
}

void setup()
{
  Serial.begin(9600);
  pinMode(ST_LED0, OUTPUT);
  pinMode(ST_LED1, OUTPUT);
  ble.attachReceiveComplete(Receive);
  GyroSensorInit();
  Operation op(&motor, &mpu, &mpudata);
  float y;
  do
  {
    y = op.ypr[0];
    for(int i = 0; i < 10; i++)
    {
        op.Gyro();
    }
  } while (fabs(y - op.ypr[0]) > 0.005);
  memcpy(mpudata.ypr, op.ypr, sizeof(op.ypr));
  digitalWrite(ST_LED0, HIGH);
  motor.setBrakeMode(true);
}

void loop()
{
  ble.getData();
}
