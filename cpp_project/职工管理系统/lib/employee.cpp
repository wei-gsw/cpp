#include "employee.h"

Employee::Employee(string n, int id, int num)
{
    this->m_name = n;
    this->m_id = id;
    this->m_num = num;
}


void  Employee::showInfn()
{
    cout << "职工编号: " << this->m_id;
    cout << "\t职工姓名: " << this->m_name;
    cout << "\t职工岗位: " << this->getnumber();
    cout << "\t职工的职责: "<< "完成经理给的任务" << endl;
}

string Employee::getnumber()
{
    return string("员工");
}