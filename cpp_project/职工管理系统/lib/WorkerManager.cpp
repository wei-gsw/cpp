#include <iostream>
#include "WorkerManager.h"
#include "employee.h"
#include "Worker.h"
#include "boss.h"
#include "manager.h"
using namespace std;

WorkerManager ::WorkerManager()
{
	// 读文件
	ifstream ifs;
	ifs.open(FILE, ios::in);
	// 判断是否为空，为空初始化
	if (!ifs.is_open())
	{
		cout << "empty..." << endl;
		this->m_array = NULL;
		this->m_Empnum = 0;
		this->isempty = true;
		ifs.close();
		return;
	}
	// 判断是否有数据，没有初始化
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "no data..." << endl;
		this->m_array = NULL;
		this->m_Empnum = 0;
		this->isempty = true;
		ifs.close();
		return;
	}
	// 有数据取出来
	int num = this->getnum();
	this->m_Empnum = num;

	// 开辟新空间
	this->m_array = new Worker *[this->m_Empnum];
	// 把数据放入新空间
	this->initemp();
}

WorkerManager::~WorkerManager() {}

void WorkerManager::show_man()
{
	cout << "----------" << endl;
	cout << "职工管理系统" << endl;
	cout << "0.退出系统" << endl;
	cout << "1.增加职员" << endl;
	cout << "2.显示信息" << endl;
	cout << "3.删除职工" << endl;
	cout << "4.修改信息" << endl;
	cout << "5.查找职工" << endl;
	cout << "6.排序信息" << endl;
	cout << "7.清空文档" << endl;
	cout << "----------" << endl
		 << endl;
	
}

void WorkerManager::eixt_man()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::addemploy()
{ // 添加新职工的数目
	cout << "请输入要添加的人数： " << endl;
	int addnum = 0;
	cin >> addnum;
	if (addnum > 0)
	{
		// 计算新空间 开辟新空间
		int newsize = this->m_Empnum + addnum;
		Worker **newspace = new Worker *[newsize];
		// 蒋原空间拷贝到新空间
		if (m_array != NULL)
		{
			for (int i = 0; i < m_Empnum; i++)
			{
				newspace[i] = m_array[i];
			}
		}
		// 开始添加新数据 批量添加
		for (int i = 0; i < addnum; i++)
		{
			unsigned int id;
			string name;
			int selectnum = 1;
			// 下面用到了cin的判断和清除来限定用户输入
			cout << "请输入第" << i + 1 << "名员工id: " << endl;
			while (!(cin >> id))
			{
				cout << "请重新输入: " << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
			cout << "请输入第" << i + 1 << "名员工姓名: " << endl;
			cin >> name;

			cout << "请输入第" << i + 1 << "名员工部门编号: " << endl;
			cout << "(1.普通员工\t2.经理\t3.boss)" << endl;
			while (true)
			{
				cin >> selectnum;
				if (selectnum == 1 || selectnum == 2 || selectnum == 3)
				{
					break;
				}
				else
				{
					cout << "请选择有效的部门编号(1, 2, 3): " << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}
			}

			// 创建员工职责 添加到数组里
			switch (selectnum)
			{
			case 1:
				newspace[m_Empnum + i] = new Employee(name, id, 1);
				break;
			case 2:
				newspace[m_Empnum + i] = new Manager(name, id, 2);
				break;
			case 3:
				newspace[m_Empnum + i] = new Boss(name, id, 3);
				break;

			default:
				break;
			}

		} // 释放原空间
		delete[] this->m_array;
		// 重新赋值
		this->m_Empnum = newsize;
		this->m_array = newspace;
		this->save();
		// 添加后不为空
		this->isempty = false;
		cout << "add employee successful! " << endl;
	}
	else
		cout << "input error! retry..." << endl;
	// 按任意键返回上一级

	system("pause");
	// system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILE, ios::out);

	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->m_array[i]->m_id << "  ";
		ofs << this->m_array[i]->m_name << "\t";
		ofs << this->m_array[i]->m_num << "\t" << endl;
	}
	ofs.close();
}

void WorkerManager::show_emp()
{
	if (this->isempty)
	{
		cout << "文件不存在or没有数据!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			this->m_array[i]->showInfn();
		}
	}
	system("pause");
	// system("cls");
}

int WorkerManager::getnum()
{
	ifstream ifs;
	ifs.open(FILE, ios::in);
	unsigned int id;
	string name;
	int num;
	int sum = 0;
	while (ifs >> id && ifs >> name && ifs >> num)
	{
		sum++;
	}
	ifs.close();
	return sum;
}

void WorkerManager::initemp()
{
	ifstream ifs;
	ifs.open(FILE, ios::in);
	int id;
	string name;
	int num;
	for (int i = 0; ifs >> id && ifs >> name && ifs >> num; i++)
	{
		Worker *worker = NULL;
		if (num == 1)
			worker = new Employee(name, id, num);
		else if (num == 2)
			worker = new Manager(name, id, num);
		else
			worker = new Boss(name, id, num);
		this->m_array[i] = worker;
	}
}

