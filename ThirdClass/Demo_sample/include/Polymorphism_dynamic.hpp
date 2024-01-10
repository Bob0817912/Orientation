#ifndef POLYMORPHISM_DYNAMIC_HPP
#define POLYMORPHISM_DYNAMIC_HPP

#include <iostream>
#include <string>

using namespace std;//教学演示请勿模仿
//定义一个父类
class Time
{
public:
    Time(int h = 19, int m = 30, int s = 24) : hour(h), minute(m), second(s) {}
    virtual void showTime(){
        cout << hour << ":" << minute << ":" << second << endl;
    
    };  //虚函数
    virtual ~Time() {}              //虚析构函数
    
private:
    int hour;
    int minute;
    int second;
};

class Date
{
public:
    Date(int y = 2023, int m = 12, int d = 9) : year(y), month(m), day(d) {}
    virtual void showDate(){
        cout << year << "-" << month << "-" << day << endl;
    }
    virtual ~Date(){}

private:

    int year;
    int month;
    int day;
};

class DateTime : public Time, public Date
{
public:
    DateTime(int y = 0, int m = 0, int d = 0, int h = 0, int min = 0, int s = 0) : Date(y, m, d), Time(h, min, s) {}
    virtual void showTime(){
        cout << "Time: ";
        Time::showTime();
    }
    virtual void showDate(){
        cout << "Date: ";
        Date::showDate();
    }
    virtual ~DateTime() {}
};

#endif // POLYMORPHISM_DYNAMIC_HPP