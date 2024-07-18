//自定义图形库
#pragma once
#ifndef BASE_H
#define BASE_H
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <initializer_list>
using namespace std;

namespace win {
	void setFont(int size = 16);//设置字体大小(窗口缩放比),16为原始值
	void setSize(int w, int h);//设置窗口宽高，有侧边滑动条
	void gotoxy(int y, int x);//设置光标位置
	void setCursor(bool mode = false);//设置光标显示(隐藏或者显示)
	void setColor(WORD color = 0x7);
}

inline void clsbuf() {//清空输入缓冲区
	while (_kbhit()) {
		static_cast<void>(_getch());
	}
}
inline void eat() {//清空输入缓冲区
	while (cin.peek() != '\n') {
		cin.get();
	}
	cin.get();
}

class Base
{
protected:
	int x;//记录宽
	int y;//记录高

	void cls();//清屏
	void hideCursor();//隐藏光标

	char** map;//记录数据
	WORD** mapColor;//记录颜色
	void setColor(WORD color);//设置输出颜色
	bool judgeX(int x);//判断x是否越界
	bool judgeY(int y);//判断y是否越界
public:
	Base(int x = 122, int y = 29);//初始化
	virtual ~Base();//释放堆内存

	//不能赋值和临时对象
	void operator=(const Base& b) = delete;
	Base(const Base& b) = delete;
	Base(const Base&& b) = delete;

	//数据接口
	int getX() const { return x; };
	int getY() const { return y; };
	int getXH() const { return x / 2; };//x的一半
	int getYH() const { return y / 2; };//y的一半
	char* getMap(int x, int y) { return &map[y][x]; };//可能会越界，谨慎
	WORD* getMapColor(int x, int y) { return &mapColor[y][x]; };//可能会越界，谨慎
	char** getmap() { return map; };//可能会越界，谨慎
	WORD** getmapColor() { return mapColor; };//可能会越界，谨慎
	char& Map(int y, int x) { return map[y][x]; };//可能会越界，谨慎
	WORD& MapColor(int y, int x) { return mapColor[y][x]; };//可能会越界，谨慎
	bool isAlive() const { return map; };//map等于nullptr的时候返回false

	//边框
	Base& setBorder(char border = '/', WORD color = 0x7);//设置边框
	Base& setBorderColor(WORD color);//设置边框颜色

	//设置输出
	Base& setText(int x, int y, const char* s, WORD color = 0x7, bool mode = true);//mode为true横向，false纵向

	//设置矩形区域颜色
	Base& setBufColor(int xStart, int yStart, int xEnd, int yEnd, WORD color);
	Base& setBufColor(int pos, int start, int end, WORD color, const char* mode = nullptr);//mode为true横向，false纵向

	//输出map
	void draw();

	//初始化map
	Base& initMap();

	//根据坐标设置输入
	Base& gotoxy(int y, int x);

	Base& setFont(int size = 16);//设置字体大小(窗口缩放比),16为原始值
};
class Baseder//基于一个Base的子窗口
{
protected:
	bool state;
	int x;//宽
	int y;//高
	int xpos;
	int ypos;
	Base* base;
	Baseder* baseder;
	char** mapT;//内容数据
	WORD** mapColorT;//颜色数据

	char** map;//内容数据
	WORD** mapColor;//颜色数据

	void setColor(WORD color);//设置输出颜色
	bool judgeX(int x);//判断x是否越界
	bool judgeY(int y);//判断y是否越界

public:
	Baseder(int x, int y, int xPos, int yPos, Base& base);//基于Base的(xPos,yPos)位置的小窗口
	Baseder(int x, int y, int xPos, int yPos, Baseder& baseder);//基于Baseder的小窗口;
	virtual ~Baseder();//只用释放二级指针堆内存，base类会释放一级指针
	Baseder(Baseder& b) :Baseder(b.x, b.y, b.xpos, b.ypos, *b.base) {};//只能基于base的窗口
	Baseder(Base& b) :Baseder(b.getX(), b.getY(), 0, 0, b) {};//复制base

	//不能赋值和临时对象
	void operator=(const Baseder& b) = delete;

	Baseder(const Baseder&& b) = delete;

	//数据接口
	int getX() const { return x; };
	int getY() const { return y; };
	int getXH() const { return x / 2; };//x的一半
	int getYH() const { return y / 2; };//y的一半

	char* getMap(int x, int y) { return &map[y][x]; };//可能会越界，谨慎
	WORD* getMapColor(int x, int y) { return &mapColor[y][x]; };//可能会越界，谨慎

	char** getmap() { return map; };//可能会越界，谨慎
	WORD** getmapColor() { return mapColor; };//可能会越界，谨慎
	char** getmapT() { return mapT; };//可能会越界，谨慎
	WORD** getmapColorT() { return mapColorT; };//可能会越界，谨慎