int WorkerManager::isfand(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_Empnum; i++)
	{
		if (id == this->m_array[i]->m_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::delemp()
{
	if (this->isempty)
	{
		cout << "文件为空,无法删除" << endl;
	}
	else
	{
		int id = 0;
		cout << "请输入要删除的员工id: " << endl;
		cin >> id;

		int index = this->isfand(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_Empnum - 1; i++)
			{
				this->m_array[i] = this->m_array[i + 1];
			}
			// 删除后--
			this->m_Empnum--;
			// 保存到txt文件
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "查无此人，删除失败！" << endl;
		}
	}
	system("pause");
	// system("cls");
}

void WorkerManager::modemp()
{
	if (this->isempty)
	{
		cout << "文件为空,无法修改" << endl;
	}
	else
	{
		int idd = 0;
		cout << "请输入要修改的员工id: " << endl;
		cin >> idd;
		int index = this->isfand(idd);

		if (index != -1)
		{ // 删除掉要修改的

			cout << "查到id为" << m_array[index]->m_id << "的员工: " << m_array[index]->m_name << endl;
			delete this->m_array[index];
			unsigned int id;
			string name;
			int selectnum = 1;

			// 下面用到了cin的判断和清除来限定用户输入
			cout << "请输入新的员工id: " << endl;
			while (!(cin >> id))
			{
				cout << "请重新输入: " << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
			cout << "请输入新的员工姓名: " << endl;
			cin >> name;

			cout << "请输入新的部门编号: " << endl;
			cout << "(1.普通员工\t2.经理\t3.boss)" << endl;
			while (true)
			{
				cin >> selectnum;
				if (selectnum == 1 || selectnum == 2 || selectnum == 3)
				{
					break;
				}
				else
				{
					cout << "请选择有效的部门编号(1, 2, 3): " << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}
			}

			// 创建员工职责 添加到数组里
			switch (selectnum)
			{
			case 1:
				m_array[index] = new Employee(name, id, 1);
				break;
			case 2:
				m_array[index] = new Manager(name, id, 2);
				break;
			case 3:
				m_array[index] = new Boss(name, id, 3);
				break;

			default:
				break;
			}
			// 修改后保存到txt文件
			this->save();
			cout << "modify successful!" << endl;
		}
		else
		{
			cout << "查无此人!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager ::findemp()
{
	if (this->isempty)
	{
		cout << "文件不存在，无法查找！" << endl;
	}
	else
	{
		int id;
		string name;
		int select;
		cout << "请输入查找方式: " << endl
			 << "1、按员工编号"
			 << "\t2、按员工姓名" << endl;
		cin >> select;
		// id finding
		if (select == 1)
		{
			cout << "请输入要查找的id: " << endl;
			cin >> id;
			int index = this->isfand(id);
			if (index != -1)
			{
				cout << "id为" << this->m_array[index]->m_id << "信息如下: " << endl;
				this->m_array[index]->showInfn();
			}
			else
			{
				cout << "查无此人！" << endl;
			}
		}
		// name finding
		else if (select == 2)
		{ // flag 标志是否查到,找到返回true
			bool flag = false;
			cout << "请输入要查找的姓名: " << endl;
			cin >> name;
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (name == this->m_array[i]->m_name)
				{
					cout << "姓名为" << this->m_array[i]->m_name << "信息如下: " << endl;
					this->m_array[i]->showInfn();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查无此人！" << endl;
			}
		}
		system("pause");
	}
}

void WorkerManager::sortemp()
{
	if (this->isempty)
	{
		cout << "文件为空，操作失败" << endl;
	}
	else
	{
		cout << "请输入排序方式: " << endl
			 << "1、id升序排列"
			 << "\t2、id降序排序" << endl;

		int select;
		cin >> select;
		for (int i = 0; i < this->m_Empnum; i++)
		{
			int minormax = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				if (select == 1) // up sort
				{
					if (this->m_array[i]->m_id > this->m_array[j]->m_id)
					{
						minormax = j;
					}
				}
				else // down sort
				{
					if (this->m_array[i]->m_id < this->m_array[j]->m_id)
					{
						minormax = j;
					}
				}
			}
			if (i != minormax)
			{
				Worker *temp = this->m_array[i];
				this->m_array[i] = this->m_array[minormax];
				this->m_array[minormax] = temp;
			}
		}
		cout << "排序完成: " << endl;
		this->save();
		this->show_emp();
	}
}

void WorkerManager ::cleanfile()
{
	cout << "请确认清空？ " << endl
		 << "1、确认"
		 << "\t2、返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		fstream ofs;
		ofs.open(FILE, ios::trunc);
		ofs.close();
		if (!this->isempty)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				delete this->m_array[i];
			}
			this->m_Empnum = 0;
			delete[] this->m_array;
			this->m_array = NULL;
			this->isempty = true;
		}
		cout << "清除成功！" << endl;
	}
	system("pause");
}