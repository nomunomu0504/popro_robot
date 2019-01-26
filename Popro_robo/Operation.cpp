#include "Arduino.h"
#include "pinmap.h"
#include "Operation.h"

Operation::Operation()
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