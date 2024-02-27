/**
 * @file armor_detector_test.cpp
 * @author RoboMaster Vision Community
 * @brief 装甲板识别单元测试
 * @version 1.0
 * @date 2022-08-26
 *
 * @copyright Copyright 2023 (c), RoboMaster Vision Community
 *
 */

#include "armor_detector_test.h"

using namespace rm_test;
using namespace rm;
using namespace std;
using namespace cv;

// 单装甲板独立测试功能
TEST_F(ArmorDetectorTest, single_armor_function_test)
{
    Point center = Point(300, 300);
    buildArmorImg(center, 5);
    // imshow("src", src);
    // waitKey(0);
    auto info = p_detector->detect(groups, src, RED, GyroData(), timer.now());
    EXPECT_EQ(groups.size(), 1);

    if (info.combos.size() == 1)
        EXPECT_LE(getDistance(info.combos.front()->getCenter(), center), 10);
    else
        FAIL();
}

// 单装甲板多灯条干扰
TEST_F(ArmorDetectorTest, single_armor_more_blob_disturb)
{
    Point center(600, 500);
    // 单装甲板区域内有灯条 ( /\/ )
    buildArmorImg(center, 0);
    buildBlobImg(7, center);
    auto info = p_detector->detect(groups, src, BLUE, GyroData(), timer.now());
    auto &trackers = groups.front()->data();
    EXPECT_TRUE(trackers.empty());
    EXPECT_TRUE(info.combos.empty());
    // 单装甲板侧面有反向倾斜灯条 ( /·/ \ )
    src = Mat::zeros(Size(1280, 1024), CV_8UC3);
    buildArmorImg(center, 5);
    buildBlobImg(-15, Point(1000, 480));
    // imshow("src", src);
    // waitKey(0);
    info = p_detector->detect(groups, src, RED, GyroData(), timer.now());
    trackers = groups.front()->data();
    EXPECT_EQ(trackers.size(), 1);

    if (info.combos.size() == 1)
        EXPECT_LE(getDistance(info.combos.front()->getCenter(), center), 10);
    else
        FAIL();
    // 单装甲板区域上方有灯条 ( /`/ )
    src = Mat::zeros(Size(1280, 1024), CV_8UC3);
    buildArmorImg(center, 5);
    buildBlobImg(-15, Point(600, 200));
    // imshow("src", src);
    // waitKey(0);
    info = p_detector->detect(groups, src, RED, GyroData(), timer.now());
    trackers = groups.front()->data();
    EXPECT_EQ(trackers.size(), 1);

    if (info.combos.size() == 1)
        EXPECT_LE(getDistance(info.combos.front()->getCenter(), center), 10);
    else
        FAIL();
    // 单装甲板左右有倾斜方向相反的灯条 ( / |·| \ )
    src = Mat::zeros(Size(1280, 1024), CV_8UC3);
    buildArmorImg(center, 0);
    buildBlobImg(10, Point(200, 450));
    buildBlobImg(-10, Point(1000, 450));
    // imshow("src", src);
    // waitKey(0);
    info = p_detector->detect(groups, src, RED, GyroData(), timer.now());
    EXPECT_EQ(groups.size(), 1);

    if (info.combos.size() == 1)
        EXPECT_LE(getDistance(info.combos.front()->getCenter(), center), 10);
    else
        FAIL();
}

// 多装甲板独立
TEST_F(ArmorDetectorTest, more_armor_independence)
{
    buildArmorImg(Point(200, 100), 5);
    buildArmorImg(Point(500, 300), 0);
    buildArmorImg(Point(800, 500), -7);

    auto info = p_detector->detect(groups, src, RED, GyroData(), timer.now());

    sort(info.combos.begin(), info.combos.end(),
         [](const combo::ptr &lhs, const combo::ptr &rhs) {
             return lhs->getCenter().x < rhs->getCenter().x;
         });
    EXPECT_EQ(info.combos.size(), 3);
    if (info.combos.size() == 3)
    {
        EXPECT_LE(getDistance(info.combos[0]->getCenter(), Point(200, 100)), 10);
        EXPECT_LE(getDistance(info.combos[1]->getCenter(), Point(500, 300)), 10);
        EXPECT_LE(getDistance(info.combos[2]->getCenter(), Point(800, 500)), 10);
    }
}

// 多装甲板交错干扰
TEST_F(ArmorDetectorTest, more_armor_disturb)
{
    auto reset = [this]() {
        src = Mat::zeros(Size(1280, 1024), CV_8UC3);
    };
    // 4 灯条补给站
    buildBlobImg(0, Point(100, 500));
    buildBlobImg(0, Point(135, 500));
    buildBlobImg(0, Point(170, 500));
    buildBlobImg(0, Point(205, 500));
    // imshow("src", src);
    // waitKey(0);
    auto info = p_detector->detect(groups, src, BLUE, GyroData(), timer.now());
    EXPECT_TRUE(info.combos.empty());
    // 正对 2 装甲板倾角相反
    reset();
    buildArmorImg(Point(300, 500), 8);
    buildArmorImg(Point(800, 500), -8);
    // imshow("src", src);
    // waitKey(0);
    info = p_detector->detect(groups, src, RED, GyroData(), timer.now());

    EXPECT_EQ(info.combos.size(), 2);
    // 2 装甲板上下相距较近、有部分交错
    reset();
    buildArmorImg(Point(300, 500), 3);
    buildArmorImg(Point(440, 400), 3);
    // imshow("src", src);
    // waitKey(0);
    info = p_detector->detect(groups, src, RED, GyroData(), timer.now());

    EXPECT_EQ(info.combos.size(), 2);
}
