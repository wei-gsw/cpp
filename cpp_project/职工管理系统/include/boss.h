#pragma once
#include "Worker.h"

class Boss : public Worker
{
public:
    Boss(string n, int id, int num);
    virtual void showInfn();
    virtual string getnumber();
};
