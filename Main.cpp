#include <iostream>
#include "LinkList.h"//链表实现
#include "testLinkList.h"//链表功能测试
#include "MailList.h"//通讯录
#include "testJosephus.h"////约瑟夫问题
#include "depositBusiness.h"//存储款业务
#include "Base.h"//自定义基于控制台的图形库
#include "Snake.h"//贪吃蛇
#include <algorithm>//STL算法
#include <functional>//STL相关函数

void project_21120891(Base& base) {
	using namespace std;
	MenuItem menuItem = { "链表类功能演示","项目1-约瑟夫问题","项目2-通讯录","项目3-存储款业务","project->add","退出"};
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
			MailList(base).start();//通讯录通过一个类来管理,匿名类.start()即可
			break;
		case 3:
			depositBusiness(base).start();//存储款业务通过一个类来管理,匿名类.start()即可
			break;
		case 4:
			Snake(base).start();//贪吃蛇的实现
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
	MenuItem items = { "21120891-韦永志","xxxxxxxx-XX","xxxxxxxx-XX","xxxxxxxx-XX"};
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