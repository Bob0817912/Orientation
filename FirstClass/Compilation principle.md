# ~~C/C++编译原理~~ 
# 免责声明：
**学长也只是比你们早来了一年电🧱，所以也会犯错误，如果发现了我的错误，请狠狠的指正我，谢谢💐💐💐**
# 编译原理
+ 对于平常的应用程序及开发，我们常使用的IDE，如微软公司的**Visual Studio**,jetbrain公司的**Clion**等，这样的编译和链接的过程一步完成，通常这种合并在一起的过程称为**构建**,但简单的一句 ```gcc helloworld.c``` ,就包含了非常复杂的过程
+ 现代编译器和IDE所集成的默认配置，编译和链接参数对于大部分的应用程序开发和工程已经相当够用，但是在这种开发过程中，我们往往由于这种IDE的**娇生惯养**，导致我们这些**婴幼儿**程序员在面临一些程序的性能瓶颈束手无策，因为不了解程序背后的本质，所以我们要学习编译原理，这对于一个C++和其他C系语言以及他们的亲戚们的(包括沙比缝合怪)的**工程师**尤为重要

在这里引用《三体》中的一段话。

> 成吉思汗的骑兵，攻击速度与二十世纪的装甲部队相当;北宋的床弩，射程达一千五百米，与二十世纪的狙击步枪差不多;但这些仍不过是古代的骑兵与弓弩而已，不可能与现代力量抗衡。**基础理论决定一切**，未来史学派清楚地看到了这一点。而你们，却被回光返照的低级技术蒙住了眼睛。

---------------------------------------

## 什么是编译器