	char& Map(int y, int x) { return map[y][x]; };//可能会越界，谨慎
	WORD& MapColor(int y, int x) { return mapColor[y][x]; };//可能会越界，谨慎
	char MapT(int y, int x) const { return mapT[y][x]; };//可能会越界，谨慎
	WORD MapColorT(int y, int x) const { return mapColorT[y][x]; };//可能会越界，谨慎

	bool isAlive() const { return map; };//map等于nullptr的时候返回false

	Base& getBase() { return *base; };
	Baseder& getBaseder() { return *baseder; };
	void reState();//state=false,释放MapT

	//相对位置数据
	int getXPos() const { if (baseder) { return baseder->getXPos() + xpos; } return xpos; };
	int getYPos() const { if (baseder) { return baseder->getYPos() + ypos; } return ypos; };

	//边框
	Baseder& setBorder(char border = '/', WORD color = 0x7);//设置边框
	Baseder& setBorderColor(WORD color);//设置边框颜色
	virtual Baseder& setBorderLine(char ch = ' ');//设置边框为线,ch表示4个角

	//设置输出
	Baseder& setText(int x, int y, const char* s, WORD color = 0x7, bool mode = true);//mode为true横向，false纵向

	//设置矩形区域颜色
	Baseder& setBufColor(int xStart, int yStart, int xEnd, int yEnd, WORD color);
	Baseder& setBufColor(int pos, int start, int end, WORD color, const char* mode = nullptr);//mode为true横向，false纵向
	Baseder& setBufColor(int x, int y, WORD color) { mapColor[y][x] = color; return *this; };
	Baseder& setBkColor(WORD color, bool mode = false);//设置背景颜色，mode表示是否设置边框

	//输出map
	void draw();
	void show() { draw(); };//不定义为虚函数,因为后面子类返回类型各不相同，使用指针和引用时需注意
	//初始化map
	virtual Baseder& initMap();

	//关闭map
	void close();//将map和mapColor变回来，释放mapT和mapColorT内存

	//设置输入位置
	Baseder& gotoxy(int y, int x);

	//设置标题
	Baseder& setTitle(string title, bool mode = true);//mode设置为false在顶部,否则在底部
};
using MenuItem = const char* [];
class Menu :public Baseder {
protected:
	char** str;
	int num;//str的元素个数
public:
	Menu(int x, int y, int xPos, int yPos, Base& base, const char* str[], int num);//基于base 
	Menu(int x, int y, int xPos, int yPos, Baseder& baseder, const char* str[], int num);//基于baseder
	Menu(Base& base, const char* str[], int num);//基于base
	Menu(Baseder& baseder, const char* str[], int num);//基于baseder
	//Menu(Menu& m);

	//Menu(int x, int y, int xPos, int yPos, Base& base, initializer_list<string> initls);//基于base 
	//Menu(int x, int y, int xPos, int yPos, Baseder& baseder, initializer_list<string> initls);//基于baseder
	//Menu(Base& base, initializer_list<string> initls);//基于base
	//Menu(Baseder& baseder, initializer_list<string> initls);//基于baseder
	virtual ~Menu();//释放堆内存

	virtual int show(int cho = 0, bool init = true);//开始展示,返回值为选项,init设置为false时不initMap()
	//cho为初始选项
//数据接口
	char** getItem() { return str; };
	int getNum() const { return num; };



	virtual Menu& push(MenuItem item, int n);//添加选项
	virtual Menu& push(const char* item);//添加选项

	virtual bool insert(MenuItem item, int qui, int index = 0);//插入选项 qui表示个数 失败返回true
	virtual bool insert(const char* item, int index = 0);//插入选项 失败返回true

	virtual Menu& reset(MenuItem item, int num);//重新设置选项
	virtual Menu& reset(char** item, int num);//重新设置选项
	//virtual Menu& reset(initializer_list<string> ls);
};
class Input :public Baseder {//输入条
public:
	Input(Base& base, int xPos = 0, int yPos = 0) :Baseder(base.getX() - xPos - 1, 1, xPos, yPos, base) { setBorder(' '); };//输入框只有一行
	Input(Baseder& baseder, int xPos = 0, int yPos = 0) :Baseder(baseder.getX() - xPos - 1, 1, xPos, yPos, baseder) { setBorder(' '); };

	virtual string show();//返回值为输入值
};
class InputBox :public Baseder {
	Input input;
public:
	InputBox(Base& base, int WITH, int xPos = 0, int yPos = 0) :Baseder(WITH, 3, xPos, yPos, base), input(base, xpos + 1, ypos + 1) {};
	InputBox(Baseder& baseder, int WITH, int xPos = 0, int yPos = 0) :Baseder(WITH, 3, xPos, yPos, baseder), input(baseder, xpos + 1, ypos = 1) {};

