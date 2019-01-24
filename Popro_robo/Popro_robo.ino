#include "pinmap.h"
#include "BLE.h"

BLE ble;

void Receive(){
  Serial.println(ble.mes);
}

void setup() {
  ble.attachReceiveComplete();
}

void loop() {
  ble.getData();
}
