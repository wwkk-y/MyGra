#include "testJosephus.h"
#include "LinkList.h"
#include <conio.h>
#include <iostream>

void testJosephus(Base& base)
{
	
	Baseder up(base.getX()-2, 4, 1, 1, base);
	up.setBorderLine();
	up.setText(1, 1, "约瑟夫(Josephus)问题:",0x06);
	up.setText(1, 2, 
	"    有n个小孩(编号1~n)围成一圈，从第1个小孩开始按顺时针方向从1~m循环报数报到m的小孩出圈。最后剩下的小孩为胜利者。",0x06);
	
	Label lbNum(base, 1, 4, base.getXH()-1);
	Label lbGap(base, base.getXH()-1, 4, base.getX() - lbNum.getX()-1);
	lbNum.setStr("  请输入小孩人数n(数字)  ").setBorderLine();
	lbGap.setStr("  请输入间隔m(数字)  ").setBorderLine();
	
	Baseder region(base.getX() - 2, base.getY() - up.getY() - 2 - 1, 1, up.getY() + 2,base);
	region.setBorderLine('*');
	up.draw();
	
	int num=10;
	int gap=3;
	try {
		num = stoi(lbNum.show());
		gap = stoi(lbGap.show());
	}
	catch (...) {//如果输入不是数字
		lbNum.setStrR(to_string(num).c_str()).showAll();
		lbGap.setStrR(to_string(gap).c_str()).showAll();

	}
	if (num < 0) { num = 10; }//不可以小于0
	if (gap <= 0) { gap = 3; }

	showJosephus(region, num, gap);

	up.close(); lbNum.close(); lbGap.close(); region.close();
}

void showJosephus(Baseder& baseder, int num, int gap) {
	LinkList<string> ls;
	for (int i = 0; i < num; ++i) {
		ls.push_back(to_string(i+1));
	}

	win::setCursor(true);
	int yt = 1;
	int temp = 0;
	int count = 1;
	while (1) {
		yt=ls.showJosephus(baseder.getX() - 2, baseder, 1, 1, temp);
		baseder.gotoxy(yt + 1, 1);
		
		if (count == gap) {
			cout << ls[temp] << " 出局...";
			ls.erase(ls.begin()+temp);
			if (ls.size() == 1) {
				cout << "   " << ls[0] << " 胜利...";
				break;
			}
			eat();

			--temp;
			count = 0;
			

			baseder.gotoxy(yt, 1);
			for (int i = 0; i < baseder.getX() - 2; ++i) {
				cout << " ";
			}
			baseder.gotoxy(yt + 1, 1);
			for (int i = 0; i < baseder.getX() - 2; ++i) {
				cout << " ";
			}
			if (temp + 1 == ls.size()) {
				temp = -1;

			}
			++temp;
			++count;
			continue;
		}

		if (temp + 1 == ls.size()) {
			temp = -1;

		}

		static_cast<void>(_getch());
		++temp;
		++count;
	}

	cin.get();
	win::setCursor();
}