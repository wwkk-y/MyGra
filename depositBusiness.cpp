#include "depositBusiness.h"
#include <fstream>
#include <time.h>
#pragma warning(disable:4996)

depositBusiness::depositBusiness(Base& base, bool mode):base(base)
{
    if (mode) {
        read();
    }
}
depositBusiness& depositBusiness::save(const string& fileName)
{
    ofstream fout(fileName);
    fout << *this;
    fout.close();
    // TODO: 在此处插入 return 语句
    return *this;
}
depositBusiness& depositBusiness::read(const string& fileName)
{
    ifstream fin(fileName);
    fin >> *this;
    fin.close();
    // TODO: 在此处插入 return 语句
    return *this;
}

int depositBusiness::show(string& name, int& index)
{
    int num = 5;
    LabelBoxArr lba1(base, num, 4, 1, 1);
    LabelBoxArr lba2(base, num, 4, 1, lba1.getY()+1);
    LabelBoxArr lba3(base, num, 4, 1, lba1.getY() * 2+1);
    MenuItem items = { "姓名","操作","日期" ,"余额"};
    for (int i = 0; i < num; ++i) {
        lba1.getLb(i).setStr(items);
        lba2.getLb(i).setStr(items);
        lba3.getLb(i).setStr(items);
    }

    int numIndex = 0;
    int what = 1;
    int lsIndex = 0;
    auto pos = ls.begin();
    while (pos=ls.find_if([&name](const data& d) {return d.name == name; }, pos)) {
        ++numIndex;
        if (numIndex > index * 15) {
            const char* strls[] = { (*pos).name.c_str(),(*pos).opt.c_str() ,(*pos).date.c_str(),(*pos).balan.c_str() };
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
            if (lsIndex == num) {
                lsIndex = 0;
                ++what;
                if (what > 3) {
                    break;
                }
            }
        }
        ++pos;
    }
    lba1.showAll();
    lba2.showAll();
    lba3.showAll();

    return index;
}

depositBusiness& depositBusiness::findOpt(string& name)
{
    Baseder baseder(base);
    MenuItem items = { "上一页","下一页","返回" };
    Menu menu(25,baseder.getY(),baseder.getX()-25,0, baseder, items, 3);
    int choice = 0;
    int index = 0;
    show(name, index);
    while (1) {
        switch (choice = menu.show(choice)) {
        case 0:
            show(name, --index);
            break;
        case 1:
            show(name, ++index);
            break;
        default:
            baseder.close();
            return *this;

        }
    }   
}

depositBusiness& depositBusiness::addOpt(string& name)
{
    Baseder baseder(base);
    LabelBox lb(base, 4, base.getXH()-10, base.getYH()-5);
    MenuItem items = { "姓名","存入","日期" ,"余额" };
    lb.setStr(items);
    string date = getDate();
    string ba = getLast(name).balan;
    MenuItem itemsR = { name.c_str(),"",date.c_str() ,ba.c_str()};
    lb.setStrR(itemsR);
    
    lb.showAll();
    
    InputTips in(lb, 6, 3);
    in.setTips("输入一个数字");
    string opt = in.show();
    try {
        ls.push_back(data(name, string("+")+opt, date, to_string(stoi(ba) + stoi(opt))) ) ;
    }
    catch (...) {
        Baseder baseder(base);
        baseder.setText(baseder.getXH() - 8, baseder.getYH(), "输入不为数字!!!", 0xfd);
        baseder.draw();
        win::gotoxy(0, 0);
        eat();
        baseder.close();
    }

    // TODO: 在此处插入 return 语句
    baseder.close();
    return *this;
}

depositBusiness& depositBusiness::takeOpt(string& name)
{
    Baseder baseder(base);
    LabelBox lb(base, 4, base.getXH() - 10, base.getYH() - 5);
    MenuItem items = { "姓名","支取","日期" ,"余额" };
    lb.setStr(items);
    string date = getDate();
    string ba = getLast(name).balan;
    MenuItem itemsR = { name.c_str(),"",date.c_str() ,ba.c_str() };
    lb.setStrR(itemsR);

    lb.showAll();

    InputTips in(lb, 6, 3);
    in.setTips("输入一个数字");
    string opt = in.show();
    try {
        if (stoi(ba) - stoi(opt)<0) {
            Baseder baseder(base);
            baseder.setText(baseder.getXH() - 6, baseder.getYH(), "余额不足!!!", 0xfd);
            baseder.draw();
            win::gotoxy(0, 0);
            eat();
            baseder.close();
        }
        else {
            ls.push_back(data(name, string("-") + opt, date, to_string(stoi(ba) - stoi(opt))));
        }
    }
    catch (...) {
        Baseder baseder(base);
        baseder.setText(baseder.getXH() - 8, baseder.getYH(), "输入不为数字!!!", 0xfd);
        baseder.draw();
        win::gotoxy(0, 0);
        eat();
        baseder.close();
    }

    // TODO: 在此处插入 return 语句
    baseder.close();
    return *this;
}

depositBusiness::data depositBusiness::getLast(string& name)
{
    auto pos = ls.begin();
    auto t = pos;
    while (pos=ls.find_if([&name](const data& d) {return d.name == name; }, pos)) {
        t = pos;
        ++pos;
    }
    return *t;
}



depositBusiness& depositBusiness::login(string name)
{
    MenuItem items = { "存入","支取","查询","退出" };
    Menu menu(base, items, 4);

    if (!(ls.find_if([&name](const data& d) {return d.name == name; }) ) ) {
        menu.setText(menu.getXH()-8, menu.getYH(), "未找到该账户!!!", 0xfd);
        menu.draw();
        win::gotoxy(0, 0);
        eat();
        menu.close();
        return *this;
    }

    int choice = 0;
    while (1) {
        switch (choice = menu.show(choice)) {
        case 0:
            addOpt(name);
            break;
        case 1:
            takeOpt(name);
            break;
        case 2:
            findOpt(name);
            break;
        default:
            menu.close();
            return *this;
        }
    }
}

string depositBusiness::getDate()
{
    time_t t;//获取系统时间 
    struct tm* lt;
    time(&t);
    lt = localtime(&t); //转为时间结构。
    //cout << lt->tm_year + 1900 << lt->tm_mon + 1 << lt->tm_mday << endl;
    return to_string(lt->tm_year + 1900) + "_" + to_string(lt->tm_mon + 1) + "_" + to_string(lt->tm_mday);
    
}

string depositBusiness::getName()
{
    Baseder baseder(base);
    Label in(baseder, baseder.getXH()-17, baseder.getYH()-1,34);
    in.setStr("请输入账号:");
    string name = in.show();
    baseder.close();
    return name;
}

void depositBusiness::addUser()
{
    string name = getName();
    if (ls.find_if([&name](const data& d) {return d.name == name; })) {
        Baseder baseder(base);
        baseder.setText(baseder.getXH() - 8, baseder.getYH(), "该账户已存在!!!", 0xfd);
        baseder.draw();
        win::gotoxy(0, 0);
        eat();
        baseder.close();
    }
    else {
        ls.push_back(data(name,"开户",getDate(),"0"));
    }
}

void depositBusiness::start()
{
    MenuItem items = { "登录","开户","退出" };
    Menu menu(base, items, 3);
    int choice = 0;
    while (1) {
        switch (choice = menu.show(choice)) {
        case 0:
            login(getName());
            break;
        case 1:
            addUser();
            break;
        default:
            menu.close();
            return;
        }
    }
}


