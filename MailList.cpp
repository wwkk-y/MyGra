#include "MailList.h"
#include <iostream>
#include <fstream>
#include <algorithm>

MailList::MailList(Base& base, bool mode) :base(base)
{
	if (mode) {
		ifstream fin("mailList.txt");
		fin >> *this;
		fin.close();
	}
}

MailList& MailList::save(const string& fileName) {
	ofstream fo(fileName);
	fo << *this;
	fo.close();
	return *this;
}

MailList& MailList::load(const string& fileName,Baseder& baseder,int& index) {
	Baseder tempBa(baseder);
	if (index != getMaxIndex(15)) {
		show(baseder, index = -1);
	}
	ifstream fin(fileName);
	Baseder bas(23, 7, baseder.getXH() - 10, baseder.getYH() - 4, baseder);
	MenuItem items = { "以追加方式添加","以覆盖方式添加"};
	bas.draw();
	Menu menu(bas, items, 2);
	menu.setBorderColor(0xfd);
	if (menu.show(0,false)) {
		ls.clear();
	}
	fin >> *this;
	fin.close();
	bas.close();
	tempBa.close();
	show(baseder, index);
	return *this;
}

MailList& MailList::show(Baseder& baseder, int& index) {
	baseder.initMap();
	static const int eleNum = 5*3;//一排5个,3排数据
	if (index >getMaxIndex(eleNum)) {
		//没有这么多元素
		index = 0;
	}
	else if (index < 0) {
		index = getMaxIndex(eleNum);
	}
	LabelBoxArr lba1(baseder, eleNum / 3, 4, 1, 1);
	LabelBoxArr lba2(baseder, eleNum / 3, 4, 1, lba1.getY()+1);
	LabelBoxArr lba3(baseder, eleNum / 3, 4, 1, lba1.getY()*2+1, 20);
	const char* str[] = { "学号","姓名","号码","QQ号" };
	for (int i = 0; i < eleNum/3; ++i) {
		lba1.getLb(i).setStr(str);
		lba2.getLb(i).setStr(str);
		lba3.getLb(i).setStr(str);
	}
	auto it = ls.begin() + index * eleNum;
	int what = 1;
	int lsIndex = 0;
	while (it) {
		const char* strls[] = { (*it).id.c_str(),(*it).name.c_str() ,(*it).tel.c_str() ,(*it).QQ.c_str()};
		switch (what) {
		case 1:
			lba1.getLb(lsIndex).setStrR(strls);
			break;
		case 2:
			lba2.getLb(lsIndex).setStrR(strls);
			break;
		case 3:
			lba3.getLb(lsIndex).setStrR(strls);
			break;
		}
		++lsIndex;
		if (lsIndex == 5) {
			lsIndex = 0;
			++what;
			if (what > 3) {
				break;
			}
		}
		++it;
	}

	lba1.showAll();
	lba2.showAll();
	lba3.showAll();
	char strt[20];
	sprintf_s(strt, "第%d页", index + 1);
	baseder.setText(lba1.getX(), 1, strt);
	baseder.setBufColor(1, lba1.getX(), lba1.getX() + 5, 0xf6);
	return *this;
}

MailList& MailList::addEle(Baseder& baseder,int& index) {
	Baseder tba(baseder);
	if (index < getMaxIndex(15)) {
		show(baseder, index = -1);
	}
	Baseder bas(22,12,baseder.getXH()-11,baseder.getYH()-6, baseder);
	bas.setText(bas.getXH() - 5, 1, "请输入信息", 0xfd);
	bas.setBorder(' ', 0xfd);
	LabelBox lb(bas, 4, 1, 2);
	const char* str[] = { "学号","姓名","号码","QQ号" };
	lb.setStr(str);
	lb.show();
	ls.push_back(data(lb.getStrR(0), lb.getStrR(1), lb.getStrR(2), lb.getStrR(3)));
	tba.close();
	show(baseder, index = -1);
	return *this;
}

void operator>>(istream& is, MailList& ml) {
	MailList::data temp;
	while (is >> temp.id >> temp.tel >> temp.name >> temp.QQ) {//一直读到文件尾
		ml.ls.push_back(temp);//没有读取失败就添加元素
	}
}

