//实现笔记本摄像头调用,且有快门功能和自动调节亮度功能，按esc退出


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Camera could not be opened." << std::endl;
        return -1;
    }
    cv::Mat frame;
    while (true) {
        // 读取摄像头
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Frame could not be captured." << std::endl;
            break;
        }
        cv::imshow("Camera", frame);
        // 按esc退出
        char key = cv::waitKey(1);
        if (key == 27) {
            break;
        }
        // 按s键保存图片
        if (key == 's') {
            cv::imwrite("test.jpg", frame);
        }
    }
    return 0;
}