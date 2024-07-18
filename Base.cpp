//图形库类实现
#include "Base.h"
#include <iostream>
#include <string>

using namespace std;

void win::setFont(int size) {//设置字体大小
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = size;  //设置字体大小
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL; //字体粗细 FW_BOLD
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void win::setSize(int w, int h)//设置窗口大小
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = { w, h };
    SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = { 1,1, w, h };
    SetConsoleWindowInfo(hOut, 1, &rc);
    return;
}

void win::gotoxy(int y, int x) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;//COORD pos = {x,y}; 
    SetConsoleCursorPosition(handle, pos);
}

void win::setCursor(bool mode)
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = mode;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}

void win::setColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

template<class T>
void myCpy(T* t1, const T* t2, int len) {
    for (int i = 0; i < len; ++i) {
        t1[i] = t2[i];
    }
}
void Base::cls()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = 0;//COORD pos = {x,y}; 
    SetConsoleCursorPosition(handle, pos);
}

void Base::hideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}

void Base::setColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

bool Base::judgeX(int x)
{
    if (x < 0 || x >= this->x) {
        cerr << "x 越界" << endl;
        cin.get();
        return true;
    }
    return false;
}

bool Base::judgeY(int y)
{
    if (y < 0 || y >= this->y) {
        cerr << "y 越界" << endl;
        cin.get();
        return true;
    }
    return false;
}

Base::Base(int x, int y) :x(x), y(y)
{
    char s[30];
    sprintf_s(s, "mode con cols=%d lines=%d", x, y + 1);
    system(s);//设置窗口大小 
    map = new char* [y];
    mapColor = new WORD * [y];
    for (int i = 0; i < y; ++i) {
        map[i] = new char[x];
        mapColor[i] = new WORD[x];
    }
    hideCursor();
    initMap();
}

Base::~Base()
{
    for (int i = 0; i < y; ++i) {
        delete[] map[i];
        delete[] mapColor[i];
    }
    delete[] map;
    delete[] mapColor;
    map = nullptr;
    mapColor = nullptr;
}

Base& Base::setBorder(char border, WORD color)
{
    int i;
    for (i = 0; i < x; i++) {
        map[0][i] = border;
        map[y - 1][i] = border;
        mapColor[0][i] = color;
        mapColor[y - 1][i] = color;
    }
    for (i = 1; i < y - 1; i++) {
        map[i][0] = border;
        map[i][x - 1] = border;
        mapColor[i][0] = color;
        mapColor[i][x - 1] = color;
    }
    return *this;
}

Base& Base::setBorderColor(WORD color)
{
    int i;
    for (i = 0; i < x; i++) {
        mapColor[0][i] = color;
        mapColor[y - 1][i] = color;
    }
    for (i = 1; i < y - 1; i++) {
        mapColor[i][0] = color;
        mapColor[i][x - 1] = color;
    }
    return *this;
}

Base& Base::setText(int x, int y, const char* s, WORD color, bool mode)
{
    if (mode) {
        int i;
        if (judgeY(y)) {
            throw "setText的y越界";
        }
        for (i = 0; s[i]; i++) {
            if (judgeX(x + i)) {
                throw "setText的x越界";
            }
            map[y][x + i] = s[i];
            mapColor[y][x + i] = color;
        }
    }
    else {
        int i;
        if (judgeX(x)) {
            throw "setText的x越界";
        }
        for (i = 0; s[i]; i++) {
            if (judgeY(y + i)) {
                throw "setText的y越界";
            }
            map[y + i][x] = s[i];
            mapColor[y + i][x] = color;
        }
    }
    return *this;
}

Base& Base::setBufColor(int xStart, int yStart, int xEnd, int yEnd, WORD color)
{
    int i, j;
    for (i = yStart; i <= yEnd; ++i) {
        if (judgeY(i)) {
            throw "setBufColor的y越界";
        }
        for (j = xStart; j <= xEnd; ++j) {
            if (judgeX(j)) {
                throw "setBufColor的x越界";
            }
            mapColor[i][j] = color;
        }
    }
    return *this;
}

