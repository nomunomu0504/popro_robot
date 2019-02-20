#include "Arduino.h"
#include "pinmap.h"
#include "Motor.h"
#include "MPU6050_DMP6.h"
#include "MPUData.h"
#include "Operation.h"
#include "Executer.h"

Executer::Executer(char code_[], Motor *motor_) : motor(motor_)
{
    int i;
    for (i = 0; code_[i] != '\0'; i += 2)
    {
        char hex[3] = {code_[i], code_[i + 1], '\0'};
        code[i / 2] = strtol(hex, NULL, 16);
    }
    code[i / 2] = '\0';
}

void Executer::Run(MPU6050 *mpu, MPUData *mpudata)
{
    for (int i = 0; code[i] != '\0'; i++)
    {
        if (Executer::isControl(code[i]))
        {
            switch (code[i])
            {
            case LOOP:

                break;

            default:
                break;
            }
        }
        else
        {
            Operation op(motor, mpu, mpudata);
            op.Run(code[i]);
        }
    }
}

bool Executer::isControl(char cmd)
{
    switch (cmd)
    {
    case LOOP:
        return true;
        break;
    default:
        return false;
        break;
    }
}