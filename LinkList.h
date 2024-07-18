//链表类头文件
#pragma once
#ifndef MYLIST_H
#define MYLIST_H
#include <iostream>//show操作会用到io库
#include "MyIterator.h"//自定义迭代器
#include <initializer_list>//列表初始构造会用到
#include <stdexcept>//链表类索引设计时用到了out_of_range异常类
#include "Base.h"//自定义图形库
//链表节点结构
template<class T>
struct Node
{
	T data;
	Node<T>* next;
	Node(const T& t) {//构造函数(方便后续添加节点少写重复代码)，结构体默认为public,也可直接自己操作数据成员
		this->data = t;
		this->next = nullptr;
	}
};


template<class T> class MyIterator;//迭代器向前声明(链表类友元类)

//链表实现
template <class T>
class LinkList {
	friend class MyIterator<T>;//迭代器设置为友元类
	Node<T>* head;//头节点
	Node<T>* tail;//尾节点（null前一个节点）
	int len;//长度
public:
	using value_type = T;//值类型(重命名方便泛型算法)
	using size_type = int;//长度类型(重命名方便泛型算法)
	//迭代器
	using iterator = MyIterator<T>;
	/*
	迭代器说明:
			迭代器是广义的指针，可对它进行类似指针的操作,如*iterator(解引用)，++iterator(后移)，*iterator++=value(将iter
		ator指向的值赋为value并后移一位)。
			更多操作参考MyIteator.h头文件里的MyIterator<T>类的operator(运算符重载)。
			这里的迭代器主要对链表节点(即Node<T>* )进行管理，实现了一个正向迭代器。
	
	设计迭代器的目的:
			根据我以往的编程经验，我个人认为让类的用户直接操作数据成员是非常危险的行为，如果没有严谨的思维和丰富的经验，
		直接操作链表节点可能会出现很多错误，严重的情况可能会直接破坏链表结构，而使用迭代器就不用担心这个问题，你可以像
		使用指针那样来修改数据，非常容易上手，并且这样确保了您的操作不会破坏数据结构，当然我个人认为我设计的接口已经能
		实现90%以上的操作，暂时还没有必须使用迭代器来修改数据的情况，当然如果您乐意，也可以使用迭代器代替我提供的接口。
			使用迭代器还有其它优点:可以使用标准库算法。虽然我这里实现的迭代器比较简陋，但还是可以使用部分标准库算法，如
		果无法使用，您也可以使用我提供的类接口。
			如果您更乐意使用链表节点或者是已经习惯使用链表节点,迭代器类也为您提供了getNode()接口，返回值为该迭代器管理的
		链表节点。

	如何声明迭代器变量:
			方式一 (使用auto(c++11)关键字):
						LinkList<int> ls(10,1);
						auto value=ls.begin();//auto自动推出类型
			方式二 (类似标准库容器,使用LinkList<T>::iterator):
						LinkList<int> ls(10,1);
						LinkList<int>::iterator value=ls.begin();
			方式三 (直接使用类名称MyIterator<T>):
						LinkList<int> ls(10,1);
						MyIterator<int> value=ls.begin();
	*/
	
	//构造函数
	LinkList() { head = tail = nullptr; len = 0; };//默认构造函数
	LinkList(std::initializer_list<T> il);//{value1, value2, value3, ...}列表初始化
	LinkList(const T& t);//初值构造
	LinkList(int num,const T& value);//num个value
	LinkList(int num,int&& value);//num个value (避免T为int时构造重定义,第二个值使用右值引用,数值参数会优先匹配此构造函数)
	LinkList(const LinkList<T>& t);//复制构造
	LinkList(LinkList<T>&& t);//右值引用构造,交换数据拥有权(相较于复制构造更快,时间固定)
	
	template <class It>
	LinkList(const It begin,const It end);//迭代器构造
	
	LinkList<T>& operator=(const LinkList<T>& t);//赋值运算符