	virtual string show(bool mode = true);
};
class Label :public Baseder {
	InputBox inputBox;
	string str;
	string strR;
public:
	Label(Base& base, int xPos = 0, int yPos = 0, int WITH = 20) :Baseder(WITH, 3, xPos, yPos, base), inputBox(base, WITH, xPos, yPos), str() {};
	Label(Baseder& baseder, int xPos = 0, int yPos = 0, int WITH = 20) :Baseder(WITH, 3, xPos, yPos, baseder), inputBox(baseder, WITH, xPos, yPos), str() {};

	Label& setStr(const string& str);
	Label& setStrR(const string& strR) { this->strR = strR; return *this; };
	const string& getStr() { return str; };
	const string& getStrR() { return strR; };

	virtual string show(bool mode = true);//mode为false只有inputBox
	virtual void showAll();//展示输入后的内容
};

#include <vector>
class LabelBox :public Baseder {//label盒子
	const int num;//元素个数
	vector<string> str;
	vector<string> strR;
public:
	LabelBox(Base& base, int num, int xPos = 0, int yPos = 0, int WITH = 20) :Baseder(WITH, 2 * num + 1, xPos, yPos, base), num(num) { setBorderLine(); };//num表示个数
	LabelBox(Baseder& baseder, int num, int xPos = 0, int yPos = 0, int WITH = 20) :Baseder(WITH, 2 * num + 1, xPos, yPos, baseder), num(num) { setBorderLine(); };

	//设置边框
	LabelBox& setBorderLine();

	//设置标签里面的元素
	template <class It>
	LabelBox& setStr(It begin);//迭代器设置元素

	template <class It>
	LabelBox& setStr(It begin, int num);//迭代器设置元素(会先清空元素)

	LabelBox& setStr(const string& str, int index);//必须index存在才行

	template <class It>
	LabelBox& setStrR(It begin);//迭代器设置元素(会先清空元素)

	template <class It>
	LabelBox& setStrR(It begin, int num);//迭代器设置元素

	LabelBox& setStrR(const string& str, int index);//必须index存在才行

	//数据接口,如果index越界则添加至index(前提是index<num)
	string& getStr(int index);
	string& getStrR(int index);

	void show();//依次show(输入元素)，会清空strR然后设置为输入
	void showAll();//依次showAll

	bool isNull() { return !(str.size() || strR.size()); };//判断是否为空
	bool isNullR() { return !strR.size(); };
};
class LabelBoxArr :public Baseder {//管理LableBoxArr
	const int num;
	allocator<LabelBox> lb;
	LabelBox* head;
public:
	LabelBoxArr(Base& base, int num, int labelNum = 1, int xPos = 0, int yPos = 0, int WITH = 20);//num表示个数
	LabelBoxArr(Baseder& baseder, int num, int labelNum = 1, int xPos = 0, int yPos = 0, int WITH = 20);//labelNum是传入lableBox的num
	virtual ~LabelBoxArr();//释放allocator

	LabelBox& getLb(int index);//数据接口,检查索引是否越界

	void show(bool mode = true);//mode=ture时会先showAll()
	void showAll();
	void showQueue();//依次输入,输入时后面的不会LabelBox展示
	bool isNull();//判断是否为空
};

class InputTips :public Baseder {//带提示的输入条
	string tips;
public:
	InputTips(Base& base, int xPos = 0, int yPos = 0)
		:Baseder(base.getX() - xPos - 1, 1, xPos, yPos, base) {
		setBorder(' ');
	};//输入框只有一行

	InputTips(Baseder& baseder, int xPos = 0, int yPos = 0)
		:Baseder(baseder.getX() - xPos - 1, 1, xPos, yPos, baseder) {
		setBorder(' ');
	};

	string& show();
	InputTips& setTips(const string& tip);
};

//模板写为内联函数
template<class It>
inline LabelBox& LabelBox::setStr(It begin)
{
	str.clear();
	for (int i = 0; i < num; ++i) {
		str.push_back(*begin);
		++begin;
	}
	// TODO: 在此处插入 return 语句
	return *this;
}

template<class It>
inline LabelBox& LabelBox::setStr(It begin, int num)
{
	str.clear();
	num = num < this->num ? num : this->num;
	for (int i = 0; i < num; ++i) {
		str.push_back(*begin);
		++begin;
	}
	// TODO: 在此处插入 return 语句
	return *this;
}

template<class It>
inline LabelBox& LabelBox::setStrR(It begin)
{
	strR.clear();
	for (int i = 0; i < num; ++i) {
		strR.push_back(*begin);
		++begin;
	}
	// TODO: 在此处插入 return 语句
	return *this;
}

template<class It>
inline LabelBox& LabelBox::setStrR(It begin, int num)
{
	strR.clear();
	num = num < this->num ? num : this->num;
	for (int i = 0; i < num; ++i) {
		strR.push_back(*begin);
		++begin;
	}
	// TODO: 在此处插入 return 语句
	return *this;
}
#endif