#include "pinmap.h"
#include "BLE.h"

BLE ble;

void Receive() {
  //Read WV Message
  Serial.println(ble.mes);
}

void setup() {
  ble.attachReceiveComplete(Receive);
}

char buff[100];
int i = 0;

void loop() {
  ble.getData();
  if (Serial.available()) {
    buff[i] = Serial.read();
    if (buff[i] == '\n') {
      buff[i] = '\0';
      i = 0;
      ble.setData("12345678901234567890123456789013",buff);
    } else {
      i++;
    }
  }
}