	//析构函数，释放链表
	~LinkList();

	//STL部分相关函数(实现了增删查改,以及部分容器标准库算法的接口)
	/*
	关于函数返回类型的说明:
				大多数操作返回值都是本身的引用(方便连续操作，如ls.clear().push_back(value).push_back(value)...)但是为了与
			标准库接口相对应，一些操作被设计为返回迭代器，如insert(iterator pos,const T& value)返回类型为迭代器来方便使用
			标准库的inserter。另外一些返回值表示位置的函数( 例如find(const T& value) )返回值也为迭代器。
	*/
	int size() const{ return len; };//长度
	LinkList<T>& push_back(const T& t);//添加尾节点
	LinkList<T>& emplace_back(std::initializer_list<T> ls);//列表直接添加到头部
	LinkList<T>& push_front(const T& t);//添加头节点
	LinkList<T>& emplace_front(std::initializer_list<T> ls);//列表直接添加到尾部
	LinkList<T>& pop_back();//删除尾节点
	LinkList<T>& pop_front();//删除头节点
	bool empty() const{ return !head; };//判断是否为空
	LinkList<T>& clear();//清空所有元素
	T& front() { return head->data; };//返回第一个元素数据
	T& back() { return tail->data; };//返回最后一个元素数据
	const T& front() const{ return head->data; };//返回第一个元素数据
	const T& back() const{ return tail->data; };//返回最后一个元素数据
	/*
	insert:		这里的insert更类似标准库容器里的insert_back,操作时间固定;
	说明:		可正常使用标准库的back_inserter,front_inserter,但使用inserter需要稍加注意:inserter会添加元素到所给位置之
			后，而标准库容器是添加到所给位置之前。
	
	关于inserter说明:
				为了节省操作时间,这里设计的insert与标准库容器的insert不同,此处的insert均添加元素到所给位置之后,如果需要添
			加到begin位置之前,不能直接使用inserter(ls,ls.begin())(ls表示一个LinkList<T>对象)，但您可使用push_front()来添加，
			虽然inserter添加位置不同，但是确保了您可以正常添加一系列元素到所给位置之后。
	
	关于end():
				insert设计为插入元素到所给位置之后来节省运行时间,但是对end()位置就不太友好,需要在尾部使用inserter时，一般来
			说需要使用end()前一个位置的迭代器，为了更优雅的使用，insert算法和迭代器设计时都单独考虑了end()，现在使用inserter
			在尾部插入元素时可直接使用end()，当然如果您乐意，使用begin()+(size()-1)也可以，迭代器设计时确保了++iterator和ite
			rator++操作不会越界（但是 iterator+数字 操作没有这个设计!!!）。
	*/
	iterator insert(const iterator& pos, const T& value);//value插入到pos位置后
														 //返回表示插入元素位置的迭代器(方便inserter插入算法中的后移操作)
	LinkList<T>& insert(const iterator& pos, int num, const T& value);//插入num个value到pos后

	template <class It>
	LinkList<T>& insert(const iterator& pos,const It begin,const It end);//迭代器插入,插入到pos位置之后
	LinkList<T>& emplace(const iterator& pos, std::initializer_list<T> ls);//pos位置后直接列表添加元素
	
	LinkList<T>& erase(iterator pos);//删除pos位置元素
	LinkList<T>& erase(iterator begin,iterator end);//删除[begin,end)区间元素
	LinkList<T>& erase_back(iterator pos);//删除pos位置后面的一个元素
	LinkList<T>& erase_back(iterator begin,iterator end);//删除[begin+1,end)区间元素

	iterator find(const T& t);//查找元素,没找到返回end(),如果为end(),iterator可转化为false,其余情况为true
	iterator find(const T& t, iterator pos);//从pos开始查找,没找到返回end(),如果为end(),iterator可转化为false,其余情况为true
	
