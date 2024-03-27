#pragma once
#include <iostream>
#include <fstream>
#define FILE "emp.txt"
using namespace std;

// 职工抽象类
class Worker
{
public:
    string m_name;
    int m_id;
    int m_num;
    virtual void showInfn() = 0;
    virtual string getnumber() = 0;
    void save();
};
