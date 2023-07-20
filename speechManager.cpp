#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include"speechManager.h"
using namespace std;
const int SpeechCount = 20;
const string FileName = "competitionResults.csv";
//���캯��
SpeechManager::SpeechManager() {
	//��ʼ������
	this->initSpeech();

	//����ѡ��
	this->createSpeaker();
}
//��������
SpeechManager::~SpeechManager() {

}
void SpeechManager::show_Menu() {
	cout << "********************************************************" << endl;
	cout << "*********************��ӭ�μ��ݽ�����*******************" << endl;
	cout << "*********************1.��ʼ�ݽ�����*********************" << endl;
	cout << "*********************2.�鿴�����¼*********************" << endl;
	cout << "*********************3.��������¼*********************" << endl;
	cout << "*********************4.�˳���������*********************" << endl;
	cout << "********************************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);//ʵ���߳��˳�
}

void SpeechManager::initSpeech() {
	//������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	//��ʼ����������
	this->m_Index = 1;
}

void SpeechManager::cleanRecord() {
	std::ofstream file(FileName, std::ios::trunc);
	file.close();
	cout << "��ճɹ���" << endl;
	cin.get(); cin.get();
}
bool isFileEmpty(const std::string& fileName) {
	std::ifstream file(fileName);
	return file.peek() == std::ifstream::traits_type::eof();
}
void SpeechManager::lookRecord() {
	ifstream file(FileName); // ���ļ�
	if (isFileEmpty(FileName)) {
		cout << "�ļ�Ϊ�գ����ȱ�����" << endl;
		cin.get();
		cin.get();
		return;
	}
	string line;
	int count = 1;
	if (file.is_open()) { // ����ļ��Ƿ�ɹ���
		while (getline(file, line)) { // ���ж�ȡ�ļ�����
			cout << "��" << count++ << "��   ";
			cout << line << endl; // ��ӡÿһ��
		}
		file.close(); // �ر��ļ�
	}
	else {
		cout << "�޷����ļ�" << endl;
	}
	cin.get(); cin.get();
}
void SpeechManager::createSpeaker() {
	string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < SpeechCount; i++) {
		Speaker speaker;
		speaker.m_Name = string("ѡ��") + s[i];
		speaker.m_Score[0] = 0;
		speaker.m_Score[1] = 0;
		//��12��ѡ�ֱ��
		this->v1.push_back(i + 1001);
		this->m_Speaker.insert(make_pair(i + 1001, speaker));
	}
	/*for (map<int, Speaker>::iterator it = m_Speaker.begin(); it != m_Speaker.end(); it++) {
		cout << it->first << " " << it->second.m_Name << endl;
	}
	cout << this->m_Speaker.size();*/
}

void SpeechManager::save() {
	ofstream of(FileName, ios::app);  // ʹ�ó�ʼ���б���ļ�����׷��ģʽ��
	if (!of.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}


	// ���ڡ��ǡ������ı�ź͵÷�д���ļ�
	of << "�ھ����: " << victory[0].first << " �÷�: " << victory[0].second << "  "
		<< "�Ǿ����: " << victory[1].first << " �÷�: " << victory[1].second << "  "
		<< "�������: " << victory[2].first << " �÷�: " << victory[2].second << endl;

	of.close();  // �ر��ļ�
}
//���¶����������
bool cmp(const pair<int, double>&a, pair<int, double>&b) {
	return a.second > b.second;
}

