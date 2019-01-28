#include "Arduino.h"
#include "pinmap.h"
#include "Operation.h"

Operation::Operation(Motor *motor_) : motor(motor_)
{
}

void Operation::Run(Behavior cmd)
{
    switch (cmd)
    {
    case Forward:
        motor->write(200, 200);
        delay(2000);
        motor->write(0, 0);
        break;
    case Back:
        motor->write(-200, -200);
        delay(2000);
        motor->write(0, 0);
        break;
    case LeftTurn:
        motor->write(-200, 200);
        delay(1500);
        motor->write(0, 0);
        break;

    default:
        break;
    }
}