#include "Arduino.h"
#include "pinmap.h"
#include "Executer.h"

Executer::Executer(char code[])
{
}

void Executer::Run()
{
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