//通讯录实现

#ifndef MAILLIST_H
#define MAILLIST_H
#include <string>
#include <iostream>
#include "Base.h"
#include "LinkList.h"

class MailList {//通讯录
	struct data {
		string id;//学号
		string name;//姓名
		string tel;//号码
		string QQ;//QQ
		data(const char* str[]) :id(str[0]), name(str[1]), tel(str[2]), QQ(str[3]) {};
		data(const string& id, const string& name, const string& tel, const string& QQ) :id(id), name(name),
			tel(tel), QQ(QQ) {};
		data() {};
	};
	LinkList<data> ls;//保存数据的容器
	Base& base;//自定义窗口类(更多细节请参考Base.h文件)
public:
	using data_type = data;

	MailList(Base& base,bool mode = true);//默认对象创建时读取文件(mailList.txt),可设置为选择false选择不读取
	~MailList() { save(); };//析构函数调用save()

	MailList& save(const string& fileName="mailList.txt");//保存数据，默认保存到mailList.txt，也可自己设置
	MailList& load(const string& fileName,Baseder& baseder,int& index);//从文件中读取数据,以追加的形式添加
	MailList& show(Baseder& baseder, int& index);//展示函数,在baseder窗口展示数据
												  //默认展示第一页(index)，利用一个静态变量来记录一页显示多少个数据
	MailList& addEle(Baseder& base,int& index);//添加元素

	
	int getMaxIndex(int num) { return (ls.size() - 1) / num; };//最大的页数
	int getIndex(int index, int num) { return index / num; }//当前下标页数
	//流中读取数据(追加),这里主要用在文件,从控制台读取数据的情况不用这个函数,所以返回值设置为void
	friend void operator>>(istream& is, MailList& ml);
	//保存文件至os
	friend ostream& operator<<(ostream& os, MailList& ml);
	string inputFileName(Baseder& baseder);//返回值为用户输入的文件名
	LinkList<data>::iterator find_by(Baseder& baseder,bool mode=true);//查询

	MailList& insertEle(Baseder& baseder,int &index);//插入元素
	MailList& delEle(Baseder& baseder, int& index);//删除元素
	MailList& replaceEle(Baseder& baseder, int& index);//修改元素
	MailList& reserveEle(Baseder& baseder, int& index) {//反转
		ls.reserve(true);
		show(baseder, index = 0);
		return *this;
	}
	MailList& sortAndUnique(Baseder& baseder, int& index);

	void start();//开始演示
};
#endif