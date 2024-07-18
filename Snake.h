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
	State state;//当前运动状态
	Pos food;//食物的位置
	LinkList<Pos> ls;//蛇
	Base& base;//窗口
	int score;//当前分数

	Pos getFood(int xs,int ys,int xe,int ye) {//(xs,ys)->(xe,ye)范围内随机获取食物
		int x;
		int y;
		do{
			x = rand() % (xe - xs) + xs;
			y = rand() % (ye - ys) + ys;

		} while (ls.find({ x,y })!= ls.end());
		return { x,y };
	}

	double getTime(int restart = 0) {//计算时间
		double c = 1.0 / CLOCKS_PER_SEC;
		static clock_t t = 0;						
		if (restart || t == 0) t = clock();			
		return c * (clock() - t);					
	}

	void showScore();//最高分展示
	void showAndSave();
	void move(double gap=0.2);//开始移动
public:
	Snake(Base& base);
	void start();
};
#endif