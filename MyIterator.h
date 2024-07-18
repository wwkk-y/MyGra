//自定义迭代器
#ifndef MYITERATOR_H
#define MYITERATOR_H
#include "LinkList.h"
#include <iostream>

//向前声明结构点和链表类(迭代器类友元类)
template <class T> class LinkList;
template<class T> struct Node;

//链表迭代器(正向迭代器)
template<class T>
class MyIterator {
	friend class LinkList<T>;//声明链表类为友元
	Node<T>* p;//当前表示的节点
	int index;//当前节点的链表位置
public:
	using value_type = T;//值类型,泛型算法接口
	//构造函数
	//构造1:使用index
	//(需要计算，时间跟index有关，为线性时间)
	MyIterator(LinkList<T>& ls, int index) {
		this->index = index;
		int i = 0;
		for (p = ls.head; i < index; ++i) {
			p = p->next;
		}
	};
private:
	//构造2:Node<T>和index直接构造
	//(更节约时间,可避免容器计算end()消耗太多时间,使用第一个构造需要遍历链表，时间是线性的)
	MyIterator(Node<T>* p, int index) :p(p), index(index) {};
public:
	//（迭代器 - 迭代器）操作
	int operator-(const MyIterator& it) const {
		return index - it.index;//如果两个迭代器绑定的是不同的LinkList对象，该操作的结果是未定义的
	}
	

	//解除引用操作,值为p->data
	T& operator*() {
		return this->p->data;
	};

	//++操作
	//前缀++
	MyIterator<T>& operator++() {
		if (this->p == nullptr) {//确保不会越界，方便inserter泛型算法在结尾插入时的后移(++iterator)操作
			return *this;
		}
		++index;
		p = p->next;
		return *this;
	};
	//后缀++
	MyIterator<T> operator++(int) {
		MyIterator<T> temp = *this;
		if (this->p == nullptr) {//确保不会越界，方便inserter泛型算法在结尾插入时的后移(iterator++)操作
			return temp;
		}
		this->index += 1;
		this->p = this->p->next;
		return temp;
	}

	//加数操作(可能会越界,越界的情况是未定义的)
	MyIterator<T>& operator+=(int num) {
		index += num;
		for (int i = 0; i < num; ++i) {
			p = p->next;
		}
		return *this;
	}
	MyIterator<T> operator+(int num) const{
		MyIterator<T> temp = *this;
		temp.index += num;
		for (int i = 0; i < num; ++i) {
			temp.p = temp.p->next;
		}
		return temp;
	}

	//判断
	//==
	bool operator==(const MyIterator<T>& it) const{
		return p == it.p;
	}
	//< 
	bool operator<(const MyIterator<T>& it) const {
		return  index < it.index;//如果两个迭代器绑定的是不同的LinkList对象，该操作的结果是未定义的
	}
	//( >, >=, <, <= 可以通过以上两种组合来实现)
	// != 
	bool operator!=(const MyIterator<T>& it) const {
		return p != it.p;
	}
	
	//bool类型转换,p为nullptr时转化为false,其余情况皆为true
	explicit operator bool() const{ return p; };//加上explicit避免自动转换

	//数据接口
	int getIndex() { return index; };
	Node<T>* getNode() { return p; };


	//输出
	friend std::ostream& operator<<(std::ostream& os, MyIterator<T> it) {
		using namespace std;
		if (!it) {
			cout << "data:nullptr  index:"<<it.getIndex();
		}
		else {
			cout <<"data:" << it.p->data << "  index:" << it.getIndex();
		}
		return os;
	}
};
#endif