void SpeechManager::startSpeech() {
	srand(time(0));
	//��һ�ֱ���
	//1 ��ǩ
	cout <<endl<< "��<< 1 >>��ʽ������ʼѡ�����ڳ�ǩ....." << endl;
	//����ʱ����
	vector<pair<int,double>> group1, group2;//����С�� A B
	//���ѡ��6����
	int flag[1001+SpeechCount] = { 0 };
	int count = 0;
	int a = 1001, b = 1001 + SpeechCount-1;
	while (count < (SpeechCount/2)) {//ѡ��һ������
		int opt = (rand() % (b - a + 1)) + a;//ѡ��һ����
		if (!flag[opt]) {//û�б�ѡ
			//ѡ��
			flag[opt] = true;
			count++;
		}
	}
	for (int i = 1001; i <= 1001 + SpeechCount - 1; i++) {
		int c = 500, d = 1000;
		double score = (double)((rand() % (d - c + 1)) + c) / 10;//���
		this->m_Speaker[i].m_Score[0] = score;
		if (flag[i]) {
			group1.push_back(make_pair(i,score));
		}
		else {
			group2.push_back(make_pair(i, score));
		}
	}
	cout <<endl<< "��ǩ���ݽ�˳������:" << endl;
	for (int i = 0; i < SpeechCount / 2; i++) {
		cout << "��" << i+1 << "�飺" << "A�ӣ�" << group1[i].first << "  B�ӣ�" << group2[i].first << endl;;
	}
	cin.get();
	//2 ����
	cout <<endl<< "----------��һ�ֱ�����ʽ��ʼ----------";
	//����
	sort(group1.begin(), group1.end(), cmp);
	sort(group2.begin(), group2.end(), cmp);

	//3 ��ʾ�������
	cout<<endl<<"��һС��������Σ�"<<endl;
	for (int i = 0; i < group1.size(); i++) {
		if (i < (SpeechCount / 2 / 2)) {
			int c = 500, d = 1000;
			double score = (double)((rand() % (d - c + 1)) + c) / 10;//���
			this->v2.push_back(make_pair(group1[i].first,score));//ǰ����
		}
		cout << "���:" << group1[i].first << " " << "������" << this->
			m_Speaker[group1[i].first].m_Name << " " << "�ɼ�" << this->
			m_Speaker[group1[i].first].m_Score[0]<<endl;
	}
	cout << endl << "�ڶ�С��������Σ�"<<endl;
	for (int i = 0; i < group2.size(); i++) {
		if (i < (SpeechCount / 2 / 2)) {
			int c = 500, d = 1000;
			double score = (double)((rand() % (d - c + 1)) + c) / 10;//���
			this->v2.push_back(make_pair(group1[i].first, score));//ǰ����
		}
		cout << "���:" << group2[i].first << " " << "������" << this->
			m_Speaker[group2[i].first].m_Name << " " << "�ɼ�" << this->
			m_Speaker[group2[i].first].m_Score[0]<<endl;
	}
	cout << endl << "----------��һ�ֱ������----------"<<endl;

	cout << "�ɹ��������ֱ������ǣ�";
	for (int i = 0; i < this->v2.size(); i++) {
		cout << this->v2[i].first << " ";
	}cout << endl;
	//�ڶ��ֱ���
	
	//1 ��ǩ
	cout << endl << "��<< 2 >>����ʽ������ʼѡ�����ڳ�ǩ....." << endl;
	//���ѡ�������˽��е���(ʵ�ֳ�ǩ)
	for (int i = 0; i < SpeechCount / 2; i++) {
		int a = 0, b = v2.size() - 1;
		int f1 = (rand() % (b - a + 1)) + a;//ѡ��һ����
		int f2 = (rand() % (b - a + 1)) + a;//ѡ��һ����
		swap(v2[f1], v2[f2]);
	}
	cout << "��ǩ���ݽ�˳�����£�";
	for (int i = 0; i < this->v2.size(); i++) {
		cout << this->v2[i].first << " ";
	}
	cin.get();
	//2 ����
	cout << endl << "----------�ڶ��ֱ�����ʽ��ʼ----------"<<endl;
	sort(v2.begin(), v2.end(), cmp);
	//3 ��ʾ���ս��
	cout << "�ڶ���С������:" << endl;
	for (int i = 0; i < v2.size(); i++) {
		cout << "���:" << group2[i].first << " " << "������" << this->
			m_Speaker[group2[i].first].m_Name << " " << "�ɼ�" << this->
			m_Speaker[group2[i].first].m_Score[0] << endl;
	}
	cout << endl << "----------�ڶ��ֱ������----------" << endl;
	cin.get();
	cout << "�ڶ��ֽ���ѡ������:" << endl;
	for (int i = 0; i < 3; i++) {
		this->victory.push_back(make_pair(v2[i].first, v2[i].second));
		cout << "���:" << group2[i].first << " " << "������" << this->
			m_Speaker[group2[i].first].m_Name << " " << "�ɼ�" << this->
			m_Speaker[group2[i].first].m_Score[0] << endl;
	}
	//4 �������
	//����victory
	this->save();
	cin.get(); cin.get();
}