#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include "SpeechManager.h"

int main()
{
    srand((unsigned int)time(NULL));
    SpeechManager sm;
    sm.showMenu();
    while (true)
    {
        cout << "input your choice: " << endl;
        int choice = 0;
        cin >> choice;
        switch (choice)
        {
        case 0:
            sm.exitSystem();
            break;
        case 1:
            sm.starspeech();
            break;
        case 2:
            sm.showfile();
            break;
        case 3:
            sm.deletefile();
            break;
        default:
            system("cls");
            break;
        };
    }

    system("pause");
    system("cls");
    return 0;
}
