#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include"speechManager.h"
using namespace std;
const int SpeechCount = 20;
const string FileName = "competitionResults.csv";
//构造函数
SpeechManager::SpeechManager() {
	//初始化属性
	this->initSpeech();

	//创建选手
	this->createSpeaker();
}
//析构函数
SpeechManager::~SpeechManager() {

}
void SpeechManager::show_Menu() {
	cout << "********************************************************" << endl;
	cout << "*********************欢迎参加演讲比赛*******************" << endl;
	cout << "*********************1.开始演讲比赛*********************" << endl;
	cout << "*********************2.查看往届记录*********************" << endl;
	cout << "*********************3.清空往届记录*********************" << endl;
	cout << "*********************4.退出比赛程序*********************" << endl;
	cout << "********************************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	exit(0);//实现线程退出
}

void SpeechManager::initSpeech() {
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;
}

void SpeechManager::cleanRecord() {
	std::ofstream file(FileName, std::ios::trunc);
	file.close();
	cout << "清空成功！" << endl;
	cin.get(); cin.get();
}
bool isFileEmpty(const std::string& fileName) {
	std::ifstream file(fileName);
	return file.peek() == std::ifstream::traits_type::eof();
}
void SpeechManager::lookRecord() {
	ifstream file(FileName); // 打开文件
	if (isFileEmpty(FileName)) {
		cout << "文件为空，请先比赛！" << endl;
		cin.get();
		cin.get();
		return;
	}
	string line;
	int count = 1;
	if (file.is_open()) { // 检查文件是否成功打开
		while (getline(file, line)) { // 逐行读取文件内容
			cout << "第" << count++ << "届   ";
			cout << line << endl; // 打印每一行
		}
		file.close(); // 关闭文件
	}
	else {
		cout << "无法打开文件" << endl;
	}
	cin.get(); cin.get();
}
void SpeechManager::createSpeaker() {
	string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < SpeechCount; i++) {
		Speaker speaker;
		speaker.m_Name = string("选手") + s[i];
		speaker.m_Score[0] = 0;
		speaker.m_Score[1] = 0;
		//给12名选手编号
		this->v1.push_back(i + 1001);
		this->m_Speaker.insert(make_pair(i + 1001, speaker));
	}
	/*for (map<int, Speaker>::iterator it = m_Speaker.begin(); it != m_Speaker.end(); it++) {
		cout << it->first << " " << it->second.m_Name << endl;
	}
	cout << this->m_Speaker.size();*/
}

void SpeechManager::save() {
	ofstream of(FileName, ios::app);  // 使用初始化列表打开文件，以追加模式打开
	if (!of.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}


	// 将冠、亚、季军的编号和得分写入文件
	of << "冠军编号: " << victory[0].first << " 得分: " << victory[0].second << "  "
		<< "亚军编号: " << victory[1].first << " 得分: " << victory[1].second << "  "
		<< "季军编号: " << victory[2].first << " 得分: " << victory[2].second << endl;

	of.close();  // 关闭文件
}
//重新定义排序规则
bool cmp(const pair<int, double>&a, pair<int, double>&b) {
	return a.second > b.second;
}

