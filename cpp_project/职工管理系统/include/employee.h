#pragma once
#include <string>
#include <iostream>
using namespace std;
#include "Worker.h"

class Employee : public Worker
{   public:
    Employee(string n, int id, int num);
    virtual void showInfn();
    virtual string getnumber();
};  