Base& Base::setBufColor(int pos, int start, int end, WORD color, const char* mode)
{
    if (mode == nullptr) {
        if (judgeY(pos)) {
            throw "setBufColor的pos越界";
        }
        for (int i = start; i <= end; ++i) {
            if (judgeX(i)) {
                throw "setBufColor的x越界";
            }
            mapColor[pos][i] = color;
        }
    }
    else {
        if (judgeX(pos)) {
            throw "setBufColor的pos越界";
        }
        for (int i = start; i <= end; ++i) {
            if (judgeY(i)) {
                throw "setBufColor的y越界";
            }
            mapColor[i][pos] = color;
        }
    }
    return *this;
}

void Base::draw()
{
    cls();
    int i, j;
    for (i = 0; i < y; i++) {
        for (j = 0; j < x; j++) {
            setColor(mapColor[i][j]);
            cout << map[i][j];
        }
        cout << endl;
    }
}

Base& Base::initMap()
{
    int i, j;
    for (i = 0; i < y; i++) {
        for (j = 0; j < x; j++) {
            map[i][j] = ' ';
        }
    }
    setBorder('/');
    setBufColor(0, 0, x - 1, y - 1, 0x7);
    return *this;
}

Base& Base::gotoxy(int y, int x)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;//COORD pos = {x,y}; 
    SetConsoleCursorPosition(handle, pos);
    return *this;
}

Base& Base::setFont(int size)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = size;  //设置字体大小
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL; //字体粗细 FW_BOLD
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    return *this;
}



void Baseder::setColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

bool Baseder::judgeX(int x)
{
    if (x < 0 || x >= this->x) {
        cerr << "x 越界" << endl;
        cin.get();
        return true;
    }
    return false;
}

bool Baseder::judgeY(int y)
{
    if (y < 0 || y >= this->y) {
        cerr << "y 越界" << endl;
        cin.get();
        return true;
    }
    return false;
}

Baseder::Baseder(int x, int y, int xPos, int yPos, Base& base) :x(x), y(y), base(&base), baseder(nullptr), state(false), xpos(xPos), ypos(yPos)
{
    if (x + xPos > base.getX() || x < 0 || y + yPos>base.getY() || y < 0) {
        throw "Baseder越界";
    }
    map = new char* [y];
    mapColor = new WORD * [y];
    mapT = new char* [y];
    mapColorT = new WORD * [y];
    for (int i = 0; i < y; ++i) {
        mapT[i] = new char[x];
        mapColorT[i] = new WORD[x];
        map[i] = base.getMap(xPos, yPos + i);
        mapColor[i] = base.getMapColor(xPos, yPos + i);
        myCpy<char>(mapT[i], map[i], x);
        myCpy<WORD>(mapColorT[i], mapColor[i], x);
    }
    initMap();
}

Baseder::Baseder(int x, int y, int xPos, int yPos, Baseder& base) :x(x), y(y), baseder(&base), base(nullptr), state(false), xpos(xPos), ypos(yPos)
{
    if (x + xPos > base.getX() || x < 0 || y + yPos>base.getY() || y < 0) {
        throw "Baseder越界";
    }
    map = new char* [y];
    mapColor = new WORD * [y];
    mapT = new char* [y];
    mapColorT = new WORD * [y];
    for (int i = 0; i < y; ++i) {
        mapT[i] = new char[x];
        mapColorT[i] = new WORD[x];
        map[i] = base.getMap(xPos, yPos + i);
        mapColor[i] = base.getMapColor(xPos, yPos + i);
        myCpy<char>(mapT[i], map[i], x);
        myCpy<WORD>(mapColorT[i], mapColor[i], x);
    }
    initMap();
}

Baseder::~Baseder()
{
    reState();//释放mapT,mapColorT
    delete[] map;
    delete[] mapColor;
    map = nullptr;
    mapColor = nullptr;
}

void Baseder::reState()
{
    if (state) {
        return;
    }
    for (int i = 0; i < y; ++i) {
        delete[] mapT[i];
        delete[] mapColorT[i];
    }
    delete[] mapT;
    delete[] mapColorT;
    mapT = nullptr;
    mapColorT = nullptr;
    this->state = true;
}

Baseder& Baseder::setBorder(char border, WORD color)
{
    int i;
    for (i = 0; i < x; i++) {
        map[0][i] = border;
        map[y - 1][i] = border;
        mapColor[0][i] = color;
        mapColor[y - 1][i] = color;
    }
    for (i = 1; i < y - 1; i++) {
        map[i][0] = border;
        map[i][x - 1] = border;
        mapColor[i][0] = color;
        mapColor[i][x - 1] = color;
    }
    return *this;
}

