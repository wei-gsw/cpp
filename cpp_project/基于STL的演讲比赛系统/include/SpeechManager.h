#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"
using namespace std;

// 管理类
class SpeechManager
{
public:
    SpeechManager();
    ~SpeechManager();
    // 第一轮容器12人编号
    vector<int> v1;
    // 第二轮容器6人
    vector<int> v2;
    // 最后的胜利者
    vector<int> Victory;
    // 比赛轮数
    int m_index = 1;
    // 具体选手容器
    map<int, Speaker> m_Speaker;
    // 标志 文件是否为空
    bool isfileempty = true;

    // 初始化
    void initspker();
    // 显示功能菜单
    void showMenu();
    // 退出系统
    void exitSystem();
    // 创建成员
    void creatspker();
    // 开始比赛整个流程控制函数
    void starspeech();
    // 抽签
    void randspeaker();
    // 正式比赛
    void speechconst();
    // 显示结果
    void showscore();
    // 保存文件
    void savefile();
    // 显示文件内容
    void showfile();
    // 往届记录
    map<int, vector<string>> m_record;
    // 清空文件
    void deletefile();
};
