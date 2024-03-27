#include <iostream>
#include <string>
#include "WorkerManager.h"
#include "employee.h"
#include "Worker.h"
#include "boss.h"
#include "manager.h"
#define SIZE 3
using namespace std;

int main()
{

	WorkerManager wm;
	
	// test
	//   Worker *w = new Employee("张三", 1, 1);
	//   w->showInfn();
	//   Worker *w1 = new Manager("bowic",2,2);
	//    w1->showInfn();
	//   Worker *w2 = new Boss("ls", 1, 5);
	//   w2->showInfn();

	while (true)
	{
wm.show_man();	
		int choice = 0;
		cout << "input your choice :" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.eixt_man();
			break;
		case 1:
			wm.addemploy();
			break;
		case 2:
			wm.show_emp();
			break;
		case 3:
			wm.delemp();
			break;
		case 4:
			wm.modemp();
			break;
		case 5:
			wm.findemp();
			break;
		case 6:
			wm.sortemp();
			break;
		case 7:
			wm.cleanfile();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	// 清盘
	//  system("cls");
	return 0;
}
