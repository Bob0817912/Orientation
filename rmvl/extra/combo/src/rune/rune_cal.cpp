/**
 * @file Rune_cal.cpp
 * @author RoboMaster Vision Community
 * @brief 神符类中有关计算内容的成员方法实现
 * @version 1.0
 * @date 2021-09-13
 *
 * @copyright Copyright 2021 (c), RoboMaster Vision Community
 *
 */

#include <opencv2/calib3d.hpp>

#include "rmvl/combo/rune.h"

#include "rmvlpara/combo/rune.h"

namespace rm
{

std::vector<cv::Point2f> Rune::calculatePoints(RuneTarget::ptr p_target, RuneCenter::ptr p_center)
{
    // -------------------------------【获取神符五个角点】-------------------------------
    // 中心点
    cv::Point2f center = p_center->getCenter();

    cv::Point2f target_center = p_target->getCenter();
    float radius = p_target->getRadius();

    cv::Point2f direction = (target_center - center) / getDistance(target_center, center);
    // 逆时针旋转90度
    cv::Point2f vertical_direction = cv::Matx22f(0, -1, 1, 0) * direction;

    // Matx33f y_rotate;
    // Rodrigues(Vec3f(0, (PI_2) * index_delta, 0), y_rotate);
    // 四个角点
    cv::Point2f close_point = target_center - direction * radius;
    cv::Point2f left_point = target_center + vertical_direction * radius;
    cv::Point2f far_point = target_center + direction * radius;
    cv::Point2f right_point = target_center - vertical_direction * radius;

    // 4 神符装甲板角点 + 1 神符中心点, 方向是顺时针
    return {close_point, left_point, far_point, right_point, center};
}

} // namespace rm
