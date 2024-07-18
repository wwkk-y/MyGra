//存储款业务
#ifndef DEPOSIT_H
#define DEPOSIT_H
#pragma once
#include <string>
#include "LinkList.h"
#include "Base.h"
#include <iostream>

using namespace std;
class depositBusiness
{
	struct data {
		string name;//户名
		string opt;//操作 +开头存入,-开头取出,' '开头表示开户
		string date;//日期,动态获取当日时间,为none不输出,表示开户
		string balan;//余额
		data(string name, string opt, string date,string banlan) :name(name), opt(opt), date(date),balan(banlan) {};
		data() {};
	};
	LinkList<data> ls;//保存数据的容器
	Base& base;//自定义窗口类(更多细节请参考Base.h文件)
public:
	using data_type = data;

	depositBusiness(Base& base, bool mode = true);//默认对象创建时读取文件(depositBusiness.txt),可设置为选择false选择不读取
	~depositBusiness() { save(); };//析构函数调用save()

	depositBusiness& save(const string& fileName="depositBusiness.txt");//保存文件
	depositBusiness& read(const string& fileName="depositBusiness.txt");//读取文件

	//流中读取数据(追加),这里主要用在文件,从控制台读取数据的情况不用这个函数,所以返回值设置为void
	friend void operator>>(istream& is, depositBusiness& ml);
	//保存文件至os
	friend ostream& operator<<(ostream& os, depositBusiness& ml);

	int show(string& name, int& index);
	depositBusiness& findOpt(string& name);
	depositBusiness& addOpt(string& name);
	depositBusiness& takeOpt(string& name);
	data getLast(string& name);

	depositBusiness& login(string name);
	string getDate();//时间
	string getName();
	void addUser();
	void start();//入口
};

inline void operator>>(istream& is, depositBusiness& ml)
{
	string name;
	string opt;
	string date;
	string banlan;
	while (is >> name >> opt >> date>>banlan) {
		ml.ls.push_back(depositBusiness::data(name, opt, date,banlan));
	}
}

inline ostream& operator<<(ostream& os, depositBusiness& ml)
{
	for (auto& p : ml.ls) {
		os << p.name << "  " << p.opt << "  " << p.date <<"  "<<p.balan << endl;
	}
	return os;
}

#endif