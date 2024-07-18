#include "Snake.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

void Snake::showScore()
{
	ifstream fin("snakeScore.txt");
	int score = -1;
	fin >> score;
	string temp = string("最高分: ") + to_string(score);
	base.initMap();
	base.setText(base.getXH() - temp.size() / 2, base.getYH() - 1, temp.c_str());
	base.setText(base.getXH() - 6, base.getYH() + 2, "按回车键继续...");
	
	base.draw();
	base.gotoxy(0, 0);
	cin.get();

	fin.close();
}

void Snake::showAndSave()
{
	Baseder baseder(base);
	char score[12] = "score:  0";
	sprintf_s(score, "score: %-d", this->score);
	baseder.setText(baseder.getXH() - 3, baseder.getYH() - 2, "死亡！");
	baseder.setText(baseder.getXH() - strlen(score)/2, baseder.getYH(), score);
	baseder.setText(baseder.getXH() - 7, baseder.getYH()+2, "按回车键继续...");
	baseder.draw();
	
	//save
	ifstream fin("snakeScore.txt");
	int st;
	if (fin >> st) {
		if (st <this->score) {
			fin.close();
			ofstream fout("snakeScore.txt");
			fout << this->score;
		}
	}
	baseder.gotoxy(0, 0);
	eat();
}

void Snake::move(double gap)
{
	Baseder baseder(base);
	char score[12] = "score:  0";
	
	ls.clear();
	this->score = 0;
	state = up;
	food = getFood(1, 1, base.getX() - 1, base.getY() - 1);
	ls.push_back({ base.getXH(),base.getYH() });
	ls.push_back({ base.getXH(),base.getYH()+1 });
	ls.push_back({ base.getXH(),base.getYH()+2 });
	double time = getTime(1);//重置时间
	
	baseder.setText(base.getX() - 12, 1, score);
	
	baseder.initMap();
	for (const Pos& p : ls) {
		baseder.getmapColor()[p.y][p.x] = 0x8d;
	}
	baseder.getmapColor()[ls.front().y][ls.front().x] = 0xfd;
	baseder.getmapColor()[food.y][food.x] = 0xed;

	baseder.draw();
	double tgap = gap;//移动时间间隔
	while (1) {
		
		if (_kbhit()) {
			switch (_getch()) {
			case 'a':
			case 'A':
				if (state != right) {
					state = left;
					tgap = gap/2;
				}
				break;
			case 'd':
			case 'D':
				if (state != left) {
					state = right;
					tgap = gap/2;
				}
				break;
			case 'w':
			case 'W':
				if (state != down) {
					state = up;
					tgap = gap;
				}
				break;
			case 's':
			case 'S':
				if (state != up) {
					state = down;
					tgap = gap;
				}
				break;
			}
		}
	
		if (getTime() - time > tgap){
			//移动
			Pos temp = ls.front();
			if (temp.x == food.x && temp.y == food.y) {
				food = getFood(1, 1, base.getX() - 1, base.getY() - 1);
				++this->score;
				sprintf_s(score, "score: %-d", this->score);
			}
			else {
				ls.pop_back();//删除尾巴添加头的方式移动
			}

			bool live = true;//是否活着

			switch (state) {
			case up:
				ls.push_front({ temp.x,temp.y - 1 });
				break;
			case down:
				ls.push_front({ temp.x,temp.y + 1 });
				break;
			case left:
				ls.push_front({ temp.x - 1,temp.y });
				break;
			case right:
				ls.push_front({ temp.x + 1,temp.y});
				break;
			}
			//撞墙情况
			if (ls.front().x == 0 || ls.front().x == baseder.getX() - 1 || ls.front().y == 0 || ls.front().y == baseder.getY() - 1) {
				showAndSave();
				break;
			}
			//咬尾巴的情况
			else if (baseder.MapColor(ls.front().y, ls.front().x) == 0x8d){
				showAndSave();
				cin.get();
				break;
			}

			time = getTime(1);

			baseder.initMap();
			baseder.setText(base.getX() - 12, 1, score);
			for (const Pos& p : ls) {
				baseder.getmapColor()[p.y][p.x] = 0x8d;
			}
			baseder.getmapColor()[ls.front().y][ls.front().x] = 0xfd;
			baseder.getmapColor()[food.y][food.x] = 0xed;
			baseder.draw();
		}
	}
}

Snake::Snake(Base& base):base(base)
{
	srand((unsigned)time(nullptr));
	state = up;
	score = 0;
	food = { -1,-1 };
}

void Snake::start()
{
	MenuItem items = { "开始游戏","分数记录","上一级" };
	Menu menu(base, items, 3);
	int choice = 0;
	while (1) {
		switch (choice = menu.show(choice)) {
		case 0: {
			MenuItem items = { "简单","普通","困难" };
			Menu menu(base,items,3);
			switch (menu.show()) {
			case 0:
				move(0.2);
				break;
			case 1:
				move(0.1);
				break;
			case 2:
				move(0);
				break;
			}
			break;
		}
		case 1:
			showScore();
			break;
		default:
			return;
		}
	}
}
