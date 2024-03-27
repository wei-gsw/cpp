#pragma once // 防止头文件重复包含
#include <iostream>
#include <string>
#include "Worker.h"
using namespace std;

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	// 显示菜单
	void show_man();
	// 退出
	void eixt_man();
	// 在职员工数
	int m_Empnum;
	// 职工数组指针
	Worker **m_array;
	// 添加新职工
	void addemploy();
	// 保存到txt到文件
	void save();
	// 判断是否为空
	bool isempty;
	// 显示职工
	void show_emp();
	// 显示员工个数
	int getnum();
	// 初始化员工
	void initemp();
	// 删除员工
	void delemp();
	// 判断id是否找到,找到返回下标否则-1
	int isfand(int id);
	// 修改职工
	void modemp();
	// 查找职工
	void findemp();
	// sort employee
	void sortemp();
	// cleanfile'
	void cleanfile();
};
