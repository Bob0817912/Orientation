#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    // 导入文件
    cv::Mat originalImage = cv::imread("test.jpg", cv::IMREAD_COLOR);

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

