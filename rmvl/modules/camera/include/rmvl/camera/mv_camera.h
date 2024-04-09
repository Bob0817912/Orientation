/**
 * @file mv_camera.h
 * @author RoboMaster Vision Community
 * @brief 迈德威视相机库
 * @version 3.0
 * @date 2023-12-14
 *
 * @copyright Copyright 2023 (c), RoboMaster Vision Community
 *
 */

#pragma once

#include "camutils.hpp"
#include "rmvl/core/util.hpp"

namespace rm
{

//! @addtogroup camera
//! @{
//! @defgroup mv_camera 迈德威视（MindVision）相机库
//! @}

//! @addtogroup mv_camera
//! @{

//! @example samples/camera/mv/sample_mv_auto_calib.cpp 迈德威视相机自动标定例程
//! @example samples/camera/mv/sample_mv_manual_calib.cpp 迈德威视相机手动标定例程
//! @example samples/camera/mv/sample_mv_mono.cpp 迈德威视单相机例程
//! @example samples/camera/mv/sample_mv_multi.cpp 迈德威视多相机例程
//! @example samples/camera/mv/sample_mv_writer.cpp 迈德威视相机录屏例程

//! 迈德威视相机库
class MvCamera final
{
    class Impl;

public:
    using ptr = std::unique_ptr<MvCamera>;
    using const_ptr = std::unique_ptr<const MvCamera>;

    /**
     * @brief 构造 MvCamera 对象
     *
     * @param[in] init_mode 相机初始化配置模式，需要配置 GrabMode 和 RetrieveMode
     * @param[in] serial 相机唯一序列号
     */
    MvCamera(CameraConfig init_mode, std::string_view serial = "");

    MvCamera(const MvCamera &) = delete;
    MvCamera(MvCamera &&val) : _impl(std::exchange(val._impl, nullptr)) {}

    ~MvCamera();

    /**
     * @brief 构建 MvCamera 对象
     *
     * @param[in] init_mode 相机初始化配置模式，需要配置 GrabMode 和 RetrieveMode
     * @param[in] serial 相机唯一序列号
     */
    static inline std::unique_ptr<MvCamera> make_capture(CameraConfig init_mode, std::string_view serial = "")
    {
        return std::make_unique<MvCamera>(init_mode, serial);
    }

    /**
     * @brief 设置相机参数/事件
     *
     * @param[in] propId 参数/事件编号
     * @param[in] value 参数/事件值
     * @return 是否设置成功
     */
    bool set(int propId, double value = 0.0);

    /**
     * @brief 获取相机参数
     *
     * @param[in] propId 参数编号
     * @return 参数值
     */
    double get(int propId) const;

    //! 相机是否打开
    bool isOpened() const;

    /**
     * @brief 从相机设备中读取图像
     *
     * @param[out] image 待读入的图像
     * @return 是否读取成功
     */
    bool read(cv::OutputArray image);

    /**
     * @brief 从相机设备中读取图像
     *
     * @param[out] image 待读入的图像
     */
    inline MvCamera &operator>>(cv::Mat &image)
    {
        read(image);
        return *this;
    }

    /**
     * @brief 相机重连
     *
     * @return 是否成功重连
     */
    bool reconnect();

private:
    Impl *_impl;
};

//! @} mv_camera

} // namespace rm