Baseder& Baseder::setBorderColor(WORD color)
{
    int i;
    for (i = 0; i < x; i++) {
        mapColor[0][i] = color;
        mapColor[y - 1][i] = color;
    }
    for (i = 1; i < y - 1; i++) {
        mapColor[i][0] = color;
        mapColor[i][x - 1] = color;
    }
    return *this;
}

Baseder& Baseder::setBorderLine(char ch)
{
    for (int i = 1; i < getX() - 1; ++i) {
        map[0][i] = '-';
        map[getY() - 1][i] = '-';
    }
    map[0][0] = ch;
    map[0][getX() - 1] = ch;
    map[getY() - 1][0] = ch;
    map[getY() - 1][getX() - 1] = ch;

    for (int i = 1; i < getY() - 1; ++i) {
        map[i][0] = '|';
        map[i][getX() - 1] = '|';
    }

    // TODO: 在此处插入 return 语句
    return *this;
}

Baseder& Baseder::setText(int x, int y, const char* s, WORD color, bool mode)
{
    if (mode) {
        int i;
        if (judgeY(y)) {
            throw "setText的y越界";
        }
        for (i = 0; s[i]; i++) {
            if (judgeX(x + i)) {
                throw "setText的x越界";
            }
            map[y][x + i] = s[i];
            mapColor[y][x + i] = color;
        }
    }
    else {
        int i;
        if (judgeX(x)) {
            throw "setText的x越界";
        }
        for (i = 0; s[i]; i++) {
            if (judgeY(y + i)) {
                throw "setText的y越界";
            }
            map[y + i][x] = s[i];
            mapColor[y + i][x] = color;
        }
    }
    return *this;
}

Baseder& Baseder::setBufColor(int xStart, int yStart, int xEnd, int yEnd, WORD color)
{
    int i, j;
    for (i = yStart; i <= yEnd; ++i) {
        if (judgeY(i)) {
            throw "setBufColor的y越界";
        }
        for (j = xStart; j <= xEnd; ++j) {
            if (judgeX(j)) {
                throw "setBufColor的x越界";
            }
            mapColor[i][j] = color;
        }
    }
    return *this;
}

Baseder& Baseder::setBufColor(int pos, int start, int end, WORD color, const char* mode)
{
    if (mode == nullptr) {
        if (judgeY(pos)) {
            throw "setBufColor的pos越界";
        }
        for (int i = start; i <= end; ++i) {
            if (judgeX(i)) {
                throw "setBufColor的x越界";
            }
            mapColor[pos][i] = color;
        }
    }
    else {
        if (judgeX(pos)) {
            throw "setBufColor的pos越界";
        }
        for (int i = start; i <= end; ++i) {
            if (judgeY(i)) {
                throw "setBufColor的y越界";
            }
            mapColor[i][pos] = color;
        }
    }
    return *this;
}

Baseder& Baseder::setBkColor(WORD color, bool mode)
{
    if (mode) {
        setBufColor(0, 0, getX() - 1, getY() - 1, color);
    }
    else {
        setBufColor(1, 1, getX() - 2, getY() - 2, color);
    }

    // TODO: 在此处插入 return 语句
    return *this;
}

void Baseder::draw()
{
    if (base) {
        base->draw();
    }
    else {
        baseder->draw();
    }
}

Baseder& Baseder::initMap()
{
    int i, j;
    for (i = 0; i < y; i++) {
        for (j = 0; j < x; j++) {
            map[i][j] = ' ';
        }
    }
    setBorder('/');
    setBufColor(0, 0, x - 1, y - 1, 0x7);
    return *this;
}

void Baseder::close()
{
    //一个对象只能调用一次
    if (state) {
        return;
    }
    state = true;
    for (int i = 0; i < y; ++i) {
        myCpy<char>(map[i], mapT[i], x);
        myCpy<WORD>(mapColor[i], mapColorT[i], x);
        delete[] mapT[i];
        delete[] mapColorT[i];
    }
    delete[] mapT;
    delete[] mapColorT;
    mapT = nullptr;
    mapColorT = nullptr;
}

Baseder& Baseder::gotoxy(int y, int x)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x + getXPos();
    pos.Y = y + getYPos();//COORD pos = {x,y}; 
    SetConsoleCursorPosition(handle, pos);
    return *this;
}

