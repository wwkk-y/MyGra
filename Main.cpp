#include <iostream>
#include "LinkList.h"//����ʵ��
#include "testLinkList.h"//�������ܲ���
#include "MailList.h"//ͨѶ¼
#include "testJosephus.h"////Լɪ������
#include "depositBusiness.h"//�洢��ҵ��
#include "Base.h"//�Զ�����ڿ���̨��ͼ�ο�
#include "Snake.h"//̰����
#include <algorithm>//STL�㷨
#include <functional>//STL��غ���

void project_21120891(Base& base) {
	using namespace std;
	MenuItem menuItem = { "�����๦����ʾ","��Ŀ1-Լɪ������","��Ŀ2-ͨѶ¼","��Ŀ3-�洢��ҵ��","project->add","�˳�"};
	Menu menu(base, menuItem, 6);
	int choice = 0;
	while (1) {
		switch (choice = menu.show(choice)) {
		case 0:
			testLinkList(base);
			break;
		case 1:
			testJosephus(base);
			break;
		case 2:
			MailList(base).start();//ͨѶ¼ͨ��һ����������,������.start()����
			break;
		case 3:
			depositBusiness(base).start();//�洢��ҵ��ͨ��һ����������,������.start()����
			break;
		case 4:
			Snake(base).start();//̰���ߵ�ʵ��
			break;
		default:
			menu.close();
			return;
		}
	}
}

int main() {
	using namespace std;
	Base base;
	MenuItem items = { "21120891-Τ��־","xxxxxxxx-XX","xxxxxxxx-XX","xxxxxxxx-XX"};
	Menu menu(base, items, 4);
	int choice = 0;
	while (1) {
		switch (choice = menu.show(choice)) {
		case 0:
			project_21120891(base);
			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			return 0;
		}
	}
	

	return 0;
}