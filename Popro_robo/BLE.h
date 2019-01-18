#ifndef BLE_H
#define BLE_H

class BLE {
  public:
    BLE();
    void attachReceiveComplete(void (*func)());
    void getData();
    char cmd[10];
    char handle[10];
    char mes[200];
  private:
    void splitMessage(char str[]);
    void (*Receive)();
    char str[256];
    int p;
};

#endif BLE_H
