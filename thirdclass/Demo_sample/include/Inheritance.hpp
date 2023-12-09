#pragma once //防止头文件重复包含
#include<iostream>
#include<string>
using namespace std; //教学演示请勿模仿


class father{
    public:
    int age;
    string name;
    void eat(){
        cout<<"father like eating"<<endl;
    }
    void sleep(){
        cout<<"father can sleep"<<endl;
    }
    private:
    void work(){
        cout<<"father can work"<<endl;
    }
};
//子类继承父类的所有公有成员和保护成员，但是不继承私有成员
class son : public father{
    public:
    void play(){
        cout<<"son like playing  computergame"<<endl;
    }
    void sleep(){
        cout<<"son can sleep"<<endl;
    }
    private:
    void study(){
        cout<<"son can go to school"<<endl;
    }
};  
