#include "pinmap.h"
#include "BLE.h"
#include "Executer.h"
#include "motor.h"
#include "GyroSensor.h"

BLE ble;
Motor motor;

void Receive()
{
  //Read WV Message
  Serial.println(ble.mes);
  Executer ex(ble.mes, &motor);
}

void setup()
{
  pinMode(ST_LED0, OUTPUT);
  ble.attachReceiveComplete(Receive);
  GyroSensorInit();
}

void loop()
{
  ble.getData();
}