	/*
	函数符说明:
			该容器中以F名称开头的模板被当作函数符使用,如template<class F> iterator find_if(F f),其中F为一元谓词。
	n元谓词:
			接受n个T类型参数的返回值为bool类型的函数符(函数指针,lambda表达式,函数对象)，例如前面的find_if的f可为:[](const 
		int& value){return value>10;}（这里假设T为int类型）,传入find_if，它会找到第一个满足大于10的元素所在的迭代器。
			例:template<class Fj,class Fd> LinkList<T>& sort_by(F f),这里f为二元谓词，假设T为string。令函数bool deal(const
		string& value1,const string& value2){return value1.size()<value2.size();},可将deal当作deal_if的参数,此时F为bool (*)
		(const string&,const string&)类型，即一个二元谓词的函数指针类型，将此函数传入deal_if后它会按照string的长度来排序。
	*/

	template<class F>
	iterator find_if(F f);//F为一元谓词(接受一个参数的bool类型函数),返回为ture的第一个元素的迭代器,否则返回end()
	template<class F>
	iterator find_if(F f,iterator pos);//从pos位置开始查找
									//F为一元谓词(接受一个参数的bool类型函数),返回为ture的第一个元素的迭代器,否则返回end()

	template<class F>
	LinkList<T>& sort_by(F f);//排序函数，f为二元谓词(接受2个参数的bool类型函数),为true时判断为第一个元素小于第二个元素
	LinkList<T>& sort();//排序函数，要求T类型有 operator< 
	
	template<class F>
	LinkList<T>& unique_if(F f);//f为二元谓词,为true时消除第二个元素
	LinkList<T>& unique();//消除相邻重复元素 (线性时间),一般先sort再unique可消除所有重复元素
	
	template<class F>
	LinkList<T>& remove_if(F f);//f是一个一元谓词(接受一个参数的bool类型函数),为true时删除该元素
	LinkList<T>& remove(const T& value);//删除所有值为value的元素,要求T类型有 operator==

	
	template<class Fj,class Fd>
	LinkList<T>& deal_if(Fj fj, Fd fd);//fj(一元谓词)为true时对该元素进行fd(data)操作
	template<class Fj,class Fd>
	LinkList<T>& deal_if(iterator begin, iterator end, Fj fj, Fd fd);//[begin,end)范围内fj(一元谓词)为true时对该元素进行fd(data)操作
	template<class Fj, class Fd>
	LinkList<T>& deal_if(iterator begin, Fj fj, Fd fd);//[begin,end())范围内fj(一元谓词)为true时对该元素进行fd(data)操作

	template<class F>
	LinkList<T>& replace_if(F f, const T& newValue);//f为一元谓词,为true时替换该元素为newValue
	LinkList<T>& replace(const T& oldValue, const T& newValue);//将所有oldValue替换为newValue

	//尾迭代器和头迭代器
	iterator begin() { return iterator(*this,0); };
	iterator end() { return iterator(nullptr, len); };

	LinkList<T> reserve(bool mode=false);//返回翻转的链表(本身不受影响),如果mode为true，则影响本身
	LinkList<T>& swap(LinkList<T>& ls);//与ls交换,只交换指针，时间固定
	//判断==
	bool operator==(const LinkList<T>& ls) {
		return head == ls.head;//头节点相等即相等
	}

	//索引(线性时间,index过大可能会比较耗时)
	T& operator[](int index);//索引,不检查越界行为
	const T& operator[](int index) const;//常量索引,不检测越界
	T& at(int index);//检查越界行为,如果越界，会抛出一个异常并终止程序
	const T& at(int index) const;//常量索引,检查越界行为，如果越界，会抛出一个异常并终止程序

	//测试相关
	void show();//遍历并展示
	int show(int with,Baseder& baseder,int y,int x);//长度with时换行
	int showJosephus(int with, Baseder& baseder, int y, int x, int index);//index位置特殊标记
};

