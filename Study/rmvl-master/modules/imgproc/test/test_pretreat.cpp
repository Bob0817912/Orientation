/**
 * @file test_pretreat.cpp
 * @author RoboMaster Vision Community
 * @brief
 * @version 1.0
 * @date 2022-11-23
 *
 * @copyright Copyright 2023 (c), RoboMaster Vision Community
 *
 */

#include <gtest/gtest.h>

#include "rmvl/imgproc/pretreat.h"

using namespace cv;
using namespace rm;

namespace rm_test
{

class PretreatTest : public testing::Test
{
public:
    Mat img;

    inline Mat make_single_ch1(uint8_t ch) { return Mat(Size(1, 1), CV_8UC1, Scalar(ch)); }
    inline Mat make_multy_ch1(uint8_t ch) { return Mat(Size(100, 100), CV_8UC1, Scalar(ch)); }
    inline Mat make_single_ch3(uint8_t b, uint8_t g, uint8_t r) { return Mat(Size(1, 1), CV_8UC3, Scalar(b, g, r)); }
    inline Mat make_multy_ch3(uint8_t b, uint8_t g, uint8_t r) { return Mat(Size(100, 100), CV_8UC3, Scalar(b, g, r)); }
};

//! 空图像输入
TEST_F(PretreatTest, null_image_input)
{
    Mat n;
    EXPECT_TRUE(binary(n, 100).empty());
}

//! 单通道图像亮度阈值
TEST_F(PretreatTest, 1_channel_brightness)
{
    Mat ch1 = make_single_ch1(80);
    Mat bin = binary(ch1, 100);
    EXPECT_EQ(bin.at<uchar>(0, 0), 0);
    ch1 = make_single_ch1(120);
    bin = binary(ch1, 100);
    EXPECT_EQ(bin.at<uchar>(0, 0), 255);
    Mat ch2 = make_multy_ch1(120);
    bin = binary(ch2, 100);
    EXPECT_EQ(bin.at<uchar>(50, 50), 255);
}

//! 3 通道图像亮度阈值
TEST_F(PretreatTest, 3_channel_brightness)
{
    Mat ch3 = make_single_ch3(20, 80, 20);
    Mat bin = binary(ch3, 50);
    EXPECT_EQ(bin.at<uchar>(0, 0), 255);
}

//! 通道相减阈值
TEST_F(PretreatTest, 3_channel_minus)
{
    Mat ch3 = make_single_ch3(120, 20, 20);
    Mat bin = binary(ch3, BLUE, RED, 80);
    EXPECT_EQ(bin.at<uchar>(0, 0), 255);
    bin = binary(ch3, BLUE, RED, 120);
    EXPECT_EQ(bin.at<uchar>(0, 0), 0);
    ch3 = make_single_ch3(20, 20, 120);
    bin = binary(ch3, RED, BLUE, 120);
    EXPECT_EQ(bin.at<uchar>(0, 0), 0);
}

} // namespace rm_test
