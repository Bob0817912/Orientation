# OpenCV 教程（C++版）
无良作者：王炽炽只会睡觉觉

---

## 什么是OpenCV?
* **OpenCV**（Open Source Computer Vision Library）是一个开源的计算机视觉和机器学习软件库。它由一系列的C函数和少量C++类构成，同时提供Python、Java和MATLAB等语言的接口，实现了图像处理和计算机视觉方面的很多通用算法。
* OpenCV的设计目标是提供一套简单而且可扩展的计算机视觉库，使得它能够方便地在实际的应用、研究、开发中被使用。

## OpenCV的历史
* OpenCV的起源可以追溯到1999年，当时在英特尔公司由一群热情的研发工程师开始进行开发。2000年，OpenCV以开源的方式发布，旨在推动计算机视觉的发展并帮助更多人应用这一技术。自此之后，OpenCV已经不断发展，增加了大量新的功能，并已成为全球最流行的计算机视觉库之一。

## Mat类的介绍
* Mat 类用来保存矩阵类型的数据信息，包括向量、矩阵、灰度或彩色图像等数据。
* Mat类分为矩阵头和指向存储数据的矩阵指针两部分。矩阵头中包含矩阵的尺寸、存储方法、地址和引用次数等。矩阵头的大小是一个常数，不会随着矩阵尺寸的大小而改变。
* 因此图像复制和传递过程中主要的开销是存放矩阵数据。为了解决这个问题，在 OpenCV 中复制和传递图像时，只是复制了矩阵头和指向存储数据的指针 **（浅拷贝）**

```cpp
// Mat的相关参数
cv::Mat M;
int depth = M.depth();	//元素数据类型，枚举型，0为CV_8U
int channels = M.channels();  	//色彩通道数
int nRows = M.rows; 	//行数，图像高度
int nCols = M.cols;  		//列数，图像宽度
uchar * data = M.data;	//图像地址
int nDims = M.dims;		//图像维度
int nElSize = M.elemSize();	//每个像素字节数
int nElSize1 = M.elemSize1();	//每个像素单通道的字节数
int type = M.type();		//元素数据类型及通道数，枚举型

//Mat拷贝
cv::Mat A,B;
//浅拷贝
B=M;
B(M);
//深拷贝
M.copyTo(A);
```

## 图像的读取与显示
```cpp
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main() {
    cv::Mat image, img;
    image = cv::imread("/home/nishangyumei/code/opencv-teach/src/0001.png", cv::IMREAD_COLOR);
    cv::resize(image, img, cv::Size(240 * 4, 320 * 4));

    cv::namedWindow("test", cv::WINDOW_NORMAL);
    cv::imshow("test", img);
    cv::waitKey(0);
    return 0;
}
```
### imread()函数
* imread()函数读取图像形式参数

| 标志参数         | 简记 | 作用                                                  |
| ---------------- | ---- | ----------------------------------------------------- |
| IMREAD_UNCHANGED | -1   | 按照图像原样读取，保留Alpha通道（第4通道）            |
| IMREAD_GRAYSCALE | 0    | 将图像转成单通道灰度图像后读取                        |
| IMREAD_COLOR     | 1    | 将图像转换成3通道BGR彩色图像                          |
| IMREAD_ANYCOLOR  | 2    | 保留原图像的16位、32位深度，不声明该参数则转成8位读取 |
| IMREAD_LOAD_LDAL | 4    | 以任何可能的颜色读取图像                              |

### namedWindow()函数
* namedWindow()函数窗口属性标志参数

| 标志参数            | 简记       | 作用                                     |
| ------------------- | ---------- | ---------------------------------------- |
| WINDOW NORMAL       | 0x00000000 | 显示图像后，允许用户随意调整窗口大小     |
| WINDOW_AUTOSIZE     | 0x00000001 | 根据图像大小显示窗口，不允许用户调整大小 |
| WINDOW_OPENGL       | 0x00001000 | 创建窗口的时候会支持OpenGL               |
| WINDOW_FULLSCREEN   | 1          | 全屏显示窗口                             |
| WINDOW_FREERATIO    | 0x00000100 | 调整图像尺寸以充满窗口                   |
| WTNDOW_KEEPRATIO    | 0x00000000 | 保持图像的比例                           |
| WINDOW GUI_EXPANDED | 0x00000000 | 创建的窗口允许添加工具栏和状态栏         |
| WINDOW GUI_NORMAL   | 0x00000010 | 创建没有状态栏和工具栏的窗口             |

## 一些方法喵

以下は同期生のWang Chiが書いたものです
### 颜色转化 cvtColor()
```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    // 导入文件
    cv::Mat originalImage = cv::imread("/home/suibian/Orientation/smallimg3.jpeg");

    if (originalImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // 进行颜色转换
    cv::Mat rgbImage;
    cv::cvtColor(originalImage, rgbImage,cv::COLOR_BGR2RGB);

    cv::namedWindow("Original Image (BGR)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original Image (BGR)", originalImage);

    cv::namedWindow("Converted Image (RGB)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Converted Image (RGB)", rgbImage);

    //ちょっと待ってください
    cv::waitKey(0);
    

    return 0;
}


```
### 通道分离 split()
```cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    // 把图片读入
    cv::Mat originalImage = cv::imread("/home/suibian/Orientation/nice.jpeg");
    cv::imshow("Original Image", originalImage);    // 显示原图

    if (originalImage.empty()) {
        std::cerr << "エラー: 画像を読み込めませんでした。" << std::endl;
        return -1;
    }

    // 使用split函数分离通道
    std::vector<cv::Mat> channels;
    cv::split(originalImage, channels);

    // 通道数を表示
    for (int i = 0; i < channels.size(); ++i) {
        cv::namedWindow("Channel " + std::to_string(i), cv::WINDOW_AUTOSIZE);
        cv::imshow("Channel " + std::to_string(i), channels[i]);
    }

    // 稍等一下
    cv::waitKey(0);
    

    return 0;
}


```

### 二值化 threshold()
```cpp
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    cv::Mat src = cv::imread("/home/suibian/Orientation/jalen.jpg", 0);
    cv::Mat dst;
    cv::threshold(src, dst, 100, 255, cv::THRESH_BINARY);
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    return 0;
}

```

### 滤波
```cpp
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    cv::Mat src = cv::imread("懒得找照片了",0);
    cv::imshow("src", src);
    cv::Mat dst;
    cv::GaussianBlur(src, dst, cv::Size(5, 5), 0, 0);   
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    return 0;
}
```