void SpeechManager::startSpeech() {
	srand(time(0));
	//第一轮比赛
	//1 抽签
	cout <<endl<< "第<< 1 >>正式比赛开始选手正在抽签....." << endl;
	//加延时函数
	vector<pair<int,double>> group1, group2;//两个小组 A B
	//随机选出6人人
	int flag[1001+SpeechCount] = { 0 };
	int count = 0;
	int a = 1001, b = 1001 + SpeechCount-1;
	while (count < (SpeechCount/2)) {//选出一半人数
		int opt = (rand() % (b - a + 1)) + a;//选出一个人
		if (!flag[opt]) {//没有被选
			//选择
			flag[opt] = true;
			count++;
		}
	}
	for (int i = 1001; i <= 1001 + SpeechCount - 1; i++) {
		int c = 500, d = 1000;
		double score = (double)((rand() % (d - c + 1)) + c) / 10;//打分
		this->m_Speaker[i].m_Score[0] = score;
		if (flag[i]) {
			group1.push_back(make_pair(i,score));
		}
		else {
			group2.push_back(make_pair(i, score));
		}
	}
	cout <<endl<< "抽签后演讲顺序如下:" << endl;
	for (int i = 0; i < SpeechCount / 2; i++) {
		cout << "第" << i+1 << "组：" << "A队：" << group1[i].first << "  B队：" << group2[i].first << endl;;
	}
	cin.get();
	//2 比赛
	cout <<endl<< "----------第一轮比赛正式开始----------";
	//排序
	sort(group1.begin(), group1.end(), cmp);
	sort(group2.begin(), group2.end(), cmp);

	//3 显示晋级结果
	cout<<endl<<"第一小组比赛名次："<<endl;
	for (int i = 0; i < group1.size(); i++) {
		if (i < (SpeechCount / 2 / 2)) {
			int c = 500, d = 1000;
			double score = (double)((rand() % (d - c + 1)) + c) / 10;//打分
			this->v2.push_back(make_pair(group1[i].first,score));//前三名
		}
		cout << "编号:" << group1[i].first << " " << "姓名：" << this->
			m_Speaker[group1[i].first].m_Name << " " << "成绩" << this->
			m_Speaker[group1[i].first].m_Score[0]<<endl;
	}
	cout << endl << "第二小组比赛名次："<<endl;
	for (int i = 0; i < group2.size(); i++) {
		if (i < (SpeechCount / 2 / 2)) {
			int c = 500, d = 1000;
			double score = (double)((rand() % (d - c + 1)) + c) / 10;//打分
			this->v2.push_back(make_pair(group1[i].first, score));//前三名
		}
		cout << "编号:" << group2[i].first << " " << "姓名：" << this->
			m_Speaker[group2[i].first].m_Name << " " << "成绩" << this->
			m_Speaker[group2[i].first].m_Score[0]<<endl;
	}
	cout << endl << "----------第一轮比赛完毕----------"<<endl;

	cout << "成功晋级二轮比赛的是：";
	for (int i = 0; i < this->v2.size(); i++) {
		cout << this->v2[i].first << " ";
	}cout << endl;
	//第二轮比赛
	
	//1 抽签
	cout << endl << "第<< 2 >>轮正式比赛开始选手正在抽签....." << endl;
	//随机选择两个人进行调换(实现抽签)
	for (int i = 0; i < SpeechCount / 2; i++) {
		int a = 0, b = v2.size() - 1;
		int f1 = (rand() % (b - a + 1)) + a;//选出一个人
		int f2 = (rand() % (b - a + 1)) + a;//选出一个人
		swap(v2[f1], v2[f2]);
	}
	cout << "抽签后演讲顺序如下：";
	for (int i = 0; i < this->v2.size(); i++) {
		cout << this->v2[i].first << " ";
	}
	cin.get();
	//2 比赛
	cout << endl << "----------第二轮比赛正式开始----------"<<endl;
	sort(v2.begin(), v2.end(), cmp);
	//3 显示最终结果
	cout << "第二轮小组名次:" << endl;
	for (int i = 0; i < v2.size(); i++) {
		cout << "编号:" << group2[i].first << " " << "姓名：" << this->
			m_Speaker[group2[i].first].m_Name << " " << "成绩" << this->
			m_Speaker[group2[i].first].m_Score[0] << endl;
	}
	cout << endl << "----------第二轮比赛完毕----------" << endl;
	cin.get();
	cout << "第二轮晋级选手如下:" << endl;
	for (int i = 0; i < 3; i++) {
		this->victory.push_back(make_pair(v2[i].first, v2[i].second));
		cout << "编号:" << group2[i].first << " " << "姓名：" << this->
			m_Speaker[group2[i].first].m_Name << " " << "成绩" << this->
			m_Speaker[group2[i].first].m_Score[0] << endl;
	}
	//4 保存分数
	//利用victory
	this->save();
	cin.get(); cin.get();
}