template<class T>
inline LinkList<T>::LinkList(std::initializer_list<T> il) 
{
	len = 0;
	head = tail = nullptr;
	for (auto p = il.begin(); p != il.end(); ++p) {
		push_back(*p);
	}
}

template<class T>
inline LinkList<T>::LinkList(const T& t)
{
	head = new Node<T>(t);
	len = 1;
	tail = head;
}

template<class T>
inline LinkList<T>::LinkList(int num,const T& value)
{
	len = 0;
	head = tail = nullptr;
	for (int i = 0; i < num; ++i) {
		push_back(value);
	}
}

template<class T>
inline LinkList<T>::LinkList(int num,int&& value)
{
	len = 0;
	head = tail = nullptr;
	for (int i = 0; i < num; ++i) {
		push_back(value);
	}
}

template<class T>
inline LinkList<T>::LinkList(const LinkList<T>& t)
{
	len = 0;//push_back会增加len
	head = tail = nullptr;
	for (Node<T>* i = t.head; i != nullptr; i = i->next) {
		push_back(i->data);
	}
}

template<class T>
inline LinkList<T>::LinkList(LinkList<T>&& t)
{
	head = t.head;
	tail = t.tail;
	len = t.len;
	t.head = t.tail = nullptr;
	t.len = 0;
}

template<class T>
inline LinkList<T>& LinkList<T>::operator=(const LinkList<T>& t)
{
	if (&t == this) {
		return *this;//自己赋值自己
	}
	clear();//先释放
	for (Node<T>* i = t.head; i != nullptr; i = i->next) {
		push_back(i->data);
	}
	// TODO: 在此处插入 return 语句
	return *this;
}


template<class T>
inline LinkList<T>::~LinkList()
{
	clear();
}

template<class T>
inline LinkList<T>& LinkList<T>::push_back(const T& t)
{
	++len;
	if (head == nullptr) {
		head = new Node<T>(t);
		tail = head;
	}
	else {
		tail->next = new Node<T>(t);
		tail = tail->next;
	}

	// TODO: 在此处插入 return 语句
	return *this;
}

template<class T>
inline LinkList<T>& LinkList<T>::emplace_back(std::initializer_list<T> ls) {
	for (auto p = ls.begin(); p != ls.end(); ++p) {
		push_back(*p);
	}
	return *this;
}

template<class T>
inline LinkList<T>& LinkList<T>::push_front(const T& t)
{
	++len;
	Node<T>* p = new Node<T>(t);
	p->next = head;
	head = p;
	if (tail == nullptr) {
		//只有一个节点
		tail = head;
	}

	// TODO: 在此处插入 return 语句
	return *this;
}

template<class T>
inline LinkList<T>& LinkList<T>::emplace_front(std::initializer_list<T> ls) {
	for (auto p = ls.begin(); p != ls.end(); ++p) {
		push_front(*p);
	}
	return *this;
}

template<class T>
inline LinkList<T>& LinkList<T>::pop_back()
{
	if (empty()) {
		return *this;//为空时
	}
	--len;
	Node<T>* p;
	for (p = head; p->next != tail&&p->next!=nullptr; p = p->next) {
		;//不用任何操作
	}
	if (head==tail) {//只有一个节点
		delete head;
		head = tail = nullptr;
	}
	else if (p == head) {//两个节点
		delete tail;
		head->next = nullptr;
		tail = head;
	}
	else {
		delete tail;
		p->next = nullptr;
		tail = p;
	}
	
	// TODO: 在此处插入 return 语句
	return *this;
}
template<class T>
inline LinkList<T>& LinkList<T>::pop_front() {
	if (empty()) {
		return *this;
	}
	--len;
	if (len == 0) {
		delete head;
		head = tail = nullptr;
	}
	else {
		auto p = head;
		head = head->next;
		delete p;
	}
	return *this;
}