Baseder& Baseder::setTitle(string str, bool mode)
{
    if (mode) {
        Label title(*this, 0, getY() - 3, getX());
        title.setText(getXH() - 4, 1, str.c_str(), 0xf4);
        title.setBkColor(0xf4);
        title.setBorderLine();
        title.draw();
    }
    else {
        Label title(*this, 0, 0, getX());
        title.setText(getXH() - 4, 1, str.c_str(), 0xf4);
        title.setBkColor(0xf4);
        title.setBorderLine();
        title.draw();
    }
    // TODO: 在此处插入 return 语句
    return *this;
}

Menu::Menu(int x, int y, int xPos, int yPos, Base& base, const char* str[], int num) :Baseder(x, y, xPos, yPos, base)
{
    this->num = num;
    this->str = new char* [num];
    for (int i = 0; i < num; ++i) {
        this->str[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(this->str[i], str[i], strlen(str[i]) + 1);
    }
}

Menu::Menu(int x, int y, int xPos, int yPos, Baseder& baseder, const char* str[], int num) :Baseder(x, y, xPos, yPos, baseder)
{
    this->num = num;
    this->str = new char* [num];
    for (int i = 0; i < num; ++i) {
        this->str[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(this->str[i], str[i], strlen(str[i]) + 1);
    }
}

Menu::Menu(Base& base, const char* str[], int num) :Baseder(base.getX(), base.getY(), 0, 0, base)
{
    this->num = num;
    this->str = new char* [num];
    for (int i = 0; i < num; ++i) {
        this->str[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(this->str[i], str[i], strlen(str[i]) + 1);
    }
}

Menu::Menu(Baseder& baseder, const char* str[], int num) :Baseder(baseder.getX(), baseder.getY(), 0, 0, baseder)
{
    this->num = num;
    this->str = new char* [num];
    for (int i = 0; i < num; ++i) {
        this->str[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(this->str[i], str[i], strlen(str[i]) + 1);
    }
}
/*
Menu::Menu(Menu& m) :Baseder(m.x, m.y, m.xpos, m.ypos, *m.base)
{
    this->num = m.num;
    this->str = new char* [m.num];
    for (int i = 0; i < m.num; ++i) {
        this->str[i] = new char[strlen(m.str[i]) + 1];
        myCpy<char>(this->str[i], m.str[i], strlen(m.str[i]) + 1);
    }
}*/
/*
Menu::Menu(int x, int y, int xPos, int yPos, Base& base, initializer_list<string> initls) :Baseder(x, y, xPos, yPos, base)
{
    this->num = initls.size();
    this->str = new char* [num];
    int i = 0;
    for (const string& p : initls) {
        str[i] = new char[p.size()+1];
        myCpy<char>(str[i], p.c_str(), p.size() + 1);
        ++i;
    }
}*/

Menu::~Menu()
{
    for (int i = 0; i < num; ++i) {
        delete[] str[i];
    }
    delete[] str;
    str = nullptr;
}

int Menu::show(int cho, bool init)
{
    if (num <= 1) {
        throw "元素数目太少(至少大于1)";
    }
    if (init) {
        initMap();
    }
    for (int i = 0; i < num; ++i) {
        Baseder::setText(getXH() - strlen(str[i]) / 2, getY() / (num + 1) * (i + 1), str[i]);
    }
    //Baseder::setText(getXH() - str[0].size() / 2, getY() / (num + 1) * 1, str[0].c_str());
    Baseder::setText(getXH() - strlen(str[cho]) / 2 - 2, getY() / (num + 1) * (cho + 1), "->");
    Baseder::setText(getXH() + strlen(str[cho]) / 2 + 1, getY() / (num + 1) * (cho + 1), "<-");
    Baseder::setBufColor(getY() / (num + 1) * (cho + 1), getXH() - strlen(str[cho]) / 2 - 2, getXH() + strlen(str[cho]) / 2 + 2, 0xfd);
    draw();

    char ch;
    int choice = cho;
    int tchoice;
    while (1) {
        ch = _getch();
        clsbuf();
        if (ch == '\r' || ch == 'j') {
            return choice;
        }
        else if (ch == 'w' || ch == 'W') {
            tchoice = choice;
            --choice;
            if (choice < 0) {
                choice = num - 1;
            }
        }
        else {
            tchoice = choice;
            ++choice;
            if (num == choice) {
                choice = 0;
            }
        }
        setText(getXH() - strlen(str[tchoice]) / 2 - 2, getY() / (num + 1) * (tchoice + 1), "  ");
        setText(getXH() + strlen(str[tchoice]) / 2 + 1, getY() / (num + 1) * (tchoice + 1), "  ");
        setBufColor(getY() / (num + 1) * (tchoice + 1), getXH() - strlen(str[tchoice]) / 2 - 2, getXH() + strlen(str[tchoice]) / 2 + 2, 0x0f);
        setText(getXH() - strlen(str[choice]) / 2 - 2, getY() / (num + 1) * (choice + 1), "->");
        setText(getXH() + strlen(str[choice]) / 2 + 1, getY() / (num + 1) * (choice + 1), "<-");
        setBufColor(getY() / (num + 1) * (choice + 1), getXH() - strlen(str[choice]) / 2 - 2, getXH() + strlen(str[choice]) / 2 + 2, 0xfd);
        draw();
    }
    return 1;
}

Menu& Menu::push(MenuItem item, int n)
{
    char** tstr = new char* [num];
    for (int i = 0; i < num; ++i) {
        tstr[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(tstr[i], str[i], strlen(str[i]) + 1);
    }

    for (int i = 0; i < num; ++i) {
        delete[] str[i];
    }
    delete[] str;
    str = nullptr;

    str = new char* [num + n];
    for (int i = 0; i < num; ++i) {
        str[i] = new char[strlen(tstr[i]) + 1];
        myCpy<char>(str[i], tstr[i], strlen(tstr[i]) + 1);
    }

    for (int i = 0; i < num; ++i) {
        delete[] tstr[i];
    }
    delete[] tstr;
    tstr = nullptr;

    for (int i = num; i < num + n; ++i) {
        str[i] = new char[strlen(item[i]) + 1];
        myCpy<char>(str[i], item[i], strlen(item[i]) + 1);
    }
    num += n;
    return *this;
}

Menu& Menu::push(const char* item)
{
    char** tstr = new char* [num];
    for (int i = 0; i < num; ++i) {
        tstr[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(tstr[i], str[i], strlen(str[i]) + 1);
    }

    for (int i = 0; i < num; ++i) {
        delete[] str[i];
    }
    delete[] str;
    str = nullptr;

    str = new char* [num + 1];
    for (int i = 0; i < num; ++i) {
        str[i] = new char[strlen(tstr[i]) + 1];
        myCpy<char>(str[i], tstr[i], strlen(tstr[i]) + 1);
    }

    for (int i = 0; i < num; ++i) {
        delete[] tstr[i];
    }
    delete[] tstr;
    tstr = nullptr;

    str[num] = new char[strlen(item) + 1];
    myCpy<char>(str[num], item, strlen(item) + 1);
    num += 1;
    return *this;
}

bool Menu::insert(MenuItem item, int qui, int index)
{
    if (index >= num) {
        return true;
    }

    char** tstr = new char* [num + qui];
    for (int i = 0; i < index; ++i) {
        tstr[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(tstr[i], str[i], strlen(str[i]) + 1);
    }

    for (int i = index; i < index + qui; ++i) {
        tstr[i] = new char[strlen(item[i - index]) + 1];
        myCpy<char>(tstr[i], item[i - index], strlen(item[i - index]) + 1);
    }

    for (int i = index + qui; i < num + qui; ++i) {
        tstr[i] = new char[strlen(str[i - qui]) + 1];
        myCpy<char>(tstr[i], str[i - qui], strlen(str[i - qui]) + 1);
    }

    reset(tstr, num + qui);

    for (int i = 0; i < num/*reset里num已经变了*/; ++i) {
        delete[] tstr[i];
    }
    delete[] tstr;
    tstr = nullptr;

    return false;
}

bool Menu::insert(const char* item, int index)
{
    if (index >= num) {
        return true;
    }

    char** tstr = new char* [num + 1];
    for (int i = 0; i < index; ++i) {
        tstr[i] = new char[strlen(str[i]) + 1];
        myCpy<char>(tstr[i], str[i], strlen(str[i]) + 1);
    }

    tstr[index] = new char[strlen(item) + 1];
    myCpy<char>(tstr[index], item, strlen(item) + 1);

    myCpy<char>(tstr[index], item, strlen(item) + 1);
    for (int i = index + 1; i < num + 1; ++i) {
        tstr[i] = new char[strlen(str[i - 1]) + 1];
        myCpy<char>(tstr[i], str[i - 1], strlen(str[i - 1]) + 1);
    }

    reset(tstr, num + 1);

    for (int i = 0; i < num/*reset里num已经加一了*/; ++i) {
        delete[] tstr[i];
    }
    delete[] tstr;
    tstr = nullptr;

    return false;
}

Menu& Menu::reset(MenuItem item, int num)
{
    for (int i = 0; i < this->num; ++i) {
        delete[] str[i];
    }
    delete[] str;
    str = nullptr;

    str = new char* [num];
    for (int i = 0; i < num; ++i) {
        str[i] = new char[strlen(item[i]) + 1];
        myCpy<char>(str[i], item[i], strlen(item[i]) + 1);
    }
    this->num = num;

    return *this;
}

Menu& Menu::reset(char** item, int num)
{
    for (int i = 0; i < this->num; ++i) {
        delete[] str[i];
    }
    delete[] str;
    str = nullptr;

    str = new char* [num];
    for (int i = 0; i < num; ++i) {
        str[i] = new char[strlen(item[i]) + 1];
        myCpy<char>(str[i], item[i], strlen(item[i]) + 1);
    }
    this->num = num;

    return *this;
}

string Input::show()
{
    gotoxy(0, 0);
    win::setCursor(true);
    string str;
    getline(cin, str);
    win::setCursor();
    return str;
}

string InputBox::show(bool mode)
{
    if (mode) {
        initMap();
        for (int i = 1; i < getX() - 1; ++i) {
            map[0][i] = '-';
            map[2][i] = '-';
        }
        map[0][0] = ' ';
        map[0][getX() - 1] = ' ';
        map[1][0] = '|';
        map[1][getX() - 1] = '|';
        map[2][0] = ' ';
        map[2][getX() - 1] = ' ';
    }

    draw();
    input.gotoxy(0, 0);
    string str;
    win::setCursor(true);
    getline(cin, str);
    win::setCursor();
    return str;
}

Label& Label::setStr(const string& str)
{
    if (str.size() >= getX() - 2) {
        throw "setStr越界";
    }
    this->str = str;

    // TODO: 在此处插入 return 语句
    return *this;
}

string Label::show(bool mode)
{
    if (str.empty()) {
        strR = inputBox.show(mode);
        if (strR.size() > getX() - 3 - str.size()) {
            string strT(strR.begin(), strR.begin() + (getX() - 3 - str.size()));
            strR = strT;
        }
        return strR;
    }
    else {
        if (mode) {
            initMap();
            map[1][str.size() + 1] = '|';
            setBorderLine().setText(1, 1, str.c_str()).draw();
            win::setCursor(true);
            gotoxy(1, str.size() + 2);
            getline(cin, strR);
            win::setCursor();
            if (strR.size() > getX() - 3 - str.size()) {
                string strT(strR.begin(), strR.begin() + (getX() - 3 - str.size()));
                strR = strT;
            }
            showAll();
            return strR;
        }

    }
    return "";
}

void Label::showAll()
{
    if (str.empty() && strR.empty()) {
        return;
    }
    initMap();
    if (strR.size()) {
        map[1][str.size() + 1] = '|';//如果没有输入的内容就不显示分界点
    }

    setBorderLine().setText(1, 1, str.c_str());
    setText(2 + str.size(), 1, strR.c_str());
    draw();
}

LabelBox& LabelBox::setBorderLine()
{
    char c = '=';
    for (int i = 1; i < getX() - 1; ++i) {
        map[0][i] = c;
        map[getY() - 1][i] = c;
    }
    c = 'O';
    map[0][0] = c;
    map[0][getX() - 1] = c;
    map[getY() - 1][0] = c;
    map[getY() - 1][getX() - 1] = c;

    c = '|';
    for (int i = 1; i < getY() - 1; ++i) {
        map[i][0] = c;
        map[i][getX() - 1] = c;
    }

    // TODO: 在此处插入 return 语句
    return *this;
}

LabelBox& LabelBox::setStr(const string& str, int index)
{
    this->str[index] = str;
    // TODO: 在此处插入 return 语句
    return *this;
}

LabelBox& LabelBox::setStrR(const string& str, int index)
{
    this->str[index] = str;
    // TODO: 在此处插入 return 语句
    return *this;
}

string& LabelBox::getStr(int index)
{
    if (index >= str.size() && index < num) {
        for (int i = str.size() - 1; i < index; ++i) {
            str.push_back("");
        }
    }
    // TODO: 在此处插入 return 语句
    return str.at(index);
}

string& LabelBox::getStrR(int index)
{
    if (index >= strR.size() && index < num) {
        for (int i = strR.size() - 1; i < index; ++i) {
            strR.push_back("");
        }
    }
    // TODO: 在此处插入 return 语句
    return strR.at(index);
}

void LabelBox::show()
{
    showAll();
    win::setCursor(true);
    strR = vector<string>(str.size());
    for (int i = 0; i < str.size(); ++i) {
        int strRX = (i < str.size() ? str[i].size() + 1 : 1) + 1, strRY = 1 + 2 * i;
        gotoxy(strRY, strRX - 1);
        cout << "|";
        getline(cin, strR[i]);
        if (strR[i].size() > getX() - 3 - str[i].size()) {
            string strT(strR[i].begin(), strR[i].begin() + (getX() - 3 - str[i].size()));
            strR[i] = strT;
        }
    }
    win::setCursor();
    showAll();
}

void LabelBox::showAll()
{
    initMap();
    setBorderLine();
    string strLine;
    for (int i = 0; i < getX() - 2; ++i) {
        strLine.push_back('-');
    }
    int len = str.size() > strR.size() ? str.size() : strR.size();
    for (int i = 0; i < len; ++i) {
        int strX = 1, strY = 1 + 2 * i;
        int strRX = (i < str.size() ? str[i].size() + 1 : 1) + 1, strRY = strY;
        if (i < str.size()) {
            setText(strX, strY, str[i].c_str());
        }
        if (i < strR.size()) {
            setText(strRX - 1, strRY, "|");
            setText(strRX, strRY, strR[i].c_str());
        }
        if (i != len - 1) {
            setText(1, strY + 1, strLine.c_str());
        }
    }
    draw();
}

LabelBoxArr::LabelBoxArr(Base& base, int num, int labelNum, int xPos, int yPos, int WITH) :num(num), Baseder((WITH - 1)* num + 1, labelNum * 2 + 1, xPos, yPos, base)
{
    head = lb.allocate(num);
    auto p = head;
    int tnum = 0;
    while (tnum < num) {
        lb.construct(p++, *this, labelNum, tnum * (WITH - 1), 0, WITH);
        ++tnum;
    }
}

LabelBoxArr::LabelBoxArr(Baseder& baseder, int num, int labelNum, int xPos, int yPos, int WITH) :num(num), Baseder((WITH - 1)* num + 1, labelNum * 2 + 1, xPos, yPos, baseder)
{
    head = lb.allocate(num);
    auto p = head;
    int tnum = 0;
    while (tnum < num) {
        lb.construct(p++, *this, labelNum, tnum * (WITH - 1), 0, WITH);
        ++tnum;
    }
}

LabelBoxArr::~LabelBoxArr()
{
    for (int i = 0; i < num; ++i) {
        lb.destroy(head + i);
    }
    lb.deallocate(head, num);
}

LabelBox& LabelBoxArr::getLb(int index)
{
    if (index >= num) {
        throw std::out_of_range("getLb越界");
    }
    // TODO: 在此处插入 return 语句
    return head[index];
}

void LabelBoxArr::show(bool mode)
{
    if (mode) {
        showAll();
    }
    for (int i = 0; i < num; ++i) {
        head[i].show();
    }
}

void LabelBoxArr::showAll()
{
    setBorder(' ');
    for (int i = 0; i < num; ++i) {
        if (!head[i].isNullR())
            head[i].showAll();
    }
}

void LabelBoxArr::showQueue()
{
    initMap();
    setBorder(' ');
    for (int i = 0; i < num; ++i) {
        head[i].show();
    }
}

bool LabelBoxArr::isNull()
{
    int num = 0;
    for (int i = 0; i < this->num; ++i) {
        if (head[i].isNull()) {
            ++num;
        }
    }
    if (num == this->num) {
        return true;
    }
    return false;
}

string& InputTips::show()
{
    gotoxy(0, 0);
    win::setCursor(true);
    setColor(0x06);
    cout << tips;
    gotoxy(0, 0);
    setColor(0x7);

    string temp;
    getline(cin, temp);
    win::setCursor();
    if (temp.size()) {
        tips = temp;
    }
    return tips;
}

InputTips& InputTips::setTips(const string& tip)
{
    tips = tip;
    // TODO: 在此处插入 return 语句
    return *this;
}
