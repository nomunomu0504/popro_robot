#include "pinmap.h"
#include "BLE.h"
#include "GyroSensor.h"

BLE ble;

void Receive()
{
  //Read WV Message
  Serial.println(ble.mes);
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