template<class T>
inline LinkList<T>& LinkList<T>::clear()
{
	Node<T>* p;
	Node<T>* t;
	for (p = head; p != nullptr;	) {
		t = p;
		p = p->next;
		delete t;
	}
	head = tail = nullptr;
	len = 0;

	// TODO: 在此处插入 return 语句
	return *this;
}

template<class T>
inline MyIterator<T> LinkList<T>::insert(const iterator& pos, const T& value) {//插入到pos后面
	if (pos.p == nullptr) {
		push_back(value);
		return pos;
	}
	++len;
	Node<T>* later = pos.p->next;
	Node<T>* temp = new Node<T>(value);
	pos.p->next = temp;
	temp->next = later;
	return pos;
}

template<class T>
LinkList<T>& LinkList<T>::insert(const iterator& pos, int num, const T& value) {
	for (int i = 0; i < num; ++i) {
		insert(pos, value);
	}
	return *this;
}

template<class T>
template<class It>
inline LinkList<T>& LinkList<T>::insert(const iterator& pos,const It begin,const It end)
{
	if (pos.p == nullptr) {//尾节点的情况
		for (auto p = begin; p != end; ++p) {
			push_back(*p);
		}
		return *this;
	}

	int i = 0;
	iterator temp = pos;
	for (auto p = begin; p != end; ++p) {
		insert(temp, *p);//会添加len
		++temp;
	}
	// TODO: 在此处插入 return 语句
	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::emplace(const iterator& pos,std::initializer_list<T> ls) {
	insert(pos, ls.begin(), ls.end());
	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::erase(iterator pos) {
	if (pos.p == nullptr||empty()) {
		return *this;
	}
	--len;
	//头节点
	if (pos == begin()) {
		head = head->next;
		delete pos.p;
		pos.p = nullptr;
	}
	else {
		iterator itTemp = iterator(*this, pos.index - 1);
		(itTemp.p)->next = (pos.p)->next;
		delete pos.p;
		pos.p = nullptr;
	}
	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::erase(iterator begin,iterator end) {
	for (int i = 0; i < end - begin; ++i) {
		erase(iterator(*this, begin.index));
	}
	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::erase_back(iterator pos) {
	
	if (pos.p ==nullptr ) {//传入end位置,直接return
		return *this;
	}
	iterator it = pos + 1;
	if (it.p == nullptr) {//删除tail后的null,直接return
		return *this;
	}
	pos.p->next = it.p->next;
	delete it.p;
	--len;

	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::erase_back(iterator begin,iterator end) {
	if (begin.p ==nullptr ) {
		return *this;
	}
	Node<T>* p = begin.p->next;
	Node<T>* t = p;
	begin.p->next = end.p;
	while(p!=end.p){
		t = p;
		p = p->next;
		--len;
		delete t;
	}

	return *this;
}

template<class T>
MyIterator<T> LinkList<T>::find(const T& t) {
	MyIterator<T> p = begin();
	for ( ; p.p!=nullptr&& * p != t; ++p) {
		;//不需要任何操作
	}
	return p;
}

template <class T>
MyIterator<T> LinkList<T>::find(const T& t, iterator pos) {
	for (; pos.p!=nullptr &&*pos != t; ++pos) {
		;//不需要任何操作
	}
	return pos;
}

template<class T>
template<class F>
MyIterator<T> LinkList<T>::find_if(F f) {
	MyIterator<T> p = begin();
	for (; p.p != nullptr && !f(*p); ++p) {
		;//不需要任何操作
	}
	return p;
}

template<class T>
template<class F>
MyIterator<T> LinkList<T>::find_if(F f, iterator pos) {
	for (; pos.p != nullptr && !f(*pos); ++pos) {
		;//不需要任何操作
	}
	return pos;
}

template<class T>
template<class F>
LinkList<T>& LinkList<T>::sort_by(F f) {
	for (int i = 1; i < len; ++i) {
		int j = 0;
		for (Node<T>* p2 = head; j < len - i; p2 = p2->next) {
			if ( f(p2->data,p2->next->data) ) {
				T t = p2->data;
				p2->data = p2->next->data;
				p2->next->data = t;
			}
			++j;
		}
	}

	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::sort() {
	for (int i = 1; i < len;++i) {
		int j = 0;
		for (Node<T>* p2 = head; j<len-i ; p2 = p2->next) {
			if ((p2->next->data) < p2->data) {
				T t = p2->data;
				p2->data = p2->next->data;
				p2->next->data = t;
			}
			++j;
		}
	}

	return *this;
}

template<class T>
template<class F>
LinkList<T>& LinkList<T>::unique_if(F f) {
	int index = 0;
	if (empty()) {
		return *this;
	}
	for (Node<T>* p = head; p->next != nullptr; ) {
		if (f(p->data,p->next->data)) {
			erase_back(iterator(p, index));
			continue;
		}
		++index;
		p = p->next;
	}

	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::unique() {
	int index = 0;
	if (empty()) {
		return *this;
	}
	for (Node<T>* p = head; p->next != nullptr; ) {
		if (p->data == p->next->data) {
			erase_back(iterator(p, index));
			continue;
		}
		++index;
		p = p->next;
	}
	
	return *this;
}

template<class T>
template<class F>
LinkList<T>& LinkList<T>::remove_if(F f) {
	int index = 0;
	while(head) {//head不为nullptr
		if (f(head->data)) {
			pop_front();
		}
		else {
			break;
		}
	}
	if (empty()) {//考虑了nullptr情况，后面访问next是安全的
		return *this;
	}
	for (Node<T>* p = head; p->next!= nullptr; ) {
		if (f(p->next->data)) {
			erase_back(iterator(p, index));
			continue;
		}
		++index;
		p = p->next;
	}
	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::remove(const T& value) {
	int index = 0;
	while (head) {
		if (head->data == value) {
			pop_front();
		}
		else {
			break;
		}

	}
	if (empty()) {//考虑了nullptr情况，后面访问next是安全的
		return *this;
	}
	for (Node<T>* p = head; p->next != nullptr; ) {
		if (p->next->data == value) {
			erase_back(iterator(p, index));
			continue;
		}
		++index;
		p = p->next;
	}
	return *this;
}

template<class T>
template<class Fj,class Fd>
LinkList<T>& LinkList<T>::deal_if(Fj fj,Fd fd) {
	for (iterator it = begin(); it != end(); ++it) {
		if (fj(*it)) {
			fd(*it);
		}
	}
	return *this;
}

template<class T>
template<class Fj, class Fd>
LinkList<T>& LinkList<T>::deal_if(iterator begin,iterator end,Fj fj, Fd fd) {
	for (iterator it = begin; it != end; ++it) {
		if (fj(*it)) {
			fd(*it);
		}
	}
	return *this;
}

template<class T>
template<class Fj, class Fd>
LinkList<T>& LinkList<T>::deal_if(iterator begin, Fj fj, Fd fd) {
	return deal_if(begin, end(), fj, fd);
}

template<class T>
template<class F>
LinkList<T>& LinkList<T>::replace_if(F f, const T& newValue) {
	for (iterator it = begin(); it != end(); ++it) {
		if (f(*it)) {
			*it = newValue;
		}
	}
	return *this;
}

template<class T>
LinkList<T>& LinkList<T>::replace(const T& oldValue, const T& newValue) {
	for (iterator it = begin(); it != end(); ++it) {
		if (*it == oldValue) {
			*it = newValue;
		}
	}
	return *this;
}

template<class T>
LinkList<T> LinkList<T>::reserve(bool mode) {
	LinkList<T> temp;
	for (Node<T>* p = head; p != nullptr; p = p->next) {
		temp.push_front(p->data);
	}
	if (mode) {
		*this = temp;
	}
	return temp;
}

template<class T>
LinkList<T>& LinkList<T>::swap(LinkList<T>& ls) {
	Node<T>* temp = this->head;
	this->head = ls.head;
	ls.head = temp;

	temp = this->tail;
	this->tail = ls.tail;
	ls.tail = temp;

	int t = this->len;
	this->len=ls.len;
	ls.len= t;

	return *this;
}

template<class T>
inline T& LinkList<T>::operator[](int index)
{
	Node<T>* p;
	int i = 0;
	for (p = head; i < index; ++i) {
		p = p->next;
	}
	// TODO: 在此处插入 return 语句
	return p->data;
}

template<class T>
inline const T& LinkList<T>::operator[](int index) const
{
	Node<T>* p;
	int i = 0;
	for (p = head; i < index; ++i) {
		p = p->next;
	}
	// TODO: 在此处插入 return 语句
	return const_cast<const T>(p->data);
}

template<class T>
inline T& LinkList<T>::at(int index)
{
	if (index >= len || index < 0) {
		throw std::out_of_range("at越界");
	}
	Node<T>* p;
	int i = 0;
	for (p = head; i < index; ++i) {
		p = p->next;
	}

	// TODO: 在此处插入 return 语句
	return p->data;
}

template<class T>
inline const T& LinkList<T>::at(int index) const
{
	if (index >= len || index<0) {
		throw std::out_of_range("at越界");
	}
	Node<T>* p;
	int i = 0;
	for (p = head; i < index; ++i) {
		p = p->next;
	}

	// TODO: 在此处插入 return 语句
	return const_cast<const T>(p->data);
}

template<class T>
inline void LinkList<T>::show()
{ 
	for (Node<T>* p = head; p != nullptr; p = p->next) {
		std::cout << p->data << ' ';
	}
	std::cout << std::endl;
}

template<class T>
template<class It>
inline LinkList<T>::LinkList(const It begin,const It end)
{
	len = 0;
	for (auto p = begin; p != end; ++p) {
		push_back(*p);
	}
}

template <class T>
inline int LinkList<T>::show(int with,Baseder& baseder,int y,int x) {
	using namespace std;
	baseder.gotoxy(y, x);
	std::cout << "(head)";
	int temp=with - 6;
	int col = 0;
	for (Node<T>* p = head; p != nullptr; p = p->next) {
		if (temp < 8) {
			baseder.gotoxy(++y, x);
			temp = with;
			++col;
			if (col >= 5) {
				cout << "...  ->";
				break;
			}
		}
		std::cout.width(6);
		std::cout <<left<< p->data;
		std::cout << "->";
		temp -= 8;
	}
	if (temp < 7 ) {
		baseder.gotoxy(++y, x);
	}
	std::cout << "nullptr" << std::endl;
	return y;
}

template<class T>
inline int LinkList<T>::showJosephus(int with, Baseder& baseder, int y, int x, int index)
{
	using namespace std;
	baseder.gotoxy(y, x);
	std::cout << "(head)";
	int temp = with - 6;
	int col = 0;
	int ti = 0;
	for (Node<T>* p = head; p != nullptr; p = p->next) {
		if (temp < 8) {
			baseder.gotoxy(++y, x);
			temp = with;
			++col;
			if (col >= 16) {
				cout << "...  ->";
				break;
			}
		}
		if (ti++ == index) {
			win::setColor(0x04);
			cout << " *";
			std::cout.width(4);
			cout << left << p->data;
			win::setColor();

			std::cout << "->";
			
		}
		else {
			cout << "  ";
			std::cout.width(4);
			std::cout << left << p->data;
			std::cout << "->";
		}
		temp -= 8;
	}
	if (temp < 7) {
		baseder.gotoxy(++y, x);
	}
	std::cout << "nullptr" << std::endl;
	return y;
}
#endif