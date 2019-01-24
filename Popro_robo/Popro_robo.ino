#include "pinmap.h"
#include "BLE.h"

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
}

char buff[100];
int i = 0;

void loop()
{
  if (millis() % 500 == 0)
    digitalWrite(ST_LED0, !digitalRead(ST_LED0));
  ble.getData();
  if (Serial.available())
  {
    buff[i] = Serial.read();
    if (buff[i] == '\n')
    {
      buff[i] = '\0';
      i = 0;
      ble.setData("12345678901234567890123456789013", buff);
    }
    else
    {
      i++;
    }
  }
}
