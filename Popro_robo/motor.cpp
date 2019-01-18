#include "Arduino.h"
#include "pinmap.h"
#include "motor.h"

Motor::Motor() : brakeMode(false) {
  analogWrite(MD0_PWMF, 0);
  analogWrite(MD0_PWMR, 0);
  analogWrite(MD1_PWMF, 0);
  analogWrite(MD1_PWMR, 0);
}

void Motor::write(int Lp, int Rp) {
  if (Lp > 0) {
    if (brakeMode) {
      analogWrite(MD0_PWMF, 255);
      analogWrite(MD0_PWMR, map(constrain(Lp, 0, 255), 0, 255, 255, 0));
    } else {
      analogWrite(MD0_PWMF, constrain(Lp, 0, 255));
      analogWrite(MD0_PWMR, 0);
    }
  } else if (Lp < 0) {
    if (brakeMode) {
      analogWrite(MD0_PWMF, map(constrain(-Lp, 0, 255), 0, 255, 255, 0));
      analogWrite(MD0_PWMR, 255);
    } else {
      analogWrite(MD0_PWMF, 0);
      analogWrite(MD0_PWMR, constrain(-Lp, 0, 255));
    }
  } else {
    analogWrite(MD0_PWMF, 0);
    analogWrite(MD0_PWMR, 0);
  }

  if (Lp > 0) {
    if (brakeMode) {
      analogWrite(MD1_PWMF, 255);
      analogWrite(MD1_PWMR, map(constrain(Rp, 0, 255), 0, 255, 255, 0));
    } else {
      analogWrite(MD1_PWMF, constrain(Rp, 0, 255));
      analogWrite(MD1_PWMR, 0);
    }
  } else if (Lp < 0) {
    if (brakeMode) {
      analogWrite(MD1_PWMF, map(constrain(-Rp, 0, 255), 0, 255, 255, 0));
      analogWrite(MD1_PWMR, 255);
    } else {
      analogWrite(MD1_PWMF, 0);
      analogWrite(MD1_PWMR, constrain(-Rp, 0, 255));
    }
  } else {
    analogWrite(MD1_PWMF, 0);
    analogWrite(MD1_PWMR, 0);
  }
}
