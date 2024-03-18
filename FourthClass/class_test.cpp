#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    // 读取视频
    cv::Mat originalImage = cv::imread("test.jpg", cv::IMREAD_COLOR);
    

    if (originalImage.empty()) {
        std::cerr << "Error: Image could not be loaded." << std::endl;
        return -1;
    }

    // 使用split函数分离通道
    std::vector<cv::Mat> channels;
    cv::split(originalImage, channels);

    // 通道数量表示
    for (int i = 0; i < channels.size(); ++i) {
        cv::namedWindow("Channel " + std::to_string(i), cv::WINDOW_AUTOSIZE);
        cv::imshow("Channel " + std::to_string(i), channels[i]);
    }

    
    cv::waitKey(0);
    

    return 0;
}
