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
  Serial.begin(115200);
  pinMode(ST_LED0, OUTPUT);
  pinMode(ST_LED1, OUTPUT);
  ble.attachReceiveComplete(Receive);
  GyroSensorInit();
  digitalWrite(ST_LED0, HIGH);
  motor.setBrakeMode(true);
}

void gyroLoop(){
  ble.getData();
}

void loop()
{
  GyroSensorLoop(gyroLoop);
}
