#include "Arduino.h"
#include "pinmap.h"
#include "Operation.h"

Operation::Operation(Motor motor_) : motor(motor_)
{
}

void Operation::Run(Behavior cmd)
{
    switch (cmd)
    {
    case Forward:

        break;
    case Back:

        break;
    case LeftTurn:

        break;

    default:
        break;
    }
}