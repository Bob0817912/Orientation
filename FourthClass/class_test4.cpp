//使用opencv的滤波函数来处理图像

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    cv::Mat src = cv::imread("test.jpg", cv::IMREAD_COLOR);
    cv::imshow("src", src);
    cv::Mat dst;
    cv::GaussianBlur(src, dst, cv::Size(5, 5), 0, 0);   
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    return 0;
}