ostream& operator<<(ostream& os, MailList& ml) {
	for (auto& i : ml.ls) {
		os << i.id << "  " << i.name << "  " << i.tel << "  " << i.QQ << endl;
	}
	return os;
}

string MailList::inputFileName(Baseder& baseder) {
	Baseder tempBa(baseder);
	Baseder bas(20, 6, baseder.getXH() - 10, baseder.getYH() - 3, baseder);
	InputTips in(bas, 3, 3);
	in.setTips("mailList.txt");
	bas.setBorderColor(0xfd);
	bas.setText(bas.getXH() - 6, 2, "请输入文件名");
	bas.draw();
	string temp = in.show();
	bas.close();//恢复原样
	tempBa.close();
	return temp;
}

LinkList<MailList::data>::iterator MailList::find_by(Baseder& baseder,bool mode) {
	Baseder ba(baseder);
	Label lb(ba, ba.getXH()-8, 2,18);
	lb.setStr(" 请选择查找方式");
	lb.showAll();
	MenuItem items = { "学号","姓名","号码","QQ号" };
	Menu menu(ba.getX()-2,ba.getY()-6,1,5,ba,items,4);
	menu.setBorder(' ');
	int tIndex=menu.show(0,false);
	lb.setStr("       查找");
	lb.showAll();
	Label lbTemp(ba,1,1,30);
	lbTemp.setStr(string("请输入") + items[tIndex]);
	string temp = lbTemp.show();
	LinkList<data>::iterator pos=ls.begin();
	switch (tIndex) {
	case 0:
		pos=ls.find_if([&temp](const data& d) {return d.id == temp; });
		break;
	case 1:
		pos = ls.find_if([&temp](const data& d) {return d.name == temp; });
		break;
	case 2:
		pos = ls.find_if([&temp](const data& d) {return d.tel == temp; });
		break;
	case 3:
		pos = ls.find_if([&temp](const data& d) {return d.QQ == temp; });
		break;
	}
	LabelBox lbx(ba, 4, 5, 5);
	if (pos) {
		lbx.setStr(items);
		const char* itemsR[] = { (*pos).id.c_str(),(*pos).name.c_str() ,(*pos).tel.c_str() ,(*pos).QQ.c_str() };
		lbx.setStrR(itemsR);
		lbx.showAll();	
	}
	else {
		lbx.setText(lbx.getXH()-7, lbx.getYH(), "未查找到该信息");
		lbx.draw();
	}
	if (mode) {//只有展示时这一部分才需要
		ba.setText(2, 17, "按回车键继续...");
		ba.show();
		cin.get();
		ba.close();
	}
	return pos;
}

MailList& MailList::insertEle(Baseder& baseder,int &index) {
	Baseder tba(baseder);
	Baseder ba(28, 18, baseder.getXH() - 14, baseder.getYH() - 9, baseder);
	ba.setBorderColor(0xfd);
	ba.setText(ba.getXH() - 4, 2, "插入元素");
	ba.draw();
	Label lb(ba, 4, 4);
	lb.setStr("下标位置:");
	int tIndex=stoi(lb.show());
	LabelBox lbx(ba,4,4,7);
	MenuItem items = { "学号","姓名","号码","QQ号" };
	lbx.setStr(items);
	lbx.show();
	data dataTemp(lbx.getStrR(0), lbx.getStrR(1), lbx.getStrR(2), lbx.getStrR(3));//需要插入的数据

	tba.close();
	if (tIndex <= 0) {//头部插入
		ls.push_front(dataTemp);
		show(baseder, index = 0);
	}
	else if (tIndex >= ls.size()) {//尾部插入
		ls.push_back(dataTemp);
		show(baseder, index = -1);
	}
	else {//其它情况
		ls.insert(LinkList<data>::iterator(ls, tIndex - 1), dataTemp);
		show(baseder, index=getIndex(tIndex,15));
	}

	return *this;
}
MailList& MailList::delEle(Baseder& baseder, int& index) {
	//先查找
	LinkList<data>::iterator pos=find_by(baseder,false);
	Baseder ba(22,base.getY()-14-1, 4, 14,baseder );
	ba.setBorder(' ');
	//再删除元素
	if (!pos) {//pos为end
		ba.setText(1, 1, "按回车键继续...");
		ba.show();
		cin.get();
		show(baseder, index);
		return *this;
	}
	Label lb(ba, 1, 1, 20);
	lb.setStr("是否删除?<y/n>:");
	string choice=lb.show();
	if (choice == "y" || choice == "Y") {
		ls.erase(pos);
	}
	show(baseder, index);
	return *this;
}

