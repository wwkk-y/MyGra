#pragma warning (disable:4819)
#include "testLinkList.h"
#include <fstream>
#include <algorithm>

void testLinkList(Base& base) {
	LinkList<string> ls;//主要测试对象
	//一级目录主要功能
	MenuItem item1 = { "创建对象","增加","删除","查找","修改","其余函数","STL算法","退出"};
	Menu m1(16,base.getY(),base.getX()-16,0,base,item1,8);
	//二级目录展示函数名字
	Menu m2(25, base.getY(), base.getX() - 16 - 24, 0, base, nullptr, 0);
	m2.setBorderLine();
	//三级目录各种传参形式
	Menu m3(25, base.getY(), base.getX() - 16 - 24 - 24, 0, base, nullptr, 0);
	m3.setBorderLine();
	//展示区域
	Baseder baseder(base.getX() - 16 - 24 - 24-1,base.getY()-2, 1, 1, base);
	baseder.setBorderLine();
	int choice = 0;
	while (1) {
		switch (choice = m1.show(choice)) {
		case 0:
			testConstruct(m2,m3,baseder,ls);
			break;
		case 1:
			addOpt(m2, m3, baseder, ls);
			break;
		case 2:
			delOpt(m2, m3, baseder, ls);
			break;
		case 3:
			findOpt(m2, m3, baseder, ls);
			break;
		case 4:
			replaceOpt(m2, m3, baseder, ls);
			break;
		case 5:
			elseOpt(m2, m3, baseder, ls);
			break;
		case 6:
			aboutSTL(m2,m3,baseder,ls);
			break;
		default:
			m1.close();
			m2.close();
			m3.close();
			baseder.close();
			return;
		}
	}

}

void testConstruct(Menu& m2, Menu& m3, Baseder& baseder,LinkList<string>& ls) {
	MenuItem items = { "LinkList<T>","operator=","~LinkList<T>","通过IO创建","...上一级"};
	m2.reset(items, 5);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice=m2.show(choice, false)) {
		case 0:
			startConstruct(m3, baseder, ls);
			break;
		case 1:
			startEqual(m3, baseder, ls);
			break;
		case 2:
			startDecon(m3, baseder, ls);
			break;
		case 3:
			startIO(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}
}

void startIO(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "标准I/O","文件I/O","...上一级"};
	m3.reset(items, 3);
	setTitle(m3,"创建方式");
	m3.setBorderLine();
	int choice=0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			stdIO(baseder, ls);
			break;
		case 1:
			fileIO(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
	
}

