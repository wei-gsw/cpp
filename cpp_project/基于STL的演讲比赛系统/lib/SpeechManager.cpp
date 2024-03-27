#include "SpeechManager.h"
#include <iostream>
#include "Speaker.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <functional>
#include <fstream>
using namespace std;

SpeechManager::SpeechManager()
{
    initspker();
}
SpeechManager::~SpeechManager()
{
}

void SpeechManager ::initspker()
{
    // 初始化
    this->v1.clear();
    this->v2.clear();
    this->Victory.clear();
    this->m_Speaker.clear();
    this->m_index = 1;
    this->m_record.clear();
    // 创建选手
    this->creatspker();
}
void SpeechManager::showMenu()
{
    cout << "=================================" << endl;
    cout << "========欢迎参加演讲比赛!========" << endl;
    cout << "========1、开始演讲比赛!=========" << endl;
    cout << "========2、查看往届记录!=========" << endl;
    cout << "========3、清空比赛记录!=========" << endl;
    cout << "========0、退出比赛系统!=========" << endl;
    cout << "=================================" << endl
         << endl;
}

void SpeechManager::exitSystem()
{
    cout << "欢迎下次使用!" << endl;
    system("pause");
    exit(0);
}

void SpeechManager::creatspker()
{
    string sname = "ABCDEFGHIJKL";
    for (int i = 0; i < sname.size(); i++)
    {
        string newname = "选手";
        newname += sname[i];

        Speaker sp;
        sp.m_name = newname;
        for (int i = 0; i < 2; i++)
        {
            sp.m_score[i] = 0;
        }
        this->v1.push_back(i + 10001);
        this->m_Speaker.insert(make_pair(i + 10001, sp));
    }
}

void SpeechManager::starspeech()
{
    // 第一轮抽签分组
    this->randspeaker();
    // 开始比赛，打分
    this->speechconst();
    // 显示结果
    this->showscore();
    this->m_index++;
    // 第二轮抽签分组
    this->randspeaker();
    // 开始比赛，打分
    this->speechconst();
    // 显示结果
    this->showscore();
    // 保存数据
    this->savefile();
    // 做完初始化清理容器
    this->initspker();
    this->showMenu();
    system("cls");
}

// 抽签
void SpeechManager::randspeaker()
{
    cout << "第" << this->m_index << "轮"
         << "比赛开始抽签" << endl;
    cout << "=================================" << endl
         << "抽取结果如下: " << endl;
    if (this->m_index == 1)
    {
        random_shuffle(this->v1.begin(), v1.end());
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << " ";
            if (*it == v1[5])
                cout << endl;
        }
        cout << endl;
    }
    else
    {
        random_shuffle(this->v2.begin(), v2.end());
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << " ";
            if (*it == v2[2])
                cout << endl;
        }
        cout << endl;
    }
    cout << "=================================" << endl;
    system("pause");
    cout << endl;
}

void SpeechManager::speechconst()
{
    cout << "========第" << this->m_index << "轮比赛正式开始========" << endl;
    // 临时容器判断是第几轮容器
    vector<int> vv;
    if (this->m_index == 1)
        vv = v1;
    else
        vv = v2;
    // 临时容器 key唯分数 value是选手编号，降序排列
    multimap<double, int, greater<int>> mm;
    int num = 0;
    for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
    {
        // deque容器存放评委打分
        deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            double da = (rand() % 401 + 600) / 10.00f;
            d.push_back(da);
            // 显示详细成绩
            //  cout << d[i] << " ";
        }
        // cout << endl;
        // 排序
        sort(d.begin(), d.end());
        // 去掉最高分和最低分
        d.pop_back();
        d.pop_front();
        // 求出总和
        double sum = accumulate(d.begin(), d.end(), 0.0f);
        // 求出平均值
        double avg = sum / (double)d.size();
        // 导入分数
        this->m_Speaker[*it].m_score[this->m_index - 1] = avg;
        // cout << this->m_Speaker[*it].m_score[this->m_index - 1] << " ";
        // 临时容器来存放6人小组
        mm.insert(make_pair(avg, *it));
        num++;
        if (num % 6 == 0)
        {
            cout << "第" << num / 6 << "组的成绩: " << endl;
            for (multimap<double, int, greater<int>>::iterator ite = mm.begin(); ite != mm.end(); ite++)
            {
                cout << ite->second << "号" << this->m_Speaker[ite->second].m_name << "\t成绩: " << this->m_Speaker[ite->second].m_score[this->m_index - 1] << endl;
            }
            // 取前三名
            int count = 0;
            for (multimap<double, int, greater<int>>::iterator ite = mm.begin(); ite != mm.end() && count < 3; ite++, count++)
            {
                if (this->m_index == 1)
                {
                    v2.push_back(ite->second);
                }
                else
                    Victory.push_back(ite->second);
            }
            mm.clear();
        }
    }
    cout << endl;
}

