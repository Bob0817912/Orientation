# C++ OOP && STL库
## 第一篇 OOP 篇
![C++](https://upload.wikimedia.org/wikipedia/commons/1/18/ISO_C%2B%2B_Logo.svg)
### 什么是面向对象(Object-oriented programming)？
>OOP 是面向对象编程的缩写。
>程序化编程是编写对数据进行操作的程序或函数，而面向对象编程则是创建包含数据和函数的对象。
### 为什么要面向对象编程？
> ==OOP 更快、更容易执行==。OOP 为程序提供了清晰的结构。OOP 有助于保持（"不要重复自己"），并使代码更易于维护、修改和调试。OOP 使创建完整的可重用应用程序成为可能，只需更少的代码和更短的开发时间。
### 面向对象的特性
#### 继承
**什么是继承？**
>继承是一个特征或过程，在这个过程中，从现有的类中创建新的类。创建的新类称为 "派生类 "或 "子类"，现有的类称为 "基类 "或 "父类"。派生类继承自基类
+ 可能看定义有一些晦涩，我们就写一个继承的代码，方便理解：
```c++
//写一个简单的继承给你们演示
#include<iostream>
using namespace std; //教学演示请勿模仿


class father{
    public:
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
/*
zh


*/
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
int main(int argc, char const *argv[]){
    son s;
    father f;
    s.eat();
    s.sleep();
    s.play();
    //s.work(); //子类不能继承父类的私有成员
    f.eat();
    f.sleep();
    //f.study(); //父类不能继承子类的私有成员
    return 0;
}
```
![class father and son](https://img-blog.csdnimg.cn/c9f7437b68004855aa7cc96d2bf4d1d3.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAa2VkYV94aWFvbGk=,size_20,color_FFFFFF,t_70,g_se,x_16)

#### 多态
**什么是多态？**
> ==多态 "一词的意思是具有多种形式。简单地说，我们可以把多态性定义为一种信息能够以多种形式显示==多态性在现实生活中的一个例子是，一个人可以同时具有不同的特征。一个人同时是父亲、丈夫和雇员。因此，同一个人在不同的情况下会表现出不同的行为。这就是所谓的多态性。多态性被认为是面向对象编程的重要特征之一。
**多态类型**
+ 编译时多态性
+ 运行时多态性
![](https://media.geeksforgeeks.org/wp-content/uploads/20200703160531/Polymorphism-in-CPP.png)

+ **编译时多态性**
**A.函数重载**
>如果存在多个同名但参数不同的函数，那么这些函数就被称为重载函数，也就是所谓的 "函数重载"。可以通过改变参数数量或/和改变参数类型来重载函数。简单地说，这是面向对象编程的一个特点，当在一个函数名下列出许多任务时，就会出现许多名称相同但参数不同的函数。在重载函数时，应遵循一定的函数重载规则。

下面的 C++ 程序展示了函数重载或编译时多态性：
```c++
//#include <bits/stdc++.h>//C++的万能开头
#include<iostream>
using namespace std;//教学使用，请勿模仿
class Math {
public:
    void func(int x)
    {
        cout << "value of x is " << x << endl;
    }

    void func(double x)
    {
        cout << "value of x is " << x << endl;
    }
 
    void func(int x, int y)
    {
        cout << "value of x and y is " << x << ", " << y
             << endl;
    }
};
 
int main()
{
    Math math;
 

    math.func(7);
 
    math.func(9.12);
 
    math.func(77, 64);
    return 0;
}


```
+ Output
>value of x is 7
>value of x is 9.12
>value of x and y is 77, 64

+ **说明**:在上例中，名为 function func() 的单个函数在三种不同情况下的作用各不相同，这就是多态性的一个特性。要了解更多相关信息，请参阅文章--[Function Overloading in C++](https://www.geeksforgeeks.org/function-overloading-c/)或[C++ 重载运算符和重载函数](https://www.runoob.com/cplusplus/cpp-overloading.html)
**笔者更推荐后者**

**运行时多态**
>C++运行时多态性是通过虚函数来实现的，虚函数允许子类重新定义成员函数，而子类重新定义父类的做法称为覆盖(Override)，或者称为重写。

**需要注意**：
+ 只有类的成员函数才能声明为虚函数，虚函数仅适用于有继承关系的类对象。普通函数不能声明为虚函数。
+ 静态成员函数不能是虚函数，因为静态成员函数不受限于某个对象。
+ 内联函数（inline）不能是虚函数，因为内联函数不能在运行中动态确定位置。
+ 构造函数不能是虚函数。
+ 析构函数可以是虚函数，而且建议声明为虚函数。

**什么是虚函数**
简单的定义不便于你理解，我们在代码中演示：
```c++
class One {
public:
    virtual void talk() {
        std::cout << "One::talk() is running" << std::endl;
    }
};

class Two : public One {
public:
    // 重写父类的talk()方法
    void talk() override {
        std::cout << "Two::talk() is running" << std::endl;
    }
};

int main() {
    One* o = new Two();
    o->talk();
    delete o; // 释放内存
    return 0;
}

```
如果我们运行这段代码，我们会发现结果是：
> Two::talk()is running

虚函数的本质是一块可以复写的内存，。它虚就虚在所谓"推迟联编"或者"动态联编"上，一个类函数的调用并不是在编译时刻被确定的，而是在运行时刻被确定的。由于编写代码的时候并不能确定被调用的是父类的函数还是哪个子类的函数，所以被成为"虚"函数。
**虚函数只能借助于指针或者引用来达到多态的效果。**


**什么是纯虚函数**
+ 声明纯虚函数是在基类中使用 virtual 关键字和 = 0 语法声明的。它们在基类中没有实现，必须由任何具体（非抽象）派生类重写。

+ 使用方法纯虚函数提供了派生类必须实现的接口。包含至少一个纯虚函数的类将成为抽象类，而抽象类的对象不能被实例化。
```c++
class AbstractShape {
public:
    virtual void draw() const = 0; 
    //定义一个纯虚函数
};

class ConcreteCircle : public AbstractShape {
public:
    void draw() const override {
        std::cout << "Drawing a concrete circle." << std::endl;
    }
};

```
**纯虚函数最显著的特征是**：它们必须在继承类中重新声明函数（不要后面的＝0，否则该派生类也不能实例化），而且它们在抽象类中往往没有定义。
#### 抽象类的介绍
抽象类是一种特殊的类，它是为了抽象和设计的目的为建立的，它处于继承层次结构的较上层。

+ 抽象类的定义： 
>==称带有纯虚函数的类为抽象类。==

+ 抽象类的作用： 
>抽象类的主要作用是将有关的操作作为结果接口组织在一个继承层次结构中，由它来为派生类提供一个公共的根，派生类将具体实现在其基类中作为接口的操作。所以派生类实际上刻画了一组子类的操作接口的通用语义，这些语义也传给子类，子类可以具体实现这些语义，也可以再将这些语义传给自己的子类。

+ **使用抽象类时注意：**
>抽象类只能作为基类来使用，其纯虚函数的实现由派生类给出。如果派生类中没有重新定义纯虚函数，而只是继承基类的纯虚函数，则这个派生类仍然还是一个抽象类。如果派生类中给出了基类纯虚函数的实现，则该派生类就不再是抽象类了，它是一个可以建立对象的具体的类。

==抽象类是不能定义对象的。==

#### 封装
**什么是封装？**
+ 在 C++ 中，封装是指将类似的数据和函数合并到一个称为类的单元中。通过封装这些函数和数据，我们可以保护数据不被更改。这一概念也被称为数据或信息隐藏

**C++ 中的封装有哪些优势？**
+ 将相关代码封装在类中有助于简化程序。您可以将代码封装在一个位置，这样您的代码就更容易理解了。

+ 这反过来又使程序更容易调试。如果封装类中的某个函数工作不正常，你很可能就能将问题锁定在该类上，而不必再对你的代码进行梳理。

+ 封装后，您就可以控制进出类的数据流。类允许你使某些函数或变量不可访问，以防止它们在类外被使用或更改。您还可以让特定组件可访问，以便在代码的其他地方使用。

**C++怎么利用的封装呢？**
+ public
+ private
+ protect
