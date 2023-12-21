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
