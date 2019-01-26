#include "Arduino.h"
#include "pinmap.h"
#include "Operation.h"
#include "Executer.h"

Executer::Executer(char code_[])
{
    strcpy(code, code_);
}

void Executer::Run()
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
            Operation op;
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