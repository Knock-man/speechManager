#include<iostream>
#include"speechManager.h"
using namespace std;
int main() {
	SpeechManager sm;
	int choice = 0;
	while (1) {
		sm.show_Menu();
		cout << "请输入你的选择：";
		cin >> choice;
		switch ((choice))
		{
		case 1: {
			sm.startSpeech();//开始演讲比赛；
			break;
		}
		case 2: {
			sm.lookRecord();//查看往届记录
			break;
		}
		case 3: {
			sm.cleanRecord();//清空往届记录
			break;
		}
		case 4: {
			sm.exitSystem();//退出
			break;
		}
		default:
			cout << "输入有误，请重新输入" << endl;
			cin.get();
			cin.get();
			break;
		}
		system("cls");
	}
	return 0;
}