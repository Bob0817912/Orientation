#ifndef POLYMORPHISM_STATIC_HPP
#define POLYMORPHISM_STATIC_HPP

#include <iostream>
#include <string>

using namespace std;//教学演示请勿模仿
//定义一个父类和子类，实现静态多态
class Math{
    public:
    void func(int x){
        cout<<"the value of x is "<<x<<endl;
    }
    void func(double x){
        cout<<"the value of x is "<<x<<endl;
    }
    void func(int x,int y){
        cout<<"the value of x and y is "<<x<<" "<<y<<endl;
    }
};

#endif // POLYMORPHISM_HPP