MailList& MailList::replaceEle(Baseder& baseder, int& index) {
	LinkList<data>::iterator pos = find_by(baseder, false);
	Baseder ba(22, base.getY() - 14 - 1, 4, 14, baseder);
	ba.setBorder(' ');
	if (!pos) {//没找到
		ba.setText(1, 1, "按回车键继续...");
		ba.show();
		cin.get();
		show(baseder, index);
		return *this;
	}
	LabelBox lbx(ba, 4,1,3);
	MenuItem items = { "学号","姓名","号码","QQ号" };
	lbx.setStr(items);
	MenuItem itemsR = { (*pos).id.c_str(), (*pos).name.c_str(), (*pos).tel.c_str(), (*pos).QQ.c_str() };
	lbx.setStrR(itemsR);
	Label lb(ba, 0, 0,22);
	lb.setStr("请修改需要替代的值");
	lb.showAll();
	lbx.show();
	data dataTemp(lbx.getStrR(0), lbx.getStrR(1), lbx.getStrR(2), lbx.getStrR(3));
	ls.replace_if([&pos](const data& da) {return da.id == (*pos).id; }, dataTemp);//所有学号相同的全部替换
																				 //(如果正常使用,不会存在相同的一个学号)
	
	show(baseder, index);
	return *this;
}

MailList& MailList::sortAndUnique(Baseder& baseder, int& index) {
	Baseder ba(baseder);
	Label lb(ba, ba.getXH() - 8, 2, 18);
	lb.setStr(" 请选择排序方式");
	lb.showAll();
	MenuItem items = { "学号","姓名","号码","QQ号" };
	Menu menu(ba.getX() - 2, ba.getY() - 6, 1, 5, ba, items, 4);
	menu.setBorder(' ');
	int tIndex = menu.show(0, false);
	switch (tIndex) {
	case 0:
		ls.sort_by([](const data& d1, const data& d2) {return d1.id > d2.id; })
			.unique_if([](const data& d1, const data& d2) {return d1.id == d2.id; });//按照学号
		break;
	case 1:
		ls.sort_by([](const data& d1, const data& d2) {return d1.name > d2.name; })
			.unique_if([](const data& d1, const data& d2) {return d1.name == d2.name; });//按照姓名
		break;
	case 2:
		ls.sort_by([](const data& d1, const data& d2) {return d1.tel > d2.tel; })
			.unique_if([](const data& d1, const data& d2) {return d1.tel == d2.tel; });//按照号码
		break;
	case 3:
		ls.sort_by([](const data& d1, const data& d2) {return d1.QQ > d2.QQ; })
			.unique_if([](const data& d1, const data& d2) {return d1.QQ == d2.QQ; });//按照号码
		break;
	}



	show(baseder, index = 0);
	return *this;
}

void MailList::start() {
	Baseder left(base.getX() / 6 * 5 + 3, base.getY(), 0, 0, base);
	Baseder right(base.getX() / 6, base.getY(), base.getX() / 6*5 + 2, 0, base);
	MenuItem menuItem = { "下一页","上一页","追加","插入","删除",//4
						  "查询","修改","反转","排序并消重","保存文件",//9
						  "读取文件","退出" };//11
	Menu menu(right, menuItem, 12);
	int choice = 0;//当前选项
	int index = 0;//显示第几页
	show(left, index);
	while (1) {
		choice=menu.show(choice);
		switch (choice) {
		case 0:
			show(left, ++index);
			break;
		case 1:
			show(left, --index);
			break;
		case 2:
			addEle(left,index);
			break;
		case 3:
			insertEle(left,index);
			break;
		case 4:
			delEle(left, index);
			break;
		case 5:
			find_by(left);
			break;
		case 6:
			replaceEle(left,index);
			break;
		case 7:
			reserveEle(left,index);
			break;
		case 8:
			sortAndUnique(left,index);
			break;
		case 9:
			save(inputFileName(left));
			break;
		case 10: 
			load(inputFileName(left),left,index);
			break;
		case 11:
			left.close();
			right.close();
			return;
		}
	}
}