void stdIO(Baseder& baseder, LinkList<string>& ls) {
	Label lb(baseder, 0, 0, 35);
	Baseder down(baseder.getX(), baseder.getY() - 2, 0, 2, baseder);
	down.setBorderLine();
	down.draw();

	lb.setStr("Input Value <quit to quit>");
	string value;
	value = lb.show();
	ls.clear();
	while (value != "quit") {
		ls.push_back(value);
		value = lb.show();
	}

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void fileIO(Baseder& baseder, LinkList<string>& ls) {
	baseder.setText(1,1,"Input fileName: ");
	InputTips name(baseder,17,1);
	Baseder down(baseder.getX(),baseder.getY()-2, 0, 2, baseder);
	down.setBorderLine();
	down.draw();

	name.setTips("lsData.txt");
	string fileName = name.show();
	ifstream fin;
	if (fileName.size()) {
		fin.open(fileName);
	}
	else {
		fileName = "lsData.txt";
		fin.open("lsData.txt");
	}
	name.setText(0,0,fileName.c_str(),0x06);
	name.draw();

	string value;
	ls.clear();
	while (fin >> value) {
		value.resize(6, ' ');
		ls.push_back(value);
	}

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	fin.close();
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void startConstruct(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "默认构造","initializer_list<T>","const T&","int,const T&","const LinkList<T>&","LinkList<T>&&","iterator,iterator","...上一级" };
	m3.reset(items, 8);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice=m3.show(choice, false)) {
		case 0:
			defaultConstruct(baseder, ls);
			break;
		case 1:
			listConstruct(baseder, ls);
			break;
		case 2:
			valueConstruct(baseder, ls);
			break;
		case 3:
			valueNumConstruct(baseder, ls);
			break;
		case 4:
			cpyConstruct(baseder, ls);
			break;
		case 5:
			refConstruct(baseder, ls);
			break;
		case 6:
			iteConstruct(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void defaultConstruct(Baseder& baseder, LinkList<string>& ls) {
	//Label in(baseder, 0, 0, baseder.getX());
	Baseder up(baseder.getX(), 5, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY()-up.getY()+1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();
	
	
	up.setText(1, 1, "//默认构造:", 0x02);
	up.setText(1, 2, "LinkList<string> ls;", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	baseder.draw();

	ls.clear();
	down.gotoxy(ls.show(down.getX()-2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void listConstruct(Baseder& baseder, LinkList<string>& ls) {
	//Label in(baseder, 0, 0, baseder.getX());
	Baseder up(baseder.getX(), 5, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();
	

	up.setText(1, 1, "//列表构造:", 0x02);
	up.setText(1, 2, "LinkList<string> ls={\"hello\",\"world\",\"  c++\",\" win!\"};", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	baseder.draw();

	ls.clear();
	LinkList<string> tls = { "hello","world","  c++"," win!" };
	ls = tls;
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void valueConstruct(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);
	
	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();
	

	up.setText(1, 1, "//初值构造:", 0x02);
	up.setText(1, 2, "string value;", 0x02);
	up.setText(1, 3, "getline(cin,value);", 0x02);
	up.setText(1, 4, "LinkList<string> ls(value);", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	in.setStr("value:");
	ls.clear();
	LinkList<string> tls(in.show());
	ls = tls;
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();

}

void valueNumConstruct(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Label inNum(baseder, in.getX()-1, up.getY() - 1, baseder.getX()-in.getX()+1);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//num个value构造:", 0x02);
	up.setText(1, 2, "string value;", 0x02);
	up.setText(1, 3, "int num=5;", 0x02);
	up.setText(1, 4, "getline(cin,value);", 0x02);
	up.setText(1, 5, "cin>>num;//注意输入数字", 0x02);
	up.setText(1, 6, "LinkList<string> ls(num,value);", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	in.setStr("value:");
	inNum.setStr("num(请输入一个数字):");
	string value = in.show();
	int num;
	try {
		num = stoi(inNum.show());
	}
	catch (...) {//输入异常时默认为5
		num = 5;
	}
	ls.clear();
	LinkList<string> tls(num,value);
	ls = tls;
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();

}

void cpyConstruct(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 6, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//复制构造:", 0x02);
	up.setText(1, 2, "LinkList<string> temp={\"hello\",\"world\",\"  c++\",\" win!\"};", 0x02);
	up.setText(1, 3, "LinkList<string> ls=temp;", 0x02);
	up.setText(1, 4, "ls.show();", 0x02);
	baseder.draw();

	ls.clear();
	LinkList<string> temp = { "hello","world","  c++"," win!" };
	ls = temp;
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void refConstruct(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 6, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//右值引用构造,交换数据拥有权:", 0x02);
	up.setText(1, 2, "LinkList<string> temp={\"hello\",\"world\",\"  c++\",\" win!\"};", 0x02);
	up.setText(1, 3, "LinkList<string> ls((temp));//(temp)为右值", 0x02);
	up.setText(1, 4, "ls.show();", 0x02);
	baseder.draw();

	ls.clear();
	LinkList<string> temp = { "hello","world","  c++"," win!" };
	ls = temp;
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void iteConstruct(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 6, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//迭代器构造,范围为[begin,end):", 0x02);
	up.setText(1, 2, "const char* temp[]={\"hello\",\"world\",\"  c++\"};", 0x02);
	up.setText(1, 3, "LinkList<string> ls(temp,temp+3);", 0x02);
	up.setText(1, 4, "ls.show();", 0x02);
	baseder.draw();

	ls.clear();
	LinkList<string> temp = { "hello","world","  c++"};
	ls = temp;
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void startEqual(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "自己赋值自己","赋值其它对象","...上一级"};
	m3.reset(items, 3);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			equalSelf(baseder, ls);
			break;
		case 1:
			equalElse(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void equalSelf(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 6, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//自己赋值自己会直接return", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "ls=ls;", 0x02);
	up.setText(1, 4, "ls.show();", 0x02);
	baseder.draw();

	//ls.show(down.getX() - 2
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls = ls;
	down.gotoxy(ls.show(down.getX() - 2, down,y+1,1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void equalElse(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//赋值其它对象", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "LinkList<string> temp(2,\"hello\");//2个hello", 0x02);
	up.setText(1, 4, "ls=temp;", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	//ls.show(down.getX() - 2
	int y = ls.show(down.getX() - 2, down, 1, 1);
	LinkList<string> temp(2, "hello");
	ls = temp;
	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void startDecon(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	//Label in(baseder, 0, 0, baseder.getX());
	m3.setText(m3.getXH() - 2, m3.getYH()-1, "none",0xfd);
	setM3Title(m3);
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();

	
	up.setText(1, 1, "//析构函数释放链表:", 0x02);
	up.setText(1, 2, "{", 0x02);
	up.setText(1, 3, "    LinkList<string> ls;", 0x02);
	up.setText(1, 4, "    //代码块执行完毕,ls被释放", 0x02);
	up.setText(1, 5, "}", 0x02);
	baseder.draw();

	ls.clear();

	m3.initMap();
	m3.setBorderLine('*');
	return;
}

void addOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "push_back","emplace_back","push_front","emplace_front","insert","emplace","...上一级"};
	m2.reset(items, 7);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice = m2.show(choice, false)) {
		case 0:
			testPushBack(m3, baseder, ls);
			break;
		case 1:
			testEmplaceBack(m3,baseder,ls);
			break;
		case 2:
			testPushFront(m3, baseder, ls);
			break;
		case 3:
			testEmplaceFront(m3, baseder, ls);
			break;
		case 4:
			testInsert(m3, baseder, ls);
			break;
		case 5:
			testEmplace(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}

}

void testPushBack(Menu& m3, Baseder& baseder, LinkList<string>& ls){
	setM3Title(m3);
	m3.setText(m3.getXH() - 7, m3.getYH(), "const T& value", 0xfd);
	
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//push_back:添加到尾部", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "string value;", 0x02);
	up.setText(1, 5, "getline(cin,value);", 0x02);
	up.setText(1, 6, "ls.push_back(value);", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	ls.push_back(in.show());
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	
	eatBuf();
	win::setCursor();
	m3.initMap();
	m3.setBorderLine('*');
	return;
}

void testEmplaceBack(Menu& m3, Baseder& baseder, LinkList<string>& ls){
	setM3Title(m3);
	m3.setText(m3.getXH() - 11, m3.getYH(), "initializer_list<T> ls", 0xfd);

	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//emplace_back:以列表形式添加到尾部(可使用右值)", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "string value;", 0x02);
	up.setText(1, 5, "getline(cin,value);", 0x02);
	up.setText(1, 6, "ls.emplace_back({value,value,\"hello\",\"world\"});", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	string temp = in.show();
	ls.emplace_back({temp,temp,"hello","world"});
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";

	eatBuf();
	win::setCursor();
	m3.initMap();
	m3.setBorderLine('*');
	return;
}

void testPushFront(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	setM3Title(m3);
	m3.setText(m3.getXH() - 7, m3.getYH(), "const T& value", 0xfd);

	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//push_front:添加到头部", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "string value;", 0x02);
	up.setText(1, 5, "getline(cin,value);", 0x02);
	up.setText(1, 6, "ls.push_front(value);", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	ls.push_front(in.show());
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";

	eatBuf();
	win::setCursor();
	m3.initMap();
	m3.setBorderLine('*');
	return;

}

void testEmplaceFront(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	setM3Title(m3);
	m3.setText(m3.getXH() - 11, m3.getYH(), "initializer_list<T> ls", 0xfd);

	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//emplace_front:以列表形式添加到头部(可使用右值)", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "string value;", 0x02);
	up.setText(1, 5, "getline(cin,value);", 0x02);
	up.setText(1, 6, "ls.emplace_front({value,value,\"hello\",\"world\"});//相反", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	string temp = in.show();
	ls.emplace_front({ temp,temp,"hello","world" });
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";

	eatBuf();
	win::setCursor();
	m3.initMap();
	m3.setBorderLine('*');
	return;
}

void testInsert(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "iterator,T","iterator,int,T","iterator,iter,iter","...上一级" };
	m3.reset(items, 4);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			firstInsert(baseder, ls);
			break;
		case 1:
			secondInsert(baseder, ls);
			break;
		case 2:
			thirdInsert(baseder, ls);
			break;
		
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void firstInsert(Baseder& baseder, LinkList<string>& ls){
	Baseder up(baseder.getX(), 10, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//insert(const iterator& pos, const T& value)", 0x02);
	up.setText(1, 2, "//value 插入到pos位置之后", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "cin.get();", 0x02);
	up.setText(1, 5, "string value;", 0x02);
	up.setText(1, 6, "getline(cin,value);", 0x02);
	up.setText(1, 7, "ls.insert(ls.begin(),value);", 0x02);
	up.setText(1, 8, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	ls.insert(ls.begin(), in.show());
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";

	eatBuf();
	return;
}

void secondInsert(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 10, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//insert(const iterator& pos,int num,const T& value)", 0x02);
	up.setText(1, 2, "//插入num个value到pos位置之后", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "cin.get();", 0x02);
	up.setText(1, 5, "string value;", 0x02);
	up.setText(1, 6, "getline(cin,value);", 0x02);
	up.setText(1, 7, "ls.insert(ls.begin(),5,value);", 0x02);
	up.setText(1, 8, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	ls.insert(ls.begin(),5, in.show());
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";

	eatBuf();
	return;
}

void thirdInsert(Baseder& baseder, LinkList<string>& ls) {
	//Label in(baseder, 0, 0, baseder.getX());
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//insert(const iter& pos,const It begin,const It end)", 0x02);
	up.setText(1, 2, "//pos位置后插入[begin,end)", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "cin.get();", 0x02);
	up.setText(1, 5, "const char* temp[]={\"hello\",\"world\",\"  c++\"};", 0x02);
	up.setText(1, 6, "ls.insert(ls.begin(),temp,temp+3);", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	const char* temp[] = { "hello","world","  c++"};
	ls.insert(ls.begin(), temp, temp + 3);

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
}

void testEmplace(Menu& m3, Baseder& baseder, LinkList<string>& ls){
	setM3Title(m3);
	m3.setText(m3.getXH() - 10, m3.getYH(), "It,initializer_list<T>", 0xfd);
	
	Baseder up(baseder.getX(), 10, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//emplace(const iter& pos,initializer_list<T> ls)", 0x02);
	up.setText(1, 2, "//pos后面以列表的形式添加(可右值)", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "cin.get();", 0x02);
	up.setText(1, 5, "string value;", 0x02);
	up.setText(1, 6, "getline(cin,value);", 0x02);
	up.setText(1, 7, "ls.emplace(ls.begin(),{value,value,\"hello\",\"world\"});", 0x02);
	up.setText(1, 8, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();



	in.setStr("value:");
	string value = in.show();
	ls.emplace(ls.begin(), {value,value,"hello","world"});
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	
	eatBuf();
	win::setCursor();
	m3.initMap();
	m3.setBorderLine('*');
	return;
}

void delOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "pop_back","pop_front","clear","erase","erase_back","remove","remove_if","...上一级"};
	m2.reset(items, 8);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice = m2.show(choice, false)) {
		case 0:
			testPopBack(m3, baseder, ls);
			break;
		case 1:
			testPopFront(m3, baseder, ls);
			break;
		case 2:
			testClear(m3, baseder, ls);
			break;
		case 3:
			testErase(m3, baseder, ls);
			break;
		case 4:
			testEraseBack(m3, baseder, ls);
			break;
		case 5:
			testRemove(m3, baseder, ls);
			break;
		case 6:
			testRemoveIf(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}

}

void testPopBack(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 2, m3.getYH() - 1, "none", 0xfd);
	setM3Title(m3);

	//Label in(baseder, 0, 0, baseder.getX());
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//删除尾元素:", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "ls.pop_back();", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	ls.pop_back();

	down.initMap().setBorderLine().draw();
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testPopFront(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 2, m3.getYH() - 1, "none", 0xfd);
	setM3Title(m3);

	//Label in(baseder, 0, 0, baseder.getX());
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//删除首元素:", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "ls.pop_front();", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	ls.pop_front();

	down.initMap().setBorderLine().draw();
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testClear(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 2, m3.getYH() - 1, "none", 0xfd);
	setM3Title(m3);

	//Label in(baseder, 0, 0, baseder.getX());
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//全部清除:", 0x02);
	up.setText(1, 2, "ls.show();", 0x02);
	up.setText(1, 3, "cin.get();", 0x02);
	up.setText(1, 4, "ls.clear();", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	ls.clear();

	down.initMap().setBorderLine().draw();
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testErase(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "iterator","iterator,iterator","...上一级" };
	m3.reset(items, 3);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			eraseFirst(baseder, ls);
			break;
		case 1:
			eraseSecond(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void eraseFirst(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//erase(iterator pos)", 0x02);
	up.setText(1, 2, "//删除pos位置的元素", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "ls.erase(ls.begin());", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	//ls.show(down.getX() - 2
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls.erase(ls.begin());
	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void eraseSecond(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//erase(iterator begin,iterator end)", 0x02);
	up.setText(1, 2, "//删除[begin,end)区间元素", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "ls.erase(ls.begin(),ls.end());", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	//ls.show(down.getX() - 2
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls.erase(ls.begin(), ls.end());
	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void testEraseBack(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "iterator","iterator,iterator","...上一级" };
	m3.reset(items, 3);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			eraseBackFirst(baseder, ls);
			break;
		case 1:
			eraseBackSecond(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void eraseBackFirst(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//erase_back(iterator pos)", 0x02);
	up.setText(1, 2, "//删除pos位置后面的元素", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "ls.erase_back(ls.begin());", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	//ls.show(down.getX() - 2
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls.erase_back(ls.begin());
	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void eraseBackSecond(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);
	//in.setBorderLine();
	up.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//erase_back(iterator begin,iterator end)", 0x02);
	up.setText(1, 2, "//删除[begin+1,end)区间元素", 0x02);
	up.setText(1, 3, "ls.show();", 0x02);
	up.setText(1, 4, "ls.erase_back(ls.begin(),ls.end());", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	//ls.show(down.getX() - 2
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls.erase_back(ls.begin(), ls.end());
	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void testRemove(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 4, m3.getYH() - 1, "const T&", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 8, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//remove(value),移除所有value:", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string value;", 0x02);
	up.setText(1, yt++, "getline(cin,value);", 0x02);
	up.setText(1, yt++, "ls.remove(value);", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	ls.remove(in.show());

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testRemoveIf(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 5, m3.getYH() - 1, "function f", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//remove_if(f),f(data)为true的移除:", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string value;", 0x02);
	up.setText(1, yt++, "getline(cin,value);", 0x02);
	up.setText(1, yt++, "ls.remove_if([&value](const string&", 0x02);
	up.setText(1, yt++, "/*lambda表达式*/ data){return data==value;});", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value:");
	string value = in.show();
	ls.remove_if([&value](const string& data) {return data == value; });

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void findOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "find","find_if","...上一级" };
	m2.reset(items, 3);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice = m2.show(choice, false)) {
		case 0:
			testFind(m3, baseder, ls);
			break;
		case 1:
			testFindIf(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}

}

void testFind(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "const T&","const T&,iterator","...上一级" };
	m3.reset(items, 3);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			findFirst(baseder, ls);
			break;
		case 1:
			findSecond(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void findFirst(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//find(const T& value):", 0x02);
	up.setText(1, 2, "string value;", 0x02);
	up.setText(1, 3, "getline(cin,value);", 0x02);
	up.setText(1, 4, "ls.find(value);", 0x02);
	up.setText(1, 5, "ls.show();", 0x02);
	baseder.draw();

	in.setStr("value:");
	auto it=ls.find(in.show());
	down.gotoxy(1, 1);
	cout << it ;
	down.gotoxy(2, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void findSecond(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 8, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//find(const T& value,iterator pos):", 0x02);
	up.setText(1, 2, "//从pos位置开始查找value", 0x02);
	up.setText(1, 3, "string value;", 0x02);
	up.setText(1, 4, "getline(cin,value);", 0x02);
	up.setText(1, 5, "ls.find(value,ls.begin());", 0x02);
	up.setText(1, 6, "ls.show();", 0x02);
	baseder.draw();

	in.setStr("value:");
	auto it = ls.find(in.show(),ls.begin());
	down.gotoxy(1, 1);
	cout << it ;
	down.gotoxy(2, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void testFindIf(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "function","function,iterator","...上一级" };
	m3.reset(items, 3);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			findIfFirst(baseder, ls);
			break;
		case 1:
			findIfSecond(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void findIfFirst(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//find(function f):", 0x02);
	up.setText(1, 2, "//f为一个函数符", 0x02);
	up.setText(1, 3, "string value;", 0x02);
	up.setText(1, 4, "getline(cin,value);", 0x02);
	up.setText(1, 5, "ls.find_if([&value](const string& data){", 0x02);
	up.setText(1, 6, "/*lambda表达式*/ return data==value;});", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	in.setStr("value:");
	string value = in.show();
	auto it = ls.find_if([&value](const string& data) {return data == value; });
	down.gotoxy(1, 1);
	cout << it;
	down.gotoxy(2, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void findIfSecond(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 15);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	in.setBorderLine();
	down.setBorderLine();


	up.setText(1, 1, "//find(function f,iterator pos):", 0x02);
	up.setText(1, 2, "//f为一个函数符,从pos位置开始查找", 0x02);
	up.setText(1, 3, "string value;", 0x02);
	up.setText(1, 4, "getline(cin,value);", 0x02);
	up.setText(1, 5, "ls.find_if([&value](const string& data){", 0x02);
	up.setText(1, 6, "/*lambda表达式*/ return data==value;},ls.begin());", 0x02);
	up.setText(1, 7, "ls.show();", 0x02);
	baseder.draw();

	in.setStr("value:");
	string value = in.show();
	auto it = ls.find_if([&value](const string& data) {return data == value; },ls.begin());
	down.gotoxy(1, 1);
	cout << it;
	down.gotoxy(2, 1);
	cout << "按回车键继续...";
	win::setCursor(true);
	eatBuf();
	win::setCursor();
}

void replaceOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "replace","replace_if","deal_if","reserve","swap","...上一级" };
	m2.reset(items, 6);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice = m2.show(choice, false)) {
		case 0:
			testReplace(m3, baseder, ls);
			break;
		case 1:
			testReplaceIf(m3, baseder, ls);
			break;
		case 2:
			testDealIf(m3, baseder, ls);
			break;
		case 3:
			testReserve(m3, baseder, ls);
			break;
		case 4:
			testSwap(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}

}

void testReplace(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 9, m3.getYH() - 1, "const T&,const T&", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Label old(baseder, 0, up.getY() - 1, 13);
	Label neIn(baseder,old.getX(), up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	old.setBorderLine();
	neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//replace(old,new),old替换为new:", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string old,newValue;", 0x02);
	up.setText(1, yt++, "getline(cin,old);", 0x02);
	up.setText(1, yt++, "getline(cin,newValue);", 0x02);
	up.setText(1, yt++, "ls.replace(old,newValue);", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	old.setStr("old");
	neIn.setStr("newValue");
	string ol = old.show();
	ls.replace(ol,neIn.show());

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testReplaceIf(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 10, m3.getYH() - 1, "function f,const T&", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 10, 0, 0, baseder);
	Label old(baseder, 0, up.getY() - 1, 13);
	Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	old.setBorderLine();
	neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//replace_if(f,newValue),f(data)为true替换为new:", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string old,newValue;", 0x02);
	up.setText(1, yt++, "getline(cin,old);", 0x02);
	up.setText(1, yt++, "getline(cin,newValue);", 0x02);
	up.setText(1, yt++, "ls.replace_if([&old](const string& data)", 0x02);
	up.setText(1, yt++, "/*lambda*/ {return data==old;},newValue);", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	old.setStr("old");
	string ol = old.show();
	neIn.setStr("newValue");
	ls.replace_if([&ol](const string& data) {return data == ol; }, neIn.show());

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testDealIf(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "function,function","iter,iter,func,func","iter,func,func","...上一级"};
	m3.reset(items, 4);
	setM3Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			dealIfFirst(baseder, ls);
			break;
		case 1:
			dealIfSecond(baseder, ls);
			break;
		case 2:
			dealIfThird(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void dealIfFirst(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 11, 0, 0, baseder);
	Label old(baseder, 0, up.getY() - 1, 13);
	Label neIn(baseder, old.getX(), up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	old.setBorderLine();
	neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//(fj,fd),[begin(),end())区间fj(data)为true时fd(data)", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string old,newValue;", 0x02);
	up.setText(1, yt++, "getline(cin,old);", 0x02);
	up.setText(1, yt++, "getline(cin,newValue);", 0x02);
	up.setText(1, yt++, "ls.deal_if(", 0x02);
	up.setText(1, yt++, "/*lambda*/[&old](const string& t){return t==old;},", 0x02);
	up.setText(1, yt++, "/*lambda*/[&newValue](string& t){t=newValue;});", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	old.setStr("old");
	neIn.setStr("newValue");
	string ol = old.show();
	string newValue = neIn.show();
	ls.deal_if([&ol](const string& t) {return t == ol; }, [&newValue](string& t) {t = newValue; });

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
}

void dealIfSecond(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 11, 0, 0, baseder);
	Label old(baseder, 0, up.getY() - 1, 13);
	Label neIn(baseder, old.getX(), up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	old.setBorderLine();
	neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//(begin,end,fj,fd),[begin,end)fj(data)为true时fd(data)", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string old,newValue;", 0x02);
	up.setText(1, yt++, "getline(cin,old);", 0x02);
	up.setText(1, yt++, "getline(cin,newValue);", 0x02);
	up.setText(1, yt++, "ls.deal_if(ls.begin(),ls.end(),", 0x02);
	up.setText(1, yt++, "/*lambda*/[&old](const string& t){return t==old;},", 0x02);
	up.setText(1, yt++, "/*lambda*/[&newValue](string& t){t=newValue;});", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	old.setStr("old");
	neIn.setStr("newValue");
	string ol = old.show();
	string newValue = neIn.show();
	ls.deal_if(ls.begin(), ls.end(), [&ol](const string& t) {return t == ol; }, [&newValue](string& t) {t = newValue; });

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
}

void dealIfThird(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 11, 0, 0, baseder);
	Label old(baseder, 0, up.getY() - 1, 13);
	Label neIn(baseder, old.getX(), up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	old.setBorderLine();
	neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//(pos,fj,fd),[pos,end())fj(data)为true时fd(data)", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "string old,newValue;", 0x02);
	up.setText(1, yt++, "getline(cin,old);", 0x02);
	up.setText(1, yt++, "getline(cin,newValue);", 0x02);
	up.setText(1, yt++, "ls.deal_if(ls.begin(),", 0x02);
	up.setText(1, yt++, "/*lambda*/[&old](const string& t){return t==old;},", 0x02);
	up.setText(1, yt++, "/*lambda*/[&newValue](string& t){t=newValue;});", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	old.setStr("old");
	neIn.setStr("newValue");
	string ol = old.show();
	string newValue = neIn.show();
	ls.deal_if(ls.begin(), [&ol](const string& t) {return t == ol; }, [&newValue](string& t) {t = newValue; });

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
}

void testReserve(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 2, m3.getYH() - 1, "none", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 8, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() -1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//翻转元素", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "ls.reserve(ture);", 0x02);
	up.setText(1, yt++, "//如果是false不改变本体并返回一个倒序链表", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls.reserve(true);
	down.gotoxy(ls.show(down.getX() - 2, down, y+1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testSwap(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 6, m3.getYH() - 1, "LinkList<T>", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//交换元素", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "LinkList<string> temp(10,\"hello\");", 0x02);
	up.setText(1, yt++, "ls.swap(temp);", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);
	LinkList<string> temp(10, "hello");
	ls.swap(temp);
	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void elseOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "数据接口","sort","sort_by","unique","unique_if","...上一级" };
	m2.reset(items, 6);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice = m2.show(choice, false)) {
		case 0:
			testData(m3, baseder, ls);
			break;
		case 1:
			testSort(m3, baseder, ls);
			break;
		case 2:
			testSortBy(m3, baseder, ls);
			break;
		case 3:
			testUnique(m3, baseder, ls);
			break;
		case 4:
			testUniqueIf(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}

}

void testData(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "empty()","operator[]","at(index)","front()","back()","size()" };
	m3.setText(m3.getXH() - 4, m3.getY() / 7 * 1, items[0], 0xfd);
	m3.setText(m3.getXH() - 5, m3.getY() / 7 * 2, items[1], 0xfd);
	m3.setText(m3.getXH() - 5, m3.getY() / 7 * 3, items[2], 0xfd);
	m3.setText(m3.getXH() - 4, m3.getY() / 7 * 4, items[3], 0xfd);
	m3.setText(m3.getXH() - 3, m3.getY() / 7 * 5, items[4], 0xfd);
	m3.setText(m3.getXH() - 3, m3.getY() / 7 * 6, items[5], 0xfd);
	setTitle(m3,"函数名称");
	
	Baseder up(baseder.getX(), 14, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//数据接口", 0x02);
	up.setText(1, yt++, "try{", 0x02);
	up.setText(1, yt++, "   //是否为空", 0x02);
	up.setText(1, yt++, "   cout << boolalpha << ls.empty()<<endl;", 0x02);
	up.setText(1, yt++, "   //第一个元素,如果没有元素at会引发异常", 0x02);
	up.setText(1, yt++, "   cout<<ls.at(0)<<ls[0]<<ls.front()<<endl;", 0x02);
	up.setText(1, yt++, "   //最后一个元素", 0x02);
	up.setText(1, yt++, "   cout<<ls.back()<<endl;", 0x02);
	up.setText(1, yt++, "}", 0x02);
	up.setText(1, yt++, "catch(...){", 0x02);
	up.setText(1, yt++, "    cout << \"没有元素\"<<endl;", 0x02);
	up.setText(1, yt++, "}", 0x02);
	baseder.draw();

	win::setCursor(true);
	yt = 1;
	down.gotoxy(yt++, 1);
	try {//如果没有元素会引发异常
		cout << boolalpha << ls.empty();
		down.gotoxy(yt++, 1);
		cout << ls.at(0) << ls[0] << ls.front();
		down.gotoxy(yt++, 1);
		cout << ls.back();
	}
	catch (...) {
		cout << "没有元素";
	}
	down.gotoxy(yt++, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testSort(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 2, m3.getYH() - 1, "none", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 6, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//排序,要求T类型有<操作", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "ls.sort();", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);

	ls.sort();

	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testSortBy(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 5, m3.getYH() - 1, "function f", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//f(data1,data2)为ture时判定为data2<data1来排序", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "ls.sort_by([](const string& d1,const string& d2)", 0x02);
	up.setText(1, yt++, "/*lambda*/ {return d2<d1;});", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);
	
	ls.sort_by([](const string& d1, const string& d2) {return d2 < d1; });

	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testUnique(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 2, m3.getYH() - 1, "none", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 6, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//消除相邻重复元素,要求T类型有==操作", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "ls.unique();", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);
	
	ls.unique();

	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testUniqueIf(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 5, m3.getYH() - 1, "function f", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 7, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//f(data1,data2)为ture时删除data2", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "ls.unique_if([](const string& d1,const string& d2)", 0x02);
	up.setText(1, yt++, "/*lambda*/ {return d1==d2;});", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);
	ls.unique_if([](const string& d1, const string& d2) {return d1 == d2; });

	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void aboutSTL(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "iterator","inserter","for_each","fill","...上一级"};
	m2.reset(items, 5);
	setM2Title(m2);
	int choice = 0;
	while (1) {
		switch (choice = m2.show(choice, false)) {
		case 0:
			testIterator(m3, baseder, ls);
			break;
		case 1:
			testInserter(m3, baseder, ls);
			break;
		case 2:
			testForEach(m3, baseder, ls);
			break;
		case 3:
			testFill(m3, baseder, ls);
			break;
		default:
			m2.initMap();
			m2.setBorderLine('*');
			return;
		}
	}
}

void testIterator(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 5, m3.getYH() - 1, "正向迭代器", 0xfd);
	setTitle(m3,"迭代器");

	Baseder up(baseder.getX(), 13, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//为LinkList类设计了正向迭代器", 0x02);
	up.setText(1, yt++, "  //迭代器声明", 0x02);
	up.setText(1, yt++, "LinkList<string>::iterator it=ls.begin();//头迭代器", 0x02);
	up.setText(1, yt++, "if(!ls.empty()){//ls不为空时", 0x02);
	up.setText(1, yt++, "    cout<<*it<<endl;//头,可解引用迭代器", 0x02);
	up.setText(1, yt++, "    it=ls.end();//尾迭代器", 0x02);
	up.setText(1, yt++, "    cout<<it<<endl;//尾为nullptr,定义了友元来输出*iter", 0x02);
	up.setText(1, yt++, "}", 0x02);
	up.setText(1, yt++, "for(it=ls.begin();it!=ls.end();++it){", 0x02);
	up.setText(1, yt++, "    cout<<it;//通过迭代器遍历链表,定义了友元来输出*iter", 0x02);
	up.setText(1, yt++, "}", 0x02);
	baseder.draw();

	win::setCursor(true);

	yt = 0;
	if (!ls.empty()) {
		down.gotoxy(++yt, 1);
		LinkList<string>::iterator it = ls.begin();
		cout << *it;
		down.gotoxy(++yt, 1);
		it = ls.end();
		cout << it;
	}
	

	down.gotoxy(ls.show(down.getX() - 2, down, yt + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testInserter(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "back_inserter","front_inserter","inserter","...上一级" };
	m3.reset(items, 4);
	setM2Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			inserterBack(baseder, ls);
			break;
		case 1:
			inserterFront(baseder, ls);
			break;
		case 2:
			inserterDemo(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void inserterBack(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//back_inserter(ls)插入到ls的后面", 0x02);
	up.setText(1, yt++, "#include <algorithm> //STL算法库", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "auto it = back_inserter(ls);", 0x02);
	up.setText(1, yt++, "*it = \"back\";", 0x02);
	up.setText(1, yt++, "*it = \"insert\";", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	yt = ls.show(down.getX() - 2, down, 1, 1);

	auto it = back_inserter(ls);
	*it = "back";
	*it = "insert";

	down.gotoxy(ls.show(down.getX() - 2, down, yt + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
}

void inserterFront(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//front_inserter(ls)插入到ls的前面", 0x02);
	up.setText(1, yt++, "#include <algorithm> //STL算法库", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "auto it = front_inserter(ls);", 0x02);
	up.setText(1, yt++, "*it = \"front\";", 0x02);
	up.setText(1, yt++, "*it = \"insert\";", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	yt = ls.show(down.getX() - 2, down, 1, 1);

	auto it = front_inserter(ls);
	*it = "front";
	*it = "insert";

	down.gotoxy(ls.show(down.getX() - 2, down, yt + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
}

void inserterDemo(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 9, 0, 0, baseder);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//inserter(ls,pos)从ls的pos位置插入", 0x02);
	up.setText(1, yt++, "#include <algorithm> //STL算法库", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "auto it = inserter(ls, ls.end());", 0x02);
	up.setText(1, yt++, "*it = \"insert\";", 0x02);
	up.setText(1, yt++, "*it = \"back\";", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	yt = ls.show(down.getX() - 2, down, 1, 1);

	auto it = inserter(ls, ls.end());
	*it = "insert";
	*it = "end()";

	down.gotoxy(ls.show(down.getX() - 2, down, yt + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
}

void testForEach(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	m3.setText(m3.getXH() - 9, m3.getYH() - 1, "iter,iter,function", 0xfd);
	setM3Title(m3);

	Baseder up(baseder.getX(), 8, 0, 0, baseder);
	//Label old(baseder, 0, up.getY() - 1, 13);
	//Label neIn(baseder, old.getX() - 1, up.getY() - 1, 18);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1, 0, up.getY() - 1, baseder);

	up.setBorderLine();
	//old.setBorderLine();
	//neIn.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//(begin,end,func)[begin,end)区间执行func(data)", 0x02);
	up.setText(1, yt++, "#include <algorithm> //STL算法库", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "for_each(ls.begin(),ls.end(),[](string& data){", 0x02);
	up.setText(1, yt++, "/*lambda表达式*/               data=\"each\";})", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	int y = ls.show(down.getX() - 2, down, 1, 1);

	for_each(ls.begin(), ls.end(), [](string& data) {data = "each"; });

	down.gotoxy(ls.show(down.getX() - 2, down, y + 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	win::setCursor();
	m3.initMap().setBorderLine('*');
}

void testFill(Menu& m3, Baseder& baseder, LinkList<string>& ls) {
	MenuItem items = { "fill","fill_n","...上一级" };
	m3.reset(items, 3);
	setM2Title(m3);
	int choice = 0;
	while (1) {
		switch (choice = m3.show(choice, false)) {
		case 0:
			fillLs(baseder, ls);
			break;
		case 1:
			fillNLs(baseder, ls);
			break;
		default:
			m3.initMap();
			m3.setBorderLine('*');
			return;
		}
	}
}

void fillLs(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 10, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 14);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//fill(first,last,value)[first,last)全设置为value", 0x02);
	up.setText(1, yt++, "#include <algorithm> //STL算法库", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "cin.get();", 0x02);
	up.setText(1, yt++, "string value;", 0x02);
	up.setText(1, yt++, "getline(cin,value);", 0x02);
	up.setText(1, yt++, "fill(ls.begin(),ls.end(),value);", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value");
	fill(ls.begin(), ls.end(), in.show());

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
}

void fillNLs(Baseder& baseder, LinkList<string>& ls) {
	Baseder up(baseder.getX(), 10, 0, 0, baseder);
	Label in(baseder, 0, up.getY() - 1, 14);
	Baseder down(baseder.getX(), baseder.getY() - up.getY() + 1 - 2, 0, up.getY() + 1, baseder);

	up.setBorderLine();
	down.setBorderLine();

	int yt = 1;
	up.setText(1, yt++, "//fill(pos,n,value)pos后设置n个value", 0x02);
	up.setText(1, yt++, "#include <algorithm> //STL算法库", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	up.setText(1, yt++, "cin.get();", 0x02);
	up.setText(1, yt++, "string value;", 0x02);
	up.setText(1, yt++, "getline(cin,value);", 0x02);
	up.setText(1, yt++, "fill_n(front_inserter(ls),10,value);", 0x02);
	up.setText(1, yt++, "ls.show();", 0x02);
	baseder.draw();

	win::setCursor(true);
	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();

	in.setStr("value");
	fill_n(front_inserter(ls),10,in.show());

	down.gotoxy(ls.show(down.getX() - 2, down, 1, 1) + 1, 1);
	cout << "按回车键继续...";
	eatBuf();
	win::setCursor();
}