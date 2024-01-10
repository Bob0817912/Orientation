#include"Inheritance.hpp"
#include"Polymorphism_dynamic.hpp"
#include"Polymorphism_static.hpp"
#include<iostream>

int main(){
    father f;
    son s;
    f.eat();
    f.sleep();
    // f.study(); //error
    s.play();
    s.sleep();
    // s.work(); //error
    s.age=18;
    std::cout<<s.age<<std::endl;
    s.name="xiejun";
    std::cout<<s.name<<std::endl;

    Math m;
    m.func(1);
    m.func(1.1);
    m.func(1,2);
    Time t;
    Date d;
    DateTime dt;
    t.showTime();
    d.showDate();
    dt.showTime();
    dt.showDate();


    
    return 0;

}