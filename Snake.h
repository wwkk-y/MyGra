#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include "LinkList.h"
#include "Base.h"
#include <time.h>
class Snake
{
	struct Pos {
		int x;
		int y;
		bool operator!=(const Pos& p) const{
			return !(p.x == x && p.y == y);
		}
	};

	enum State{up,down,left,right};
	State state;//��ǰ�˶�״̬
	Pos food;//ʳ���λ��
	LinkList<Pos> ls;//��
	Base& base;//����
	int score;//��ǰ����

	Pos getFood(int xs,int ys,int xe,int ye) {//(xs,ys)->(xe,ye)��Χ�������ȡʳ��
		int x;
		int y;
		do{
			x = rand() % (xe - xs) + xs;
			y = rand() % (ye - ys) + ys;

		} while (ls.find({ x,y })!= ls.end());
		return { x,y };
	}

	double getTime(int restart = 0) {//����ʱ��
		double c = 1.0 / CLOCKS_PER_SEC;
		static clock_t t = 0;						
		if (restart || t == 0) t = clock();			
		return c * (clock() - t);					
	}

	void showScore();//��߷�չʾ
	void showAndSave();
	void move(double gap=0.2);//��ʼ�ƶ�
public:
	Snake(Base& base);
	void start();
};
#endif