## 被隐藏的过程
+ 经典的hello world程序作为学习计算机的你来说闭着眼睛都能敲出来
```C
#include<stdio.h>
int main(void){
    printf("hello world\n");
    return 0;
}

```
+ 在windows下我们在配置gcc后就可以通过
```
gcc helloworld.c
```
就会产生了 **.exe**文件产生结果；
而在 **linux**系统下：
```
gcc helloworld.c
./a.out
```
结果：
```
hello world
```
事实上经过了四个步骤：
* 预处理(preprocessing)：根据已放置的文件中的预处理指令来修改源文件的内容
* 编译(compilation)：通过词法分析和语法分析，在确认所有指令都是符合语法规则之后，将其翻译成等价的中间代码表示或汇编代码
* 汇编(assembly)：把汇编语言代码翻译成目标机器指令的过程
* 链接(linking)：找到所有用到的函数所在的目标文件，并把它们链接在一起合成为可执行文件(executable file)
![编译原理](https://static.javatpoint.com/cpages/images/compilation-process-in-c3.png)

## 预处理
+ 预处理器是在程序源文件被编译之前根据预处理指令对程序源文件进行处理的程序。**预处理器指令以#号开头标识，末尾不包含分号**。预处理命令不是C/C++语言本身的组成部分，不能直接对它们进行编译和链接。C/C++语言的一个重要功能是可以使用预处理指令和具有预处理的功能。C/C++提供的预处理功能主要有文件包含、宏替换、条件编译等。
预处理的命令
```shell
gcc -E helloworld.c -o hello.i
#另外一种形式
cpp helloworld.c > helloworld.i

```
## 头文件包含

头文件是一种文本文件，使用文本编辑器将代码编写好之后，以扩展名.h(.hpp)保存就行了。头文件中一般放一些重复使用的代码，例如函数声明、变量声明、常数定义、宏的定义等等。当使用预处理指令`#include`引用头文件时，相当于将头文件中所有内容，复制到include处。
 
那么编译器在哪里找到include的头文件呢？这就涉及到了 include 的搜索机制。
头文件有两种：
```C++
#include<Library.h>
#include"Library.h"
```
这两种有什么区别呢？
+ 在使用 **<>** 时，编译器会在标准系统目录中搜索指定文件。这些目录由编译器预定义，通常包含系统或库头文件。
该语法通常用于包含标准库头文件
+ 使用 **“”** 时，编译器会首先在当前目录下查找指定文件。如果在当前目录下找不到该文件，编译器就会在标准系统目录下搜索。
这种语法通常用于包含作为项目或程序一部分的头文件
系统目录一般是：
```C
/usr/include
/usr/local/include
/usr/lib/gcc-lib/linux/11/include
```
**每个人不一样的，别直接以为我的就是绝对的**
* 这里有一个不错的提问，可以有机会看看：
[How to add a default include path for gcc in linux?](
https://stackoverflow.com/questions/558803/how-can-i-add-a-default-include-path-for-gcc-in-linux）)
虽然linux本身就带有gcc，但是这些还是你需要了解的；
# **注意**
+ 对于用户自己编写的头文件，宜用双引号形式。对于系统提供的头文件，既可以用尖括号形式，也可以用双引号形式，它们都能找到被包含的文件，但显然用尖括号形式更直截了当，效率更高。
**但是有一些C语言书籍的笔者写的时候常常用“”，这就是不好好学编译原理的原因，请大家不要养成不好的习惯**

## 宏替换
+ 首先什么是宏？
    宏的格式如下：
```
#define <宏名/标识符> <字符串>
```
举例来说：
```C
#define PI 3.14
```
## **说明**

①宏名一般用大写

②宏定义末尾不加分好;

③可以用#undef命令终止宏定义的作用域

④宏定义可以嵌套

⑤字符串“”中永远不包含宏

⑥宏替换在编译前进行，不分配内存，变量定义分配内存，函数调用在编译后程序运行时进行，并且分配内存

⑦预处理是在编译之前的处理，而编译工作的任务之一就是语法检查，预处理不做语法检查

⑧使用宏可提高程序的通用性和易读性，减少不一致性，减少输入错误和便于修改。例如：数组大小常用宏定义
 ## 编译
+ 这里引用[Compile](https://users.cs.utah.edu/~germain/PPS/Topics/C_Language/compiling_C_programs.html#:~:text=Compiling%20a%20C%20Program,A%20compiler%20is%20a%20program.)文档里的一句话：
**Compiling is the transformation from Source Code (human readable) into machine code (computer executable). A compiler is a program. A compiler takes the recipe (code) for a new program (written in a high level language) and transforms this Code into a new language (Machine Language) that can be understood by the computer itself. This "machine language" is difficult to impossible for humans to read and understand (much less debug and maintain), thus the need for "high level languages" such as C.**
编译使用的命令是：
处理的命令
```shell
g++ -g -pedantic -Wall -o executable_file_name source_file_name.C

```

+ 但**值得注意的是**在现代版本的GCC将预编译和编译合成为一个步骤，使用一个叫做**ccl**的命令来完成这两个步骤:
这里以笔者的电脑为例
```
cd /usr/lib/gcc/x86_64-linux-gnu/11/ccl
$ /usr/lib/gcc/x86_64-linux-gnu/11/ccl helloworld.c

```
+ 对于c语言来说，这个预编译和编译过程的命令是cc1,对于C++来说，有对应的程序是cc1plus，Java是jc1
C++的编译有一篇小小博客希望你喜欢[C++ compile](https://www.codecademy.com/article/cpp-compile-execute-locally)

+ 实际上gcc只是上面那些程序的包装，它会根据不同的参数去要求调用**预编译编译程序cc1,汇编器as，链接器ld**
## 汇编
这里放一张图片可能更明显 
 ![汇编过程](https://static.javatpoint.com/cpages/images/compilation-process-in-c.png)
 而在编译语言中，就是将预处理的文件经过汇编器转换为机器能够看懂的二进制文件；
 我们可以使用gcc来帮助我们实现
 ```
 gcc -c helloworld.s -o helloworld.o
 ```
也可以直接调用汇编器：
```
$as helloworld.s -o helloworld.o
```
 
 ## 链接
 + 链接其实是这四步中最麻烦的，也是最不容易让人理解的部分
 链接其实就是从多个对象文件(object file)来生成一个可执行文件(executable file)
 #### 为什么要有链接器呢？
 + 在我们编写工程的时候，在编译过程中，如果编译器找不到某个函数的定义，它会简单地认为该函数是在另一个文件中定义的。如果不是这种情况，编译器就会呆掉了
 + 它不会一次查看多个文件的内容。但是，链接器可能会查看许多文件，并试图找到未提及的函数的引用。
 + 相反，它使用所谓的 "条件编译"。因此，必须只编译那些有变化的源文件。至于其他文件，目标文件是链接器的适当输入。

+ 最后，它还使预编译代码库的实施变得更加容易。只需创建对象文件，然后像链接其他对象文件一样链接它们即可。我们将其称为 "单独编译模式"，因为每个文件都是与其他文件中的信息分开编译的。

+ 为了充分发挥条件编译的优势，找一个程序来帮助你可能比试图记住上次编译后你修改了哪些文件要容易得多。如果使用集成开发环境 (IDE)，就可以自己解决这个问题
+ 结论
因此，了解编译阶段和链接阶段之间的区别至关重要。换句话说，这可以让查找错误变得更容易。编译器错误一般都是语法错误--少了一个分号，多了一个括号。

另外，链接错误一般涉及缺失或多重定义。如果从链接器中得到一个函数或变量被多次定义的错误信息，那么很可能是两个源代码文件中存在相同的函数或变量。

[gcc编译原理](https://blog.csdn.net/u013836909/article/details/81106715#:~:text=%E9%93%BE%E6%8E%A5%E6%98%AF%E5%B0%86%E5%90%84%E7%A7%8D,%E4%BD%BF%E5%BE%97%E5%88%86%E7%A6%BB%E7%BC%96%E8%AF%91%E6%88%90%E4%B8%BA%E5%8F%AF%E8%83%BD%E3%80%82)
[C与C++编译原理及链接](https://zhuanlan.zhihu.com/p/346787730)