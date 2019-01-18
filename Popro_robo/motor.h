#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  public:
    Motor();
    void write(int Lp, int Rp);
    void setBrakeMode(bool mode){
      brakeMode = mode;
    }
    
  private:
    //true : HighSide false : LowSide
    bool brakeMode;
};

#endif
