#include<iostream>
#include"speechManager.h"
using namespace std;
int main() {
	SpeechManager sm;
	int choice = 0;
	while (1) {
		sm.show_Menu();
		cout << "���������ѡ��";
		cin >> choice;
		switch ((choice))
		{
		case 1: {
			sm.startSpeech();//��ʼ�ݽ�������
			break;
		}
		case 2: {
			sm.lookRecord();//�鿴�����¼
			break;
		}
		case 3: {
			sm.cleanRecord();//��������¼
			break;
		}
		case 4: {
			sm.exitSystem();//�˳�
			break;
		}
		default:
			cout << "������������������" << endl;
			cin.get();
			cin.get();
			break;
		}
		system("cls");
	}
	return 0;
}