void SpeechManager::showscore()
{
    vector<int> vv;
    if (this->m_index == 1)
    {
        vv = v2;
    }
    else
    {
        vv = Victory;
    }
    cout << "本轮晋级的选手有: " << endl;
    for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
    {
        cout << *it << "号选手" << this->m_Speaker[*it].m_name << "\t成绩: " << this->m_Speaker[*it].m_score[this->m_index - 1] << endl;
    }
    cout << "===========第" << this->m_index << "轮比赛结束=========" << endl;
    cout << "=================================" << endl
         << endl;
    system("pause");
}

void SpeechManager::savefile()
{
    fstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    if (!ofs.is_open())
    {
        cout << "文件不存在!" << endl;
    }
    else
    {
        for (vector<int>::iterator it = Victory.begin(); it != Victory.end(); it++)
        {
            ofs << *it << "," << this->m_Speaker[*it].m_score[1] << ",";
        }
    }
    ofs << endl;
    // 关闭文件
    ofs.close();
    cout << "记录已经保存" << endl;
    this->isfileempty = false;
}

void SpeechManager::showfile()
{
    // 读文件
    fstream ifs;
    ifs.open("speech.csv", ios::in);

    if (!ifs.is_open())
    {
        this->isfileempty = true;
        cout << "文件不存在,无法查看!" << endl;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        this->isfileempty = true;
        cout << "文件为空！" << endl;
        ifs.close();
        return;
    }

    this->isfileempty = false;
    // 将上面的ch放回去
    ifs.putback(ch);
    // 临时容器来存放往届数据
    vector<string> vv;
    string data;
    // 第几届
    int index = 0;

    while (ifs >> data)
    {
        // cout << data << endl;
        //  "10010,86.675,10009,81.3,10007,78.55,"
        int pos = -1;
        int ss = 0;
        while (true)
        {
            pos = data.find(",", ss);
            if (pos == -1)
            {
                break;
            }
            string temp = data.substr(ss, pos - ss);
            vv.push_back(temp);
            ss = pos + 1;

            // cout << temp << endl;
        }

        this->m_record.insert(make_pair(index, vv));
        index++;
        vv.clear();
    }
    ifs.close();
    for (int i = 0; i < m_record.size(); i++)
    {
        cout << "第" << i + 1 << "届前三名: " << endl;
        cout << "冠军编号" << m_record[i][0] << "\t成绩: " << m_record[i][1] << endl;
        cout << "亚军编号" << m_record[i][2] << "\t成绩: " << m_record[i][3] << endl;
        cout << "季军编号" << m_record[i][4] << "\t成绩: " << m_record[i][5] << endl;
    }
}

void SpeechManager::deletefile()
{
    cout << "请确认要删除文件？" << endl;
    cout << "1、确认\t2、返回" << endl;
    int select = 2;
    cin >> select;
    if (select == 1)
    {
        ofstream ofs;
        ofs.open("speech.csv", ios::trunc);
        ofs.clear();
        this->initspker();
        cout << "清楚成功" << endl;
        this->isfileempty = true;
    }
}