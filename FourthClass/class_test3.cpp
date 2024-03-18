//用opencv的函数实现图像的二值化

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    cv::Mat src = cv::imread("test.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat dst;
    cv::threshold(src, dst, 100, 255, cv::THRESH_BINARY);
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    return 0;
}

