//测试链表功能

#ifndef TESTLINKLIST_H
#define TESTLINKLIST_H
#include "Base.h"
#include "LinkList.h"
#include <conio.h>
#include <iostream>
using namespace std;
void testLinkList(Base &base);//测试链表类功能


void testConstruct(Menu& m2, Menu& m3, Baseder& baseder,LinkList<string>& ls);//
																			//构造相关（构造,析构,等于）测试
void startIO(Menu& m3, Baseder& baseder, LinkList<string>& ls);//通过IO来构造list
void stdIO(Baseder& baseder, LinkList<string>& ls);//标准IO
void fileIO(Baseder& baseder, LinkList<string>& ls);//文件IO

void startConstruct(Menu& m3, Baseder& baseder, LinkList<string>& ls);//构造
void defaultConstruct(Baseder& baseder, LinkList<string>& ls);//默认构造
void listConstruct(Baseder& baseder, LinkList<string>& ls);//列表构造
void valueConstruct(Baseder& baseder, LinkList<string>& ls);//初值构造
void valueNumConstruct(Baseder& baseder, LinkList<string>& ls);//num个value构造
void cpyConstruct(Baseder& baseder, LinkList<string>& ls);//复制构造
void refConstruct(Baseder& baseder, LinkList<string>& ls);//右值引用构造
void iteConstruct(Baseder& baseder, LinkList<string>& ls);//迭代器构造

void startEqual(Menu& m3, Baseder& baseder, LinkList<string>& ls);//operator=
void equalSelf(Baseder& baseder, LinkList<string>& ls);//自己赋值自己
void equalElse(Baseder& baseder, LinkList<string>& ls);//赋值其它对象

void startDecon(Menu& m3, Baseder& baseder, LinkList<string>& ls);//析构

void addOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls);//
																	//添加元素的操作
void testPushBack(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testEmplaceBack(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testPushFront(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testEmplaceFront(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testInsert(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void firstInsert(Baseder& baseder, LinkList<string>& ls);//第一种插入方式
void secondInsert(Baseder& baseder, LinkList<string>& ls);//第二种插入方式
void thirdInsert(Baseder& baseder, LinkList<string>& ls);//第二种插入方式

void testEmplace(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void delOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls);//
															//删除元素的操作
void testPopBack(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testPopFront(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testClear(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testErase(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void eraseFirst(Baseder& baseder, LinkList<string>& ls);//第一种删除方式
void eraseSecond(Baseder& baseder, LinkList<string>& ls); // 第二种删除方式

void testEraseBack(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void eraseBackFirst(Baseder& baseder, LinkList<string>& ls);//第一种删除方式
void eraseBackSecond(Baseder& baseder, LinkList<string>& ls); // 第二种删除方式

void testRemove(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testRemoveIf(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void findOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls);//
																	//查找元素的操作
void testFind(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void findFirst(Baseder& baseder, LinkList<string>& ls);//第一种查找方式
void findSecond(Baseder& baseder, LinkList<string>& ls); // 第二种查找方式

void testFindIf(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void findIfFirst(Baseder& baseder, LinkList<string>& ls);//第一种查找方式
void findIfSecond(Baseder& baseder, LinkList<string>& ls); // 第二种查找方式

void replaceOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls);//
																	//修改元素的操作
void testReplace(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testReplaceIf(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testDealIf(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void dealIfFirst(Baseder& baseder, LinkList<string>& ls);//第一种处理方式
void dealIfSecond(Baseder& baseder, LinkList<string>& ls); // 第二种处理方式
void dealIfThird(Baseder& baseder, LinkList<string>& ls); // 第三种处理方式

void testReserve(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testSwap(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void elseOpt(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls);//
																	//其它操作
void testData(Menu& m3, Baseder& baseder, LinkList<string>& ls);//测试数据接口
void testSort(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testSortBy(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testUnique(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void testUniqueIf(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void aboutSTL(Menu& m2, Menu& m3, Baseder& baseder, LinkList<string>& ls);//STL测试
void testIterator(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void testInserter(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void inserterBack(Baseder& baseder, LinkList<string>& ls);
void inserterFront(Baseder& baseder, LinkList<string>& ls);
void inserterDemo(Baseder& baseder, LinkList<string>& ls);

void testForEach(Menu& m3, Baseder& baseder, LinkList<string>& ls);

void testFill(Menu& m3, Baseder& baseder, LinkList<string>& ls);
void fillLs(Baseder& baseder, LinkList<string>& ls); // 第二种处理方式
void fillNLs(Baseder& baseder, LinkList<string>& ls); // 第三种处理方式


inline void setM2Title(Menu& m2) {//重复操作声明为内联
	Label title(m2, 0, m2.getY() - 3, m2.getX());
	title.setText(title.getXH() - 4, 1, "函数名称", 0xf4);
	title.setBkColor(0xf4);
	title.setBorderLine();
	title.draw();
}

inline void setM3Title(Menu& m3) {//重复操作声明为内联
	Label title(m3, 0, m3.getY() - 3, m3.getX());
	title.setText(title.getXH() - 4, 1, "参数形式", 0xf4);
	title.setBkColor(0xf4);
	title.setBorderLine();
	title.draw();
}

inline void setTitle(Menu& m3,const char* str) {//重复操作声明为内联
	Label title(m3, 0, m3.getY() - 3, m3.getX());
	title.setText(title.getXH() - 4, 1, str, 0xf4);
	title.setBkColor(0xf4);
	title.setBorderLine();
	title.draw();
}

inline void eatBuf() {//清空输入缓冲区
	while (cin.peek() != '\n') {
		cin.get();
	}
	cin.get();
}

#endif