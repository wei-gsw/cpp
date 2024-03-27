#pragma once
#include "Worker.h"

class Manager : public Worker
{
public:
    Manager(string n, int id, int num);
    virtual void showInfn();
    virtual string getnumber();
};
