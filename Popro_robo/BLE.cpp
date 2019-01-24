#include "Arduino.h"
#include "pinmap.h"
#include "BLE.h"

BLE::BLE() : p(0), Receive(NULL) {
  Serial1.begin(115200);
  pinMode(CMD_MLDP, OUTPUT);
  digitalWrite(CMD_MLDP, HIGH);
}

void BLE::getData() {
  if (Serial1.available()) {
    byte data = Serial1.read();
    if (data == '.') {
      str[p] = '\0';
      p = 0;
      BLE::splitMessage(str);
      for (int i = 0; i < 256; i++) str[i] = 0;

      if (Receive != NULL)
        BLE::Receive();
    }
    else {
      str[p] = data;
      p++;
    }
  }
}

void BLE::attachReceiveComplete(void (*func)()) {
  BLE::Receive = func;
}

void BLE::splitMessage(char str[]) {
  int j = 0;
  int tmp;
  char c[10] = "\0";
  char h[10] = "\0";
  char m[200] = "\0";
  for (; !(str[j] == 'W' && str[j + 1] == 'V'); j++)
    if (str[j] == '\0') return;
  tmp = j;
  for (j--; str[j] != ','; j++) {
    c[j - tmp] = str[j];
  }
  c[j++] = '\0';
  tmp = j;
  for (; str[j] != ','; j++) {
    h[j - tmp] = str[j];
  }
  h[j++ - tmp] = '\0';
  tmp = j;
  for (; str[j] != '\0'; j++) {
    m[j - tmp] = str[j];
  }
  m[j - tmp] = '\0';
  strcpy(cmd, c);
  strcpy(handle, h);
  strcpy(mes, m);
}
