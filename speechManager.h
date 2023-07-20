#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
using namespace std;



//�ݽ�������
class SpeechManager {
public :
	//���캯��
	SpeechManager();

	//�˵�����
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������
	void initSpeech();

	//����num��ѡ��
	void createSpeaker();

	//��ʼ���� --�������̿���
	void startSpeech();

	//�鿴�����¼
	void lookRecord();

	//��������¼
	void cleanRecord();

	//�����ļ�
	void save();

	//����ѡ������ 12��
	vector<int> v1;

	//��һ�ֽ������� 6��
	vector<pair<int,double>> v2;

	//ʤ��ǰ�������� 3��
	vector<pair<int, double>> victory;

	//��ű�� �Լ���Ӧ�ľ���ѡ������
	map<int, Speaker> m_Speaker;
	
	//��¼��������
	int m_Index;
	//��������
	~SpeechManager();
};