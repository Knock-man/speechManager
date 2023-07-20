#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
using namespace std;



//演讲管理类
class SpeechManager {
public :
	//构造函数
	SpeechManager();

	//菜单功能
	void show_Menu();

	//退出系统
	void exitSystem();

	//初始化属性
	void initSpeech();

	//创建num名选手
	void createSpeaker();

	//开始比赛 --比赛流程控制
	void startSpeech();

	//查看往届记录
	void lookRecord();

	//清空往届记录
	void cleanRecord();

	//保存文件
	void save();

	//比赛选手容器 12人
	vector<int> v1;

	//第一轮晋级容器 6人
	vector<pair<int,double>> v2;

	//胜利前三名容器 3人
	vector<pair<int, double>> victory;

	//存放编号 以及对应的具体选手容器
	map<int, Speaker> m_Speaker;
	
	//记录比赛轮数
	int m_Index;
	//析构函数
	~SpeechManager();
};