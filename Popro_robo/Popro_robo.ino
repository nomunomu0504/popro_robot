#include "pinmap.h"
#include "BLE.h"

BLE ble;

void Receive(){
  //Read WV Message
  Serial.println(ble.mes);
}

void setup() {
  ble.attachReceiveComplete(Receive);
}

void loop() {
  ble